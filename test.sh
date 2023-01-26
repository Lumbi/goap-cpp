#!/bin/bash

set -eo pipefail

./build.sh

ctest --test-dir build --output-on-failure
