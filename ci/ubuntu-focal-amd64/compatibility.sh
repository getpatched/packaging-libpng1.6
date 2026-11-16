#!/usr/bin/env bash
set -euo pipefail

work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT
cd "$work"
cc -std=c99 -Wall -Wextra -Werror /recipe/ci/ubuntu-focal-amd64/compatibility.c -lpng -o consumer
./consumer
