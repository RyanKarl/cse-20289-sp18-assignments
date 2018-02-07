#!/bin/sh

SCRIPT=caesar.sh
WORKSPACE=/tmp/$SCRIPT.$(id -u)
FAILURES=0

error() {
    echo "$@"
    echo
    [ -r $WORKSPACE/test ] && cat $WORKSPACE/test
    echo
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

cat > $WORKSPACE/input0 <<EOF
It is better to create than to learn! Creating is the essence of life.
I came, I saw, I conquered.
Experience is the teacher of all things.
Men willingly believe what they wish.
EOF

cat > $WORKSPACE/output0 <<EOF
Vg vf orggre gb perngr guna gb yrnea! Perngvat vf gur rffrapr bs yvsr.
V pnzr, V fnj, V pbadhrerq.
Rkcrevrapr vf gur grnpure bs nyy guvatf.
Zra jvyyvatyl oryvrir jung gurl jvfu.
EOF

cat > $WORKSPACE/output1 <<EOF
Sd sc loddob dy mbokdo drkx dy vokbx! Mbokdsxq sc dro occoxmo yp vspo.
S mkwo, S ckg, S myxaeobon.
Ohzobsoxmo sc dro dokmrob yp kvv drsxqc.
Wox gsvvsxqvi lovsofo grkd droi gscr.
EOF

cat > $WORKSPACE/output2 <<EOF
Wh wg pshhsf hc qfsohs hvob hc zsofb! Qfsohwbu wg hvs sggsbqs ct zwts.
W qoas, W gok, W qcbeisfsr.
Sldsfwsbqs wg hvs hsoqvsf ct ozz hvwbug.
Asb kwzzwbuzm pszwsjs kvoh hvsm kwgv.
EOF

echo "Testing caesar.sh ..."

echo -n "   Usage "
./$SCRIPT -h 2>&1 | grep -i usage 2>&1 > /dev/null
if [ $? -ne 0 ]; then
    error "Failed Usage Test"
else
    echo "Success"
fi

echo -n " ROT13-E "
./$SCRIPT < $WORKSPACE/input0 | diff -y - $WORKSPACE/output0 > $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failed Encryption Test"
else
    echo "Success"
fi

echo -n " ROT13-D "
./$SCRIPT < $WORKSPACE/output0 | diff -y - $WORKSPACE/input0 > $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failed Decryption Test"
else
    echo "Success"
fi

echo -n " ROT10-E "
./$SCRIPT 10 < $WORKSPACE/input0 | diff -y - $WORKSPACE/output1 > $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failed Encryption Test"
else
    echo "Success"
fi

echo -n " ROT16-D "
./$SCRIPT 16 < $WORKSPACE/output1 | diff -y - $WORKSPACE/input0 > $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failed Decryption Test"
else
    echo "Success"
fi

echo -n " ROT40-E "
./$SCRIPT 40 < $WORKSPACE/input0 | diff -y - $WORKSPACE/output2 > $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failed Encryption Test"
else
    echo "Success"
fi

echo -n " ROT12-D "
./$SCRIPT 12 < $WORKSPACE/output2 | diff -y - $WORKSPACE/input0 > $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failed Decryption Test"
else
    echo "Success"
fi

echo "   Score $(echo "scale=2; (7 - $FAILURES) / 7.0 * 2.5" | bc)"
echo
