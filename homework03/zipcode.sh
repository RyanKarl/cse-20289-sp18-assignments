#!/bin/sh
# Functions Print usage info and exit
usage() { 
	cat <<EOF Usage: zipcode.sh
        -c CITY Which city to search
        -s STATE Which state to search (Indiana) If no CITY is 
specified, then all the zip codes for the STATE are displayed. 
EOF
        exit $1
}
# Parse command-line options Set default values
STATE="Indiana" 
CITY="" 
while [ $# -gt 0 ]; do
        if [ $1 = "-h" ]; then
                usage 0
        #Allow user to change the city searched for
        elif [ $1 = "-c" ]; then
                CITY="$2"
                FLAG=1
                shift
        #Allow user to change the state searched for
        elif [ $1 = "-s" ]; then
                #
                STATE="$2"
                shift
        #Handle errors
        else
                usage 1
        fi 
shift 
done 
URL="http://www.zipcodestogo.com/${STATE}/"
#Filter pipeline(s) Choose which command to execute to scan for 
#zip codes
if [ "$FLAG" = "1" ]; then
        curl -sL "$URL" | grep "\/${CITY}\/" | grep -Eo '[0-9]{5}' | sort | uniq 
else
        curl -sL "$URL" | grep -E '\/[0-9]{5}\/' | grep -Eo '[0-9]{5}' | sort | uniq 
fi
