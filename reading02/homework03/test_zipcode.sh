#!/bin/sh

SCRIPT=zipcode.sh
WORKSPACE=/tmp/$SCRIPT.$(id -u)
FAILURES=0

error() {
    echo "$@"
    [ -r $WORKSPACE/test ] && cat $WORKSPACE/test
    FAILURES=$((FAILURES + 1))
}

cleanup() {
    STATUS=${1:-$FAILURES}
    rm -fr $WORKSPACE
    exit $STATUS
}

mkdir $WORKSPACE

trap "cleanup" EXIT
trap "cleanup 1" INT TERM

echo "Testing zipcode.sh ..."

echo -n "   Usage "
./$SCRIPT -h 2>&1 | grep -i usage 2>&1 > /dev/null
if [ $? -ne 0 ]; then
    error "Failed Usage Test"
else
    echo "Success"
fi

echo -n " Default "
if [ $(./$SCRIPT | wc -l) -ne 988 ]; then
    error "Failed Default Test"
else
    echo "Success"
fi

echo -n "      IN "
if [ $(./$SCRIPT -s Indiana | wc -l) -ne 988 ]; then
    error "Failed Indiana Test"
else
    echo "Success"
fi

echo -n "  ND, IN "
if [ $(./$SCRIPT -s Indiana -c "Notre Dame" | wc -l) -ne 1 ]; then
    error "Failed Notre Dame, Indiana Test"
else
    echo "Success"
fi

echo -n "  SB, IN "
if [ $(./$SCRIPT -s Indiana -c "South Bend" | wc -l) -ne 18 ]; then
    error "Failed South Bend, Indiana Test"
else
    echo "Success"
fi

echo -n "      CA "
if [ $(./$SCRIPT -s California | wc -l) -ne 2657 ]; then
    error "Failed California Test"
else
    echo "Success"
fi

echo -n "  OR, CA "
if [ $(./$SCRIPT -s California -c "Orange" | wc -l) -ne 11 ]; then
    error "Failed Orange, California Test"
else
    echo "Success"
fi

echo -n "      NY "
if [ $(./$SCRIPT -s "New York" | wc -l) -ne 2205 ]; then
    error "Failed New York Test"
else
    echo "Success"
fi

echo -n "  NY, NY "
if [ $(./$SCRIPT -s "New York" -c "New York" | wc -l) -ne 162 ]; then
    error "Failed New York, New York Test"
else
    echo "Success"
fi

echo "   Score $(echo "scale=2; (9 - $FAILURES) / 9.0 * 3.5" | bc)"
echo
