#!/bin/sh

testcase_dir="./testcases/"
bin_dir="./bin/"
test_executable="${bin_dir}test"

export LD_LIBRARY_PATH="./lib/"

for file in ${testcase_dir}*; do
  if $test_executable $file; then
    echo "$file: OK"
  fi
done
