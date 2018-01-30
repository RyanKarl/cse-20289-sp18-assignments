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
                #echo "tgz"
                ;;
        *.tar.gz)
                tar -xzvf $ARGUEMENT
                #echo "tar.gz"
                ;;
        *.tbz)
                tar -xjf $ARGUEMENT
                #echo "tbz"
                ;;
        *.tar.bz2)
                tar -xvjf  $ARGUEMENT
               # echo "tar.bz2"
                ;;
        *.txz)
                tar -xf $ARGUEMENT
               # echo "txz"
                ;;
        *.tar.xz)
                tar -xf $ARGUEMENT
               # echo "tar.xz"
                ;;
        *.zip)
                unzip $ARGUEMENT
               # echo "zip"
                ;;
        *.jar)
                unzip $ARGUEMENT
               # echo "jar"
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

