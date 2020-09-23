#!/bin/bash
set -exo pipefail
rm -rf debug
mkdir debug
cd debug
cmake -DCMAKE_BUILD_TYPE=Release ..
make
make install
