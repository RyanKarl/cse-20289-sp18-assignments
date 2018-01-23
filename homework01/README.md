Homework 01
===========
Ryan Karl

Activity 1: File Operations (2 Points)
---------------------------------------------
1. Copy all the contents of the /usr/share/pixmaps folder to a new images folder in your AFS home directory.
2. Rename this new images folder in your home directory to pixmaps.
3. Move this new pixmaps folder to /tmp/$USER-pixmaps (where $USER is your netid)
4. Remove the /tmp/$USER-pixmaps folder

5. Markdown Table

	| Command                             | Elapsed Time  |
	|-------------------------------------|---------------|
	| cp -r /usr/share/pixmaps ~/images   | 1.200 seconds |
	| mv images/ pixmaps                  | 0.004 seconds |
	| mv pixmaps/ /tmp/rkarl-pixmaps      | 0.764 seconds |
	| rm -r /tmp/rkarl-pixmaps            | 0.009 seconds |

1.Both renaming and moving the pixmaps folder use the mv command but the former operation takes 
  significantly less time than the latter. Explain why this is.

	With the former operation, we are already in the destination directory, so we can simply 
	rewrite the name of the folder.  The latter operation is more complicated, as we must remove
	the directory at its current location, traverse the directory hierarchy and then copy the
	directory to its final location, and more time is needed to complete all of these steps.


2.Similarly, explain why removing the /tmp/$USER-pixmaps operation is faster than the move operation.

	The former operation is faster because we are simply removing the link to the directory.  In
	contrast, the latter operation requires the multistep process described above, which takes 
	significantly more time to complete. 


Activity 2: Redirection (2 Points)
---------------------------------------
1. How would you use I/O redirection to process the math.txt file with bc?

	bc < math.txt


2. How would you use I/O redirection to process the math.txt file with bc and save the output to results.txt?

	bc < math.txt > results.txt


3. How would you use I/O redirection to process the math.txt file with bc, save the output to results.txt, and suppress any errors?

	bc < math.txt > output.txt 2>/dev/null


4-1. How would you use cat and a pipeline instead of I/O redirection to process the math.txt file with bc?

	cat math.txt | bc

4-2. Why is this considered less efficient than using I/O redirection?

	This requires the system to process two seperate programs, as we must use two tools, 
	'cat' and '|' (pipeline), to accomplish our task, instead of simply using one tool '<' to redirect input.


Activity 3: Pipelines (3 Points)
--------------------------------------
1. Determine how many accounts in the /etc/passwd file have /sbin/nologin as their shell.

	cat /etc/passwd | grep /sbin/nologin | wc -l
	50 accounts


2. Determine how many instances of bash are running on the current machine (including all users).

	ps -A | grep bash | wc -l
	19 total instances


3. Determine the top 5 largest files or directories in the /etc directory while suppressing any errors.

	du /etc/* 2>/dev/null | sort -nr | head -n 5
	
	|Rank: |Usage:| File/Directory Name:          |
	|------|------|-------------------------------|
	|1     |8952  | /etc/selinux                  |
	|2     |8932  | /etc/selinux/targeted         |
	|3     |8556  | /etc/gconf                    |
	|4     |8284  | /etc/selinux/targeted/policy  |
	|5     |4760  | /etc/gconf/gconf.xml.defaults |


4. Determine how many unique users are logged into the current system.

	who | awk '{print $1}' | sort | uniq | wc -l
	3 unique users


Activity 4: Processes & Signals (3 Points)
---------------------------------------------------
1. Using a single terminal window, run the TROLL program and figure out a way to terminate it:
a. Describe what commands or operations failed to terminate the process.

	Note that CTRL-C will not terminate the process, and CTRL-Z will stop the process
	without terminating it outright.  Once stopped, the command 'pgrep TROLL' will display
	the PID of the TROLL program.  Using the 'kill' command on this PID with flags 1, 2, 
	3, 15, 19, and 20 also failed to terminate the TROLL. 
	

b. Describe what commands or operations finally succeeded in terminating the process.

	Entering CTRL-Z to stop the process, followed by 'pgrep TROLL', and finally
	'kill -9 PID' where PID is the output of 'pgrep TROLL' terminated the process. 


2. Using two terminal windows, run the TROLL program in the first window and figure out a way to 
terminate it from the second terminal window:
a. Describe a pipeline that can be used to terminate the process from the second terminal window.

	'kill -9 $(ps -A | grep TROLL | awk '{print $1}')' works, but note it makes use of 
	command substitution.
	

b. Describe a single command that can be used to terminate the process from the second terminal window.

	'killall -9 TROLL'
	

3.Which signals lead to interesting messages that are not taunts or insults?

	The combination CTRL-4 gives a message 'Quit (core dumped)' and the majority of the other
	CTRL-(number or letter) give messages of the form '^(number or letter key pressed)'.


