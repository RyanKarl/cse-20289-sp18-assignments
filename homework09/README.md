
mework09
===============================
By Ryan Karl


1. As discussed in class, working with system calls can be tricky because unlike most normal functions, they can fail. For each of the following scenarios involving doit, identify which system calls would fail (if any) and described you handled that situation:
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

a) No arguments passed to doit.
        No system calls will fail because I catch this situation and print a usage message to the user.

        b) $EDITOR environmental variable is not set.
                Getenv would fail, because there is nothing in the variable for it to return, but I test if the return value is NULL/false, and assign vim as a default editor.

                c) User has run out of processes.
                        Fork would fail, but I use an if statement after it is called to verify whether fork failed, and then return false and exit the program if necessary.

                        d) $EDITOR program is not found.
                                Execlp would fail, because there is nothing in the variable for it to return, but I test if the return value is NULL/false, and assign vim as a default editor.

                                e) Temporary file is deleted before moving files.
                                        Fopen would fail.  Note that move_files will rename files as specified in contents of path, and returns true or false based on whether or not all rename operations were successful. 
                                                However, I use an if statement after it is called to determine whether a path to a file does not exist and then return false if necessary.

                                                f) Destination path is not writable.
                                                        Fdopen would fail.  Note that move_files will rename files as specified in contents of path, and returns true or false based on whether or not all rename operations were successful.  
                                                                However, I use an if statement after it is called to determine whether the path is writable and return NULL if necessary.if



                                                                2. As described in the project write-up, the parent is doing most of the work in timeit since it forks, times, and waits for the child (and possibly kills it), while the child simply calls exec. To distribute the work more evenly, Bill proposes the following change:
                                                                ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                                                        Have the child set an alarm that goes off after the specified timeout. In the signal handler for the alarm, simply call exit, to terminate the child. This way, the parent just needs to wait and doesn't need to perform a kill (since the child will terminate itself after the timeout).

                                                                        Is this a good idea? Explain why or why not.
                                                                        -------------------------------------------------

                                                                                This is not a good idea, because it makes the signal handler more verbose, and increases the chance that it may be interupted.  If this happens, the parent may not be able to wait on the child, and this could spawn zombie processes.


