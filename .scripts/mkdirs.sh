#!/bin/sh

for i in $(seq 1 11); do
    n=$(printf "%02d" $i)
    mkdir reading$n
    mkdir homework$n

    cat > reading$n/README.md <<EOF
Reading $n
==========
EOF
    cat > homework$n/README.md <<EOF
Homework $n
===========
EOF
done

rm -fr homework11
