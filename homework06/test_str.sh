#!/bin/bash

WORKSPACE=/tmp/str.$(id -u)
FAILURES=0

input() {
    cat <<EOF

 
Through the woods
 Blank Space
Out of Style
I need a hero
 You Got A Friend in Me!!! 
Hello, World!
EOF
}

error() {
    echo "$@"
    [ -r $WORKSPACE/test ] && (echo; cat $WORKSPACE/test; echo)
    FAILURES=$((FAILURES + 1))
}

cleanup() {
    STATUS=${1:-$FAILURES}
    rm -fr $WORKSPACE
    exit $STATUS
}

export LD_LIBRARY_PATH=$LD_LIBRRARY_PATH:.

mkdir $WORKSPACE

trap "cleanup" EXIT
trap "cleanup 1" INT TERM

echo "Testing str utility..."

printf " %-40s ... " "str -h"
if ! ./str-static -h |& grep -q -i usage; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "str -h (valgrind)"
valgrind --leak-check=full ./str-dynamic -h &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "str"
input | ./str-static | diff -y - <(input) &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "str (valgrind)"
input | valgrind --leak-check=full ./str-dynamic &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "str aeio 4310"
input | ./str-static aeio 4310 | diff -y - <(input | tr aeio 4310) &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "str aeio 4310 (valgrind)"
input | valgrind --leak-check=full ./str-dynamic aeio 4310 &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "str -s aeio 4310"
input | ./str-static -s aeio 4310 | diff -y - <(input | tr aeio 4310 | sed -E -e 's/^\s+//' -e 's/\s+$//') &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "str -s aeio 4310 (valgrind)"
input | valgrind --leak-check=full ./str-dynamic -s aeio 4310 &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "str -r aeio 4310"
input | ./str-static -r aeio 4310 | diff -y - <(input | tr aeio 4310 | rev) &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "str -r aeio 4310 (valgrind)"
input | valgrind --leak-check=full ./str-dynamic -r aeio 4310 &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "str -l aeio 4310"
input | ./str-static -l aeio 4310 | diff -y - <(input | tr aeio 4310 | tr A-Z a-z) &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "str -l aeio 4310 (valgrind)"
input | valgrind --leak-check=full ./str-dynamic -l aeio 4310 &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "str -u aeio 4310"
input | ./str-static -u aeio 4310 | diff -y - <(input | tr aeio 4310 | tr a-z A-Z) &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "str -u aeio 4310 (valgrind)"
input | valgrind --leak-check=full ./str-dynamic -u aeio 4310 &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "str -t H3ll0 aeio 4310"
input | ./str-static -t H3ll0 aeio 4310 | diff -y - <(input | tr aeio 4310 | grep '^H3ll0') &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "str -t H3ll0 aeio 4310 (valgrind)"
input | valgrind --leak-check=full ./str-dynamic -t H3ll0 aeio 4310 &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "str -d SP4C3 aeio 4310"
input | ./str-static -d SP4C3 aeio 4310 | diff -y - <(input | tr aeio 4310 | grep 'SP4C3$') &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "str -d SP4C3 aeio 4310 (valgrind)"
input | valgrind --leak-check=full ./str-dynamic -d SP4C3 aeio 4310 &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "str -l -u aeio 4310"
input | ./str-static -l -u aeio 4310 | diff -y - <(input | tr aeio 4310 | tr a-z A-Z) &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "str -l -u aeio 4310 (valgrind)"
input | valgrind --leak-check=full ./str-dynamic -l -u aeio 4310 &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "str -r -u -t 0r3h aeio 4310"
input | ./str-static -r -u -t 0r3h aeio 4310 | diff -y - <(input | tr aeio 4310 | tr a-z A-Z | rev | grep 0r3h) &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "str -r -u -t 0r3h aeio 4310 (valgrind)"
input | valgrind --leak-check=full ./str-dynamic -r -u -t 0r3h aeio 4310 &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

TESTS=$(($(grep -c Success $0) - 1))
echo "   Score $(echo "scale=2; ($TESTS - $FAILURES) / $TESTS.0 * 3.0" | bc)"
echo
