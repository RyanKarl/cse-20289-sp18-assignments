#!/bin/sh

# Functions
usage(){
echo << EOF "Usage: match.sh [-n N -d D -S -R] column
    
    -n N    Number of items to display (default is 5)
    -d D    Delimiter to use (default is ",").
    -S      Sort output
    -R      Randomize output. 

This script selects a column (default is 1) from the CSV input and then displays
the first N items."
EOF
exit $1
}

# Default variable values

NUMBER=10
DELIMITER="," 
COLUMN=1
SORT=false
RAND=false

#Parse command line arguments

while [ $# -gt 0 ]; do
    case $1 in 
        -n) NUMBER=$2 shift;;
        -d) DELIMITER=$2 shift;;
        -S) SORT=true;;
        -R) RAND=true;;
        [0-9]*) COLUMN=$1;;
        -h) usage 0;;
        *) usage 1;;
    esac
    shift
done

# Pipeline stuff
if $SORT; then
    head -n $NUMBER | cut -d $DELIMITER -f $COLUMN | sort
elif $RAND; then
    head -n $NUMBER | cut -d $DELIMITER -f $COLUMN | shuf
else
    head -n $NUMBER | cut -d $DELIMITER -f $COLUMN 
fi
