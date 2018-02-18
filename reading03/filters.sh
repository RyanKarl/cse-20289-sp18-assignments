#!/bin/bash

q1_answer() {
    # TODO: Complete pipeline
    echo "All your base are belong to us" | tr '[:lower:]' '[:upper:]'
}

q2_answer() {
    # TODO: Complete pipeline
    echo "monkeys love bananas" | sed 's/monkeys/gorillaz/g'
}

q3_answer() {
    # TODO: Complete pipeline
    echo "     monkeys love bananas" | sed -e 's/^[ \t]*//'
}

q4_answer() {
    # TODO: Complete pipeline
    curl -sL https://yld.me/raw/yWh | awk -F: '$1 == "root" { print $7 }'
}

q5_answer() {
    # TODO: Complete pipeline
    curl -sL https://yld.me/raw/yWh | sed 's:/bin/bash:/usr/bin/python:g;s:/bin/csh:/usr/bin/python:g;s:/bin/tcsh:/usr/bin/python:g' | grep python
}

q6_answer() {
    # TODO: Complete pipeline
     curl -sL https://yld.me/raw/yWh | grep -E '4[0-9]*7'
}
