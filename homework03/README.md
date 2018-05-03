Homework 03: Regex, Filters
================================
By Ryan Karl


Activity 1: Caesar Cipher (3 Points)
--------------------------------------------
In your README.md, describe how you implemented the caesar.sh script. In particular, briefly discuss:

1. How you parsed the command line arguments.

	To parse command line arguments, I used a block of if statements combined with
	the test operator.  Specifically, I tested whether the first argument "$1" was 
	equal to a flag or value related to the program, and if so I either executed a function
	to handle the flag, or stored the value for later use when constructing the cipher text.
	Note that I used the modulus operator "%" to make sure that shift values greater than 26
	were truncated to a smaller value that could be used to properly generate the target set.

2. How you constructed the source set (ie. SET1).

	Instead of constructing one source set, I used a regular expression to create two sets for uppercase and
	lowercase letters. Later when I performed the encryption, I did this in two steps.

3. How you constructed the target set (ie. SET2).

	Instead of constructing one target set, I created two sets for uppercase and lowercase letters. 
	First, I defined two variables to hold the alphabet in upper and lowercase.  Then I used the cut
	utility to remove all of the letters in these variables after the letter indicated by the shift value.
	Then I used cut and command substitution to append this value to the end of a variable containing 
	the entire alphabet (excluding the values from the original cut operation). 

4. How you used both of these sets to perform the encryption.

	To perform the encryption, I used the tr command in conjunction with pipes.  Specifically, I ran
	tr to transform first the lowercase letters in the plaintext, and I then piped this into another 
	tr command that transformed the uppercase letters.


Activity 2: Broification (3 Points)
-----------------------------------------------------------
In your README.md, describe how you implemented the broify.sh script. In particular, briefly discuss:

1. How you parsed the command line arguments.

	To parse command line arguments, I used a block of if statements inside of a while loop 
	combined with the test command.  I continued executing the while loop until all of the
	arguments given to the command had been processed (to do this I tested if "$@" was greater
	than 0, as this indicated there were still more commands to be processed, but I made sure to
	use "shift" to decrement this value after handling each flag appropriately).  Specifically, 
	I tested whether the first argument "$1" was equal to a flag or value related to the program, 
	and if so I executed a function to handle the flag.  Note that sometimes I needed to store the
	values following the flag, and so I used variables in conjunction with "$2" and "shift" to
	get the values without disrupting the while loop.
	
2. How you removed comments.

	To remove comments, I used sed.  Specifically, I used the command "sed -e 's,${DELIM}.*,"",g'"
	where the "-e" flag allows regular expressions to be interpreted, "s" allows for the replacement
	of the everything following the comment delimiter with the empty string "" (note I used a variable 
	DELIM for this as the script allows the user to specify the delimiter used) due to the use of 
	the ".*" regular expression, and "g" to copy the hold space to the pattern space.
	
3. How you removed empty lines.

	To remove empty lines, I used sed.  Specifically, I used the command "sed -e '/^[[:space:]]*$/d'"
	where the "-e" flag allows regular expressions to be interpreted, "^" anchors the text at the front 
	of the line, "[[:space:]]" is the POSIX standard for all spacing, "*" allows repeats of what comes 
	before it, "$" anchors the text at the end of the line, and "d" allows for the deletion of what is 
	specified. 

4. How the command line options affected your operations above.

	If the user specified with the "-d" flag they wished to use a different delimiter than the
	standard "#" I passed their specification from the command line to the variable "DELIM"
	which was used when constructing appropriate sed command to run.  Also, if they specified they 
	did not wish to remove empty lines with the "-w" flag, I removed the "sed -e '/^[[:space:]]*$/d'"
	from the list of commands to be executed, thus preventing empty line removal.


Activity 3: Zip Codes (4 Points)
-----------------------------------------------------------
In your README.md, describe how you implemented the zipcode.sh script. In particular, briefly discuss:

1. How you parsed the command line arguments.

	To parse command line arguments, I used a block of if statements inside of a while loop 
	combined with the test command.  I continued executing the while loop until all of the
	arguments given to the command had been processed (to do this I tested if "$@" was greater
	than 0, as this indicated there were still more commands to be processed, but I made sure to
	use "shift" to decrement this value after handling each flag appropriately).  Specifically, 
	I tested whether the first argument "$1" was equal to a flag or value related to the program, 
	and if so I executed a function to handle the flag.  Note that sometimes I needed to store the
	values following the flag, and so I used variables in conjunction with "$2" and "shift" to
	get the values without disrupting the while loop.

2. How you extracted the zip codes.

	First, I used "curl -sL" to silently scan the specified URL's HTML for text.  Note that I used
	the variable "STATE" to specify which URL to scan.  After this, I piped the text gathered into
	a form of grep (more detail on this stage of the pipeline is presented in the response below) and
	then used grep again with the "-E" flag to allow for regular expressions and the "-o" flag to specify
	that only text matching the parameters be printed, rather than the entire line.  Also, I used
	"[0-9]{5}" to specify that only values of five consecutive digits be printed.  Lastly, I piped
	this text into "sort" to sort the values and "uniq" to remove any duplicates.

3. How you filtered by STATE and CITY.

	After parsing arguments from the command line, I used the command 'grep "\/${CITY}\/"' in the 
	second stage of my pipeline if the user wished to search by city (note that "\/" allows for 
	the backward slash to be properly interpreted, and the "$CITY" variable is surrounded by curly
	braces so the value in the variable can be expanded and concatenated correctly), or the command  
	"grep -E '\/[0-9]{5}\/'" in the second stage of my pipeline if the user wished to search by 
	state (note that the "-E" flag is used to allow for regular expressions, "\/" allows for 
	the backward slash to be properly interpreted, and "[0-9]{5}" to specifies that only 
	lines containing five consecutive digits be printed).
	

