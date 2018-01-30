Homework 02
===========
Scripting the Shell
-------------------------------------------------
By: Ryan Karl


Activity 1: Saving the World (2 Points)
-------------------------------------------------

In your README.md, describe how you implemented the extract.sh script. In particular, briefly discuss:

1. How you checked and handled having no arguments.

	To check this, I used an "if" statement.  I used "[", which is symbolically linked to "test"
	to determine if the number of arguments was equal to zero.  Note that the variable "$#" is set 
	to the number of parameters the script is called with by default, and by using the "-eq" flag
	to test for equality with the value "0" the statement will return either "true" or "false".
	If this returns "false" we continue through the script, but if this returns "true", we use the 
	"echo" command to output to the terminal usage information, set the "EXITCODE" variable to equal
	"1" to indicate an error occurred as per the convention, and exit the script.

2. How you determined which command to use for each argument.

	For this part, I consulted the man pages for both the "tar" and "unzip" commands, having known from
	prior experience with these file extensions that the above commands are used to decompress their
	contents.  Note this was still a trial and error process, and other online resources were consulted,
	including howtogeek.com, stackoverflow.com, and opensource.com.  After learning which commands were
	appropriate for each extension, I implemented a for loop, that iterated through all of the arguments
	passed to the script (using the "$@" variable, as this is its default value), and check if its extension
	matched one mentioned in the assignment's instructions.  This was done with a case statement. Finally,
	I had the script execute the proper command on the argument if a match was detected, and continued
	looping through each argument until all were tested.

3. What was the most challenging aspect of writing this script and how you overcame this issue.

	The hardest part of writing this script was debugging, particularly figuring out when a variable
	need to be preceded by the "$" symbol or not for the script to run properly.  Other languages I
	have worked with such as Java and C++ follow different conventions when dealing with variables,
	and it was difficult at first to understand the new format used for bash scripts.  This experience
	was similar to learning about how to use pointers correctly in C++ for the first time.


Activity 2: Predicting the Future (4 Points)
----------------------------------------------------

In your README.md, describe how you implemented the fortune.sh script. In particular, briefly discuss:

1. How you displayed random messages to the user.

	To display random messages, I first used the "shuf" command to generate a random number between
	0-19.  After storing this value in a variable "RAND_NUM" I used the "sed" command to select a 
	single random line from a "here document", where each line contained one of the random messages.
	After choosing a message, I used a pipe ("|") to send the output of "sed" to the input of the
	"cowsay" command, to display the message to the screen.

2. How you handled signals.

	To handle signals, I first used a "trap" statement to indicate that the SIGTERM, SIGHUP, and SIGINT
	signals (i.e. 1, 2, and 15) would be caught by my function "signal_catch()".  Then I wrote such a
	function at the top of the ".sh" file to automatically exit the script with error code 1 after 
	printing an exit message to the user if any of these signals were received (i.e. CTRL-C, etc.).	  

3. How you read input from the user.

	To accept input from the user I first created a variable "INPUT_STRING" set equal to the empty string.
	Then I used a "read" command to allow the user to supply input from the keyboard, after being queried
	for a question, and encapsulated all of this inside a while loop that used "[" to test whether the user
	had in fact supplied input, or "INPUT_STRING" was still equal to the empty string.  This was, the user
	will continue to be queried until they supply input.

4. What was the most challenging aspect of writing this script and how you overcame this issue.

	The most challenging part of writing this script was debugging, particularly figuring out how to properly
	use "sed" to scan for a single line of text from the "here document" that could be piped into "cowsay". The
	"sed" command is very robust, and it took time to read its man page along with other online examples pulled
	from www.lifewire.com, stackexchange.com, and linuxconfig.org among others, to understand how to use it 
	properly.  Also, it was challenging to understand how to use a "pipe" in conjunction with a "here table", 
	and learning the proper syntax required a great deal of trial and error.


Activity 3: Meeting the Oracle (4 Points)
----------------------------------------------------------

As you travel to the Oracle, record what you witnessed and what commands you executed in your README.md.

