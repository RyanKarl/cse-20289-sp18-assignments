# Functions 
#Display usage info

usage() {
        cat <<EOF 
Usage: $(basename $0) [rotation] 

This program will read from stdin and rotate the text by the specified 
rotation.  If none is specified, then the default value is 13. 
EOF
        exit $1
}
if [ "$1" = "-h" ]; then
        usage 0
#Handle no arguments being specified
elif [ "$1" = "" ]; then
        SHIFT=13
#Allow user to specify shift value
else
        SHIFT=$(expr ${1} % 26) 
fi

#Construct source sets
LOWERCASE=abcdefghijklmnopqrstuvwxyz 
UPPERCASE=ABCDEFGHIJKLMNOPQRSTUVWXYZ

#Construct target sets
CIPHERLOWER=$(echo $LOWERCASE | cut -c ${SHIFT}-26)$(echo $LOWERCASE | cut -c 1-${SHIFT}) 
CIPHERUPPER=$(echo $UPPERCASE | cut -c ${SHIFT}-26)$(echo $UPPERCASE | cut -c 1-${SHIFT})

#Perform encryption transformation
tr '[a-z]' $CIPHERLOWER | tr '[A-Z]' $CIPHERUPPER
