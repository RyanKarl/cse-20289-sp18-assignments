#!/bin/sh

SCRIPT=broify.sh
WORKSPACE=/tmp/$SCRIPT.$(id -u)
FAILURES=0

error() {
    echo "$@"
    echo
    [ -r $WORKSPACE/test ] && cat $WORKSPACE/test
    echo
    FAILURES=$(($FAILURES + 1))
}

cleanup() {
    STATUS=${1:-$FAILURES}
    rm -fr $WORKSPACE
    exit $STATUS
}

mkdir $WORKSPACE

trap "cleanup" EXIT
trap "cleanup 1" INT TERM

cat > $WORKSPACE/input0 <<EOF
# Super useful comment describing a tricky configuration option
SETUP_THE_BOMB="no" # Hide the evidence

# Another super userful comment
BASE_OWNERSHIP="us" # All your base are belong to...
EOF

cat > $WORKSPACE/output0 <<EOF
SETUP_THE_BOMB="no"
BASE_OWNERSHIP="us"
EOF

cat > $WORKSPACE/output0W <<EOF

SETUP_THE_BOMB="no"


BASE_OWNERSHIP="us"
EOF

cat > $WORKSPACE/input1 <<EOF
// C++ is so cool
int main() {
    // Totes
    return 0;	// YESSS
}
EOF

cat > $WORKSPACE/output1 <<EOF
int main() {
    return 0;
}
EOF

cat > $WORKSPACE/output1W <<EOF

int main() {

    return 0;
}
EOF

echo "Testing broify.sh ..."

echo -n "   Usage "
./$SCRIPT -h 2>&1 | grep -i usage 2>&1 > /dev/null
if [ $? -ne 0 ]; then
    error "Failed Usage Test"
else
    echo "Success"
fi

echo -n "    BASE "
./$SCRIPT < $WORKSPACE/input0 | diff -y - $WORKSPACE/output0 > $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failed BASE Test"
else
    echo "Success"
fi

echo -n " BASE -W "
./$SCRIPT -W < $WORKSPACE/input0 | diff -y - $WORKSPACE/output0W > $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failed BASE Test (-W)"
else
    echo "Success"
fi

echo -n "     C++ "
./$SCRIPT -d '//' < $WORKSPACE/input1 | diff -y - $WORKSPACE/output1 > $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failed C++ Test"
else
    echo "Success"
fi

echo -n "  C++ -W "
./$SCRIPT -d '//' -W < $WORKSPACE/input1 | diff -y - $WORKSPACE/output1W > $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failed C++ Test (-W)"
else
    echo "Success"
fi

echo "   Score $(echo "scale=2; (5 - $FAILURES) / 5.0 * 2.5" | bc)"
echo
