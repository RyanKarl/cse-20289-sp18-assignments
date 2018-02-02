#!/bin/sh

#Set path
PATH=/afs/nd.edu/user15/pbui/pub/bin/:${PATH}

#Indicate SIGHUP, SIGINT, and SIGTERM will be caught
trap signal_catch 1 2 15

signal_catch()
{
   EXITCODE=1

   #Print message and exit with error
   cowsay "Leaving so soon?"
   exit $EXITCODE
}

EXITCODE=0

cowsay "Hello $USER what question do you have for me today?"

INPUT_STRING=""

#Check if no input was given
while [ "$INPUT_STRING" = "" ]
   do
      #Query user and accept input
      echo -n "Question? "
      read INPUT_STRING
   done

#Generate random number from 0-19
RAND_NUM=`shuf -i0-19 -n1`

#Output message from list based on random number
   #Begin here document
   sed -n ${RAND_NUM}P <<fortune_message_text | cowsay
   It is certain
   It is decidedly so
   Without a doubt
   Yes, definitely
   You may rely on it
   As I see it, yes
   Most likely
   Outlook good
   Yes
   Signs point to yes
   Reply hazy try again
   Ask again later
   Better not tell you now
   Cannot predict now
   Concentrate and ask again
   Don't count on it
   My reply is no
   My sources say no
   Outlook not so good
   Very doubtful
fortune_message_text
#End here document

#Exit successfully
exit $EXITCODE

