#!/bin/sh

#Set exit code to success
EXITCODE=0

#Check if no arguements were given
if [ $# -eq 0 ]
  then
    EXITCODE=1
    #Output usage info and exit with error code
    echo "Usage: extract.sh archive1 archive2..."
    exit $EXITCODE
fi

#Iterate through arguements
for ARGUEMENT in "$@"; do
  #Determine which unzipping tool to use based on extension
  case $ARGUEMENT in
        *.tgz)
                tar -xzvf $ARGUEMENT
                ;;
        *.tar.gz)
                tar -xzvf $ARGUEMENT
                ;;
        *.tbz)
                tar -xjf $ARGUEMENT
                ;;
        *.tar.bz2)
                tar -xvjf  $ARGUEMENT
                ;;
        *.txz)
                tar -xf $ARGUEMENT
                ;;
        *.tar.xz)
                tar -xf $ARGUEMENT
                ;;
        *.zip)
                unzip $ARGUEMENT
                ;;
        *.jar)
                unzip $ARGUEMENT
                ;;
        *)
                EXITCODE=1
                echo "Unknown archive format: $ARGUEMENT"
                exit $EXITCODE
                ;;
  esac
done

#Exit successfully
exit $EXITCODE

