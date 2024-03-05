#!/bin/bash
# Ref: https://help.acmicpc.net/language/info

src_file_name="./solution.cc"
if [[ -n $1 ]]; then
  src_file_name="$1"
fi
out_file_name="${src_file_name%.cc}"

g++ "$src_file_name" -o "$out_file_name" -O2 -Wall -lm -static -std=gnu++17 -DONLINE_JUDGE -DBOJ