1. My first step was to scan `xavier.h4x0r.space` for a HTTP port:

        $ nc -z xavier.h4x0r.space 9000-9999
        Output: Connection to xavier.h4x0r.space 9104 port [tcp/peerwire] succeeded!
		Connection to xavier.h4x0r.space 9206 port [tcp/wap-vcard-s] succeeded!
		Connection to xavier.h4x0r.space 9522 port [tcp/*] succeeded!

	As can be seen, there are `3` ports in the `9000` - `9999` range.


2. Next, I tried to access the HTTP server:

        $ curl http://xavier.h4x0r.space
        Output: curl: (7) Failed to connect to xavier.h4x0r.space port 80: No route to host

	This gave me a clue to try the specific ports 9104, 9206, and 9522.


3. Next, I tried to access the HTTP server on port 9206:

        $ curl http://xavier.h4x0r.space:9206
        Output: 
                     _              _     _
                  __| |_ __ ___  __| | __| |
                 / _` | '__/ _ \/ _` |/ _` |
                | (_| | | |  __/ (_| | (_| |
                 \__,_|_|  \___|\__,_|\__,_|
	Code:
	    # Post source code with appropriate extension
	    $ curl -F source=@program.c https://dredd.h4x0r.space/code/$name
	Quiz:	
	    # Post either JSON or YAML answers file
	    $ curl -d@answers.json https://dredd.h4x0r.space/quiz/$name

	I had a hunch this was unrelated to the assignment, so I tried another port.


4. Then, I tried to access the HTTP server on port 9104:

        $ curl http://xavier.h4x0r.space:9104
        Output:  ________________________________________
		/ Halt! Who goes there?                  \
		|                                        |
		| If you seek the ORACLE, you must come  |
		| back and _request_ the DOORMAN at      |
		| /{NETID}/{PASSCODE}!                   |
		|                                        |
		| To retrieve your PASSCODE you must     |
		| first _find_ your LOCKBOX which is     |
		| located somewhere in                   |
		| ~pbui/pub/oracle/lockboxes.            |
		|                                        |
		| Once the LOCKBOX has been located, you |
		| must use your hacking skills to        |
		| _bruteforce_ the LOCKBOX program until |
		| it reveals the passcode!               |
		|                                        |
		\ Good luck!                             /
		 ----------------------------------------
		   \   ^__^
         	    \  (oo)\_______
         	       (__)\       )\/\
         	           ||--WWW |
         	           ||     ||

	
	This gave me a clue to try and enter the directory "~pbui/pub/oracle/lockboxes"
	just to see what was there.


5. After this, I tried to access the ~pbui/pub/oracle/lockboxes directory:

        $ cd ~pbui/pub/oracle/lockboxes
        Output: none

	I knew since my access wasn't denied, I could try and see what was in this directory.


6. Next, I looked to see what was inside the directory:

        $ ls
        Output: 0190466a  2c5b6d3a  4da23379  6ad55439  a3649ff2  c250ce2a  dc30ee16
		03850be4  2daeac8e  4e001fa0  6c170ddf  a378c48e  c2ad3c32  dc3cbd7a
		044ef302  2e5417d0  502cf5a1  6ccdaf55  a55def38  c2fdc8c1  dc42d557	
		04921341  30177dfe  5138dd7e  70fe64c7  a6b5171e  c34b583b  de6dfdfb
		04d5bbe2  30b6de2c  51add6ed  75254e0d  aa1840af  c380ceec  deb20a7e
		04da1248  31047c6d  5758c74f  7a010364  aa3748db  c38df0d3  e072ef93
		0621167d  31a58320  59dd3975  7d21673f  afba5f2a  c6165aef  e0fd150c
		0c6a6662  3310bf90  5b7d897b  7ff4f9e6  afde7cdc  c68c7d65  e1938ca8
		0eb26b3e  3342ae4f  5baec464  834bdb59  aff654b6  c72129a3  e2f596f3
		15feadb9  34522804  5cc27ac4  83feedaf  b0736acb  c96c57f9  e3359730
		1799680c  38cd00e9  5e7ac306  85d79baf  b0857edd  c9eb557a  e3cd9493
		1a18d39b  393073ed  5e9b6ea7  8723ad3c  b0d75be0  cae7dcef  eb284b2c
		1b47c332  3d32c65c  5f7584f1  895b0776  b2fec8bd  ceabe8c2  eeaa57b8
		1bf84c34  3d88ee15  61a94e83  89f1ac55  b5106451  cf39eb2e  ef35833b
		1c87c20a  3e48498e  62a604b3  8abce69d  b7a528d3  cffeac8a  f3b17d44
		1e57360a  3f5d82ef  6393690e  921a9973  bb6a3412  d1641b3a  f6b0b653
		1f8cc6cd  45af1b72  64035e98  936c965f  bca00d19  d309c316  f77c5b59
		240bd2a9  4636aeae  647d38d2  9383a497  beb43f07  d3d51f42  f98d5a7d
		24b6e69a  46757a65  66c76609  972e02b0  bfd13eea  d58931dd  fa9a0e6d
		24e842fd  473978f0  68030e8d  99270a26  bff75a97  d623cdb7  fbc88614
		26a66e89  48617b25  688dc2bb  9a43cc0e  c1a8a3d1  d81a08cd  feff5973
		29d03b93  48918af2  69069df5  9e8b7e86  c1b510ee  d8e60f28  ff1c4875
		2abcc409  4c847b60  69d21a84  9ff59c66  c1e2be5a  d9b37ab4

	I knew my lockbox was inside one of these directories, but I couldn't feasibly 
	search them all manually.  I needed a clever Unix command.  


7. Following this, I tried to use the "find" command to locate my lockbox:

        $ find LOCKBOX
        Output: find: `LOCKBOX': No such file or directory

	Since this command was unsuccessful, I decided to try a broader search.


8. Next, I tried to use the "find" command with a wildcard to locate my lockbox:

        $ find *
        Output: 0190466a
		0190466a/eb5f386a
		0190466a/eb5f386a/819ffa94
		0190466a/eb5f386a/819ffa94/9f299502
		0190466a/eb5f386a/819ffa94/9f299502/62356ea4
		0190466a/eb5f386a/819ffa94/9f299502/62356ea4/ahagema1.lockbox
		...
		...
		ff1c4875
		ff1c4875/77282925
		ff1c4875/77282925/613d92d2
		ff1c4875/77282925/613d92d2/8b06f2a0
		ff1c4875/77282925/613d92d2/8b06f2a0/3c52712b
		ff1c4875/77282925/613d92d2/8b06f2a0/3c52712b/nyoshida.lockbox

	This gave me a clue to search for my netid.


9. Afterword, I tried using the "find" command in conjunction with "grep" to find my lockbox:

        $ find * | grep rkarl 
        Output: 31a58320/0c9e2d50/b950f0fa/8e85a7aa/82edcce2/rkarl.lockbox

	I knew I had found the right path to reach my lockbox.


10. Then, I copied my lockbox back to my home directory:

        $ cp 31a58320/0c9e2d50/b950f0fa/8e85a7aa/82edcce2/rkarl.lockbox ~
        Output: none


11. I next tried to run the program:

        $ ./rkarl.lockbox
        Output: Usage: lockbox password

	Since I now knew the usage information, I could begin cracking the password.


12. Following this, I used the "strings" command in conjuntion with redirection to save 
    all valid passwords to a file:

        $ strings ./rkarl.lockbox > output.txt
        Output: none


13. Next, I opened the file in vim:

        $ vim output.txt 
        Output: %b^*
		%Z^*
		%R^*
		%J^*
		...
	
	Within vim I search for the string "password" using "/".
	Output: ...
		([]A\A]A^A_
		[]A\A]A^A_
		Usage: lockbox password
		cmthcmwK
		6f01953388954ece138d0ca2afee63825dad1e5c
		FATAL: kernel too old
		FATAL: cannot determine kernel version
		/dev/full
		...
	
	This gave me the clue of trying the string "cmthcmwK" as a password, since
	it came directly after the usage information.


14. After exiting vim, I tried my hunch:

        $ ./rkarl.lockbox cmthcmwK
        Output: 6f01953388954ece138d0ca2afee63825dad1e5c

	I felt confident this must be the passcode.


15. Next, I tried to access the HTTP server on port 9104 and deliver it my passcode:

        $ curl http://xavier.h4x0r.space:9104/rkarl/6f01953388954ece138d0ca2afee63825dad1e5c
	Output:	 _________________________________________
		/ Ah yes, rkarl... I've been waiting for  \
		| you.                                    |
		|                                         |
		| The ORACLE looks forward to talking to  |
		| you, but you must authenticate yourself |
		| with our agent, BOBBIT, who will give   |
		| you a message for the ORACLE.           |
		|                                         |
		| He can be found hidden in plain sight   |
		| on Slack. Simply send him a direct      |
		| message in the form "!verify netid      |
		| passcode". Be sure to use your NETID    |
		| and the PASSCODE you retrieved from the |
		| LOCKBOX.                                |
		|                                         |
		| Once you have the message from BOBBIT,  |
		| proceed to port 9522 and deliver the    |
		| message to the ORACLE.                  |
		|                                         |
		| Hurry! The ORACLE is wise, but she is   |
		\ not patient!                            /
		 -----------------------------------------
		     \
		      \
		          oO)-.                       .-(Oo
		         /__  _\                     /_  __\
		         \  \(  |     ()~()         |  )/  /
		          \__|\ |    (-___-)        | /|__/
		          '  '--'    ==`-'==        '--'  '


16. After this, I navigated to our class's slack page using a web browser, located Bobbit at
    https://nd-cse.slack.com/messages/D8Z6ZES1F/details/, and gave him my passcode.

        $ !verify rkarl 6f01953388954ece138d0ca2afee63825dad1e5c
        Output: Hola rkarl! Please tell the ORACLE the following MESSAGE: ZXhuZXk9MTUxNzA5ODEwMw==


17. Following this, I returned to the terminal, and tried to reach the oracle at port 9522 to
    deliver the message:
	
       $ curl http://xavier.h4x0r.space:9522/ZXhuZXk9MTUxNzA5ODEwMw==
        Output:  ________________________
		< Hello, who may you be? >
		 ------------------------
		       \    ____
		        \  /    \
		          | ^__^ |
		          | (oo) |______
		          | (__) |      )\/\
		           \____/|----w |
		                ||     ||
			
		                 Moofasa
	NAME?  ______________________________________
		/ Hmm... GET /ZXhuZXk9MTUxNzA5ODEwMw== \
		| HTTP/1.1?                            |
		|                                      |
		| That name sounds familiar... what    |
		\ message do you have for me?          /
		 --------------------------------------
		       \    ____
		        \  /    \
		          | ^__^ |
		          | (oo) |______
		          | (__) |      )\/\
		           \____/|----w |
		                ||     ||
		
		                 Moofasa
	MESSAGE?  _________________________________________
		/ I'm sorry sugar, but I don't understand \
		| this message:                           |
		|                                         |
		| Host: xavier.h4x0r.space:9522           |
		|                                         |
		| Perhaps, it wasn't meant for you.       |
		|                                         |
		| Why don't you go back to the DOORMAN or |
		\ BOBBIT?                                 /
		 -----------------------------------------
		       \    ____
		        \  /    \
		          | ^__^ |
		          | (oo) |______
		          | (__) |      )\/\
		           \____/|----w |
		                ||     ||
		
		                 Moofasa
	
	
	
18. I then attempted to contact the oracle using "telnet": 

        $ telnet xavier.h4x0r.space 9522
        Output: Trying 129.74.160.130...
		Connected to xavier.h4x0r.space (129.74.160.130).
		Escape character is '^]'.
		 ________________________
		< Hello, who may you be? >
		 ------------------------
		     \
		      \
		       ("`-'  '-/") .___..--' ' "`-._
		         ` *_ *  )    `-.   (      ) .`-.__. `)
		         (_Y_.) ' ._   )   `._` ;  `` -. .-'
		      _.. `--'_..-_/   /--' _ .' ,4
		   ( i l ),-''  ( l i),'  ( ( ! .-'
		NAME?

	This seemed promising.


19. Next, I gave my netid to the oracle as my name.

        NAME? rkarl
        Output:  ___________________________________
		/ Hmm... rkarl?                     \
		|                                   |
		| That name sounds familiar... what |
		\ message do you have for me?       /
		 -----------------------------------
		     \
		      \
		       ("`-'  '-/") .___..--' ' "`-._
		         ` *_ *  )    `-.   (      ) .`-.__. `)
		         (_Y_.) ' ._   )   `._` ;  `` -. .-'
		      _.. `--'_..-_/   /--' _ .' ,4
		   ( i l ),-''  ( l i),'  ( ( ! .-'
		MESSAGE?
		

20. Following this, I gave Bobbit's message to the oracle.

        MESSAGE? ZXhuZXk9MTUxNzA5ODEwMw==
        Output:  ________________________________________
		/ Ah yes... rkarl!                       \
		|                                        |
		| You're smarter than I thought. I can   |
		| see why the instructor likes you.      |
		|                                        |
		| You met BOBBIT about 96 minutes ago... |
		\ What took you so long?                 /
		 ----------------------------------------
		     \
		      \
		       ("`-'  '-/") .___..--' ' "`-._
		         ` *_ *  )    `-.   (      ) .`-.__. `)
		         (_Y_.) ' ._   )   `._` ;  `` -. .-'
		      _.. `--'_..-_/   /--' _ .' ,4
		   ( i l ),-''  ( l i),'  ( ( ! .-'
		REASON? 


21. I then told the oracle my answer.

        REASON? I had to get past Agent Smith!
        Output: Congratulations rkarl! You have reached the end of this journey.

		I hope you learned something from the ORACLE :]

		} v   B (   Z     . <     8   : I k ;   V E       N     L f / 9   B         F &
		9 a   4 p   C     g _     H   0 2 ` k   ) $       ,     W w J T   V         1
		2 I   X "   E     a T     %   " n =     - " k     @     R   ; *   a         T
		5 n   X $   4     q =     t   ) { 4     s L G     O     c   * M   -         R
		( Y   T |   E     h #     =   + ? H     K P N     P     '     H   $         F
		  w   K a   6   Q j y   N 6   % g {     g w _   p       p     S   J         _
		  k   q o   z : % ^ R v g ; U C   T     Y   0   |     d ,       g 6         W
		  Y   }       p 4 n ] w m " 4 ^   1     k   u   X     h F       ;
		      s       C ]   ' * ; C C %   {     `   T   M     r z       >     (
		              V S   W Y c $ ^ +   x         t x A     Q 8       }     e
		              `     | l S I /     E       u Y 2 . :   @ 3       5     5 b
		              8     % m 9 & h     X   "   $ H J ] -   U         H     \ &   A
		              (       i l = Z     {   -   ; _ + : 6         L   K     C s   8
		c             [           Z s     6   t   t ] g y ^         {   k     h !   [
		V         ^   +           ! #         $   ` B r ! c %       K       V 0 S   5
		j G       B   c           ) 8   3     Y   V y r { X 5 N     <       I " U   E
		N 4       a   F             '   [     2   = < ; ) 8 S *     v       U Y 4   r
		o V       h   E             e   z     0   s V V 0 B k M     L       j [ c   p \
		< Z       "   %             z   9     ]   | J w   w Y j     x       4 m &   s V
		0 O 7     O   l             s   $         M ) }   \ I ,     v q     < B W * 5 :
		K F +     r I h             I   4         o L t   g Q %     ^ -     } k = ' [ 2
		  > 1     { O )             5   `         8 - e   7 < >     - ]     & B 3 % $ y
		  o i     Y < J             6   u         *   |   { ! /     D | / n ! z J u   $
		  t c     g o X K           j   ;         '   S   L W `     8   U |   & 6 ,   d


	I learned a lot completing this exercise, in particular, how to leverage tools
	like "netcat", "curl", and "telnet" to accomplish networking tasks.  These tools allowed
	me to scan for open ports on external networked devices, connect to these devices from my
	terminal, and communicate with them throughout my journey.  Also, I gained experience 
	with security related tasks, such as password cracking, and made use of the "strings" 
	command to inspect an executable file for useful information during a penetration test.
	

