#!/bin/sh
# Functions Tell user usage details and exit
usage() {
        cat <<EOF 
	Usage: broify.sh
        -d DELIM Use this as the comment delimiter.
        -W Don't strip empty lines. 
EOF
        exit $1
}
#Declare default delimiter and default command to remove 
#comments, empty lines, and trailing whitespace
DELIM="#" 
PIPE="sed -e 's,${DELIM}.*,"",g; /^[[:space:]]*$/d; s/[ \t]*$//'"
# Parse command-line options
while [ $# -gt 0 ]; do
        #Call usage
        if [ "$1" = "-h" ]; then
                usage 0
        #Store new delimiter value and new command to remove 
        #comments, empty lines, and trailing whitespace
        elif [ "$1" = "-d" ]; then
                DELIM=${2}
                PIPE=" sed -e 's,${DELIM}.*,"",g; /^[[:space:]]*$/d; s/[ \t]*$//'"
                shift
        #Store new command to only remove comments and trailing 
        #whitespace
        elif [ "$1" = "-W" ]; then
                PIPE=" sed -e 's,${DELIM}.*,"",g; s/[ \t]*$//'"
        else
        #Handle errors
                usage 1
        fi
        shift 
done
# Filter pipeline Apply changes
eval $PIPE
