#!/bin/bash

set -e

command_exists() {
    command -v "$1" >/dev/null 2>&1
}

get_compose_cmd() {
    if command_exists "docker" && docker compose version >/dev/null 2>&1; then
        echo "docker compose"
    elif command_exists "docker-compose"; then
        echo "docker-compose"
    else
        echo "none"
    fi
}

compose_cmd=$(get_compose_cmd)

if [ "$compose_cmd" = "none" ]; then
    echo "Error: Neither 'docker compose' nor 'docker-compose' is available."
    echo "Please install Docker with Compose plugin or standalone docker-compose."
    exit 1
fi

$compose_cmd pull codefreemax
$compose_cmd up -d --remove-orphans
