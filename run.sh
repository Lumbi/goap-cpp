#!/bin/bash

set -eo pipefail

./build.sh

./build/src/goap
