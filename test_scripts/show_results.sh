#!/bin/sh

SCRIPT_NAME=$0
TEST_FILE=$1


# compile programs
cd ..
make clean && make
cd -
#


echo
echo "Path to test file -> '$TEST_FILE'"
echo "===============RESULTS================="
echo
echo "wc results"
wc -l $TEST_FILE
echo "---------------------------------------"

echo
echo "simple_line_count results"
../simple_line_count $TEST_FILE
echo "---------------------------------------"

echo
echo "wc_alias results"
../wc_alias $TEST_FILE
echo "---------------------------------------"

