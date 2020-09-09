#!/usr/bin/env bash
apt update && apt install -y libflint-dev libflint-arb-dev
git clone https://github.com/wbhart/antic /tmp/antic
cd /tmp/antic
./configure
make
make install
