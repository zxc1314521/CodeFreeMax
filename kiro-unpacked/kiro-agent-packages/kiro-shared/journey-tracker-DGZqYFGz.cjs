"use strict";
var __defProp = Object.defineProperty;
var __defNormalProp = (obj, key, value) => key in obj ? __defProp(obj, key, { enumerable: true, configurable: true, writable: true, value }) : obj[key] = value;
var __publicField = (obj, key, value) => __defNormalProp(obj, typeof key !== "symbol" ? key + "" : key, value);
const api = require("@opentelemetry/api");
const telemetry_definitions_index = require("./telemetry/definitions/index.cjs");
class Metrics {
  /**
   * Creates a new Metrics instance for the given telemetry namespace
   * @param namespace The telemetry namespace to use for metrics
   */
  constructor(namespace) {
    __publicField(this, "counters", /* @__PURE__ */ new Map());
    __publicField(this, "histograms", /* @__PURE__ */ new Map());
    __publicField(this, "namespace");
    __publicField(this, "meter");
    this.namespace = namespace;
    this.meter = getMeter(namespace);
  }
  /**
   * Add a count metric
   */
  addCount(name, value, attributes = {}) {
    const values = this.counters.get(name) || [];
    values.push({ value, attributes });
    this.counters.set(name, values);
  }
  /**
   * Add a histogram metric
   */
  addHistogram(name, value, attributes = {}) {
    const values = this.histograms.get(name) || [];
    values.push({ value, attributes });
    this.histograms.set(name, values);
  }
  /**
   * Flush all collected metrics to OpenTelemetry
   */
  flush() {
    for (const [name, values] of this.counters.entries()) {
      const counter = this.meter.createCounter(name);
      for (const { value, attributes } of values) {
        counter.add(value, attributes);
      }
    }
    this.counters.clear();
    for (const [name, values] of this.histograms.entries()) {
      const histogram = this.meter.createHistogram(name);
      for (const { value, attributes } of values) {
        histogram.record(value, attributes);
      }
    }
    this.histograms.clear();
  }
}
function createCounter(namespace, name, options) {
  return getMeter(namespace).createCounter(name, options);
}
function createHistogram(namespace, name, options) {
  return getMeter(namespace).createHistogram(name, options);
}
const meters = {};
function getMeter(namespace) {
  if (namespace in meters) {
    return meters[namespace];
  }
  const meter = api.metrics.getMeter(namespace, telemetry_definitions_index.APPLICATION_VERSION);
  if (telemetry_definitions_index.isInitialized()) {
    meters[namespace] = meter;
  }
  return meter;
}
const journeyTrackers = {};
function getJourneyTracker(namespace) {
  if (namespace in journeyTrackers) {
    return journeyTrackers[namespace];
  }
  const tracker = new JourneyTracker(namespace);
  journeyTrackers[namespace] = tracker;
  return tracker;
}
class JourneyTracker {
  /**
   * Creates a new journey tracker
   */
  constructor(namespace) {
    __publicField(this, "namespace");
    __publicField(this, "activeJourneys", /* @__PURE__ */ new Map());
    this.namespace = namespace;
  }
  /**
   * Starts tracking a new telemetry journey
   * @param config Configuration for the journey
   * @returns Unique journey identifier
   * @example
   * const journeyId = telemetry.startJourney({
   *   id: 'onboarding',
   *   timeoutMs: 10000,
   *   namespace: TelemetryNamespace.Core
   * });
   */
  startJourney(config) {
    const existingJourney = this.activeJourneys.get(config.id);
    if (existingJourney) {
      return existingJourney.uniqueId;
    }
    const uniqueId = `${config.id}-${Date.now()}-${Math.random().toString(36).slice(2, 8)}`;
    const timeoutId = setTimeout(() => {
      this.timeoutJourney(config.id);
    }, config.timeoutMs);
    const newContext = {
      journeyId: config.id,
      uniqueId,
      timeoutId,
      startTime: performance.now(),
      durationTracker: createHistogram(this.namespace, `journey.${config.id}.duration`, {
        unit: "milliseconds"
      }),
      metrics: new Metrics(this.namespace),
      onJourneyEnd: config.onJourneyEnd
    };
    this.activeJourneys.set(config.id, newContext);
    createCounter(this.namespace, `journey.${config.id}.started`).add(1);
    return uniqueId;
  }
  /**
   * Marks a journey as successfully completed
   * @param journeyId ID of the journey to complete
   * @param attributes Additional attributes to record with completion
   * @example
   * telemetry.completeJourney('journey-123', { outcome: 'success' });
   */
  completeJourney(journeyId, attributes = {}) {
    const journey = this.activeJourneys.get(journeyId);
    if (!journey) {
      return;
    }
    this.cleanupJourney(journeyId);
    createCounter(this.namespace, `journey.${journeyId}.completed`).add(1, {
      ...attributes
    });
  }
  /**
   * Handles journey timeout by marking the span as error and cleaning up
   * @param journeyId ID of the timed out journey
   */
  timeoutJourney(journeyId) {
    const journey = this.activeJourneys.get(journeyId);
    if (!journey) {
      return;
    }
    this.cleanupJourney(journeyId);
    createCounter(this.namespace, `journey.${journeyId}.time_out`).add(1, {});
  }
  cleanupJourney(journeyId) {
    const journey = this.activeJourneys.get(journeyId);
    if (!journey) {
      return;
    }
    if (journey.onJourneyEnd) {
      journey.onJourneyEnd(journey.metrics);
    }
    journey.durationTracker.record(performance.now() - journey.startTime);
    journey.metrics.flush();
    clearTimeout(journey.timeoutId);
    this.activeJourneys.delete(journeyId);
  }
  /**
   * Cleans up all active journeys when the tracker is disposed
   */
  dispose() {
    for (const [journeyId, journey] of this.activeJourneys) {
      this.cleanupJourney(journeyId);
      createCounter(this.namespace, `journey.${journeyId}.disposed`).add(1, {
        journeyId,
        uniqueJourneyId: journey.uniqueId
      });
    }
    this.activeJourneys.clear();
  }
}
exports.JourneyTracker = JourneyTracker;
exports.Metrics = Metrics;
exports.createCounter = createCounter;
exports.createHistogram = createHistogram;
exports.getJourneyTracker = getJourneyTracker;
