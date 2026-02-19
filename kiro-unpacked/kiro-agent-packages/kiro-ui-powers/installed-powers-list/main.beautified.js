import {
  r as e,
  Y as p,
  j as s,
  d as P,
  E as x,
  c as j,
  x as f
} from "../assets/ErrorMessage-sgZuVxCg.js";
import {
  P as I
} from "../assets/PowersList-S_kIuQZ-.js";
import "../styles.js";

function C() {
  const {
    addListener: o,
    callApi: r
  } = e.useContext(p), [d, n] = e.useState(!0), [a, i] = e.useState([]), [c, u] = e.useState(), l = e.useCallback(
  async () => {
      n(!0);
      try {
        const {
          powers: t
        } = await r("listInstalledPowers");
        i(t)
      } catch (t) {
        u(t)
      } finally {
        n(!1)
      }
    }, [r]);
  e.useEffect(() => {
    l();
    const t = o("onPowerInstalled", () => {
        l()
      }),
      m = o("onPowerUninstalled", () => {
        l()
      });
    return () => {
      t(), m()
    }
  }, [o, l]);
  const w = e.useCallback(() => {
    r("addCustomPower")
  }, [r]);
  return {
    isLoading: d,
    installedPowers: a,
    installedPowersError: c,
    handleAddCustomPowerClick: w
  }
}

function h({
  onClick: o
}) {
  return s.jsxs("div", {
    className: "add-custom-power",
    onClick: o,
    children: [s.jsx("div", {
      className: "add-custom-power-icon",
      children: s.jsx(P, {
        type: "add"
      })
    }), s.jsxs("div", {
      className: "add-custom-power-content",
      children: [s.jsx("div", {
        className: "add-custom-power-label",
        children: "Add Custom Power"
      }), s.jsx("div", {
        className: "add-custom-power-description",
        children: "Import from url, folder or build your own"
      })]
    })]
  })
}

function v() {
  const {
    isLoading: o,
    installedPowers: r,
    installedPowersError: d,
    handleAddCustomPowerClick: n
  } = C();
  return d ? s.jsx(x, {
    error: d
  }) : !o && s.jsx(I, {
    firstItem: s.jsx(h, {
      onClick: n
    }),
    powers: r
  })
}
j.createRoot(document.getElementById("root")).render(s.jsx(e.StrictMode, {
  children: s.jsx(f, {
    editorApi: window.vscode,
    children: s.jsx(v, {})
  })
}));