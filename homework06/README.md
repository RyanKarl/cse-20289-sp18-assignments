Homework 06: Pointers, Arrays, Strings
==================================================
By: Ryan Karl


Activity 1: String Utilities Library (10 Points)
-----------------------------------------------------------------


1. What is the difference between a shared library such as libstr.so and a static library such as libstr.a?
	 
	With a shared library (i.e. a .so file), all of the library's code remains in the file, and is later 
	referenced at run-time.  With a static library (i.e. a .a file), all of the library's code is directly 
	linked at compile time (i.e. it is copied to the top of the program).  Note that static libraries are more 
	portable, but using them will increase the size of binaries, lead to higher memory usage, and could potentially
	cause security issues.  Dynamic libraries can be more difficult to maintain, but allow for more flexiblity during
	software development.


2. Compare the sizes of libstr.so and libstr.a, which one is larger? Why?

	After running the ls -l command, it was determined that libstr.so contains 12831 bytes, and libstr.a 
	contains 10970 bytes, so libstr.so is larger.  This is because a shared library has more overhead for supporting
	its modular components, whereas a static library can be neatly packaged together for inclusion in a program.  Also,
	to enable run-time linking the shared object requires extra bookkeeping.  Dr. Bui compared a static library to 
	a sleek, streamlined MacBook that is powerful but not flexible, and a shared library to a Dell laptop 
	that is bulkier, but has multiple parts that can be customized to fit individual needs.


Activity 2: Str Utility (5 Points)
---------------------------------------------------------------

1. What is the difference between a static executable such as str-static and a dynamic executable such as str-dynamic?

	With a static executable, there is no dynamic linking as it is bound (i.e. the library code is copied and pasted into the executable) 
	prior to compile time.  This allows for increased portability, as the executable has been compiled, the library 
	files that were previously referenced can be discarded, as the relevant parts were copied and pasted into the executable. 
	This makes it easy to download and install programs, as no additional libraries are needed to successfully run them if 
	they are statically linked.  Unfortunately, using them increases the size of binaries, leads to higher memory usage, 
	and could potentially cause security issues. With a dynamic executable, there undefined symbols are allowed to exist in a program,
	along with a list of libraries to provide definitions at runtime.  Loading the program also loads these libraries so the linking is 
	properly completed at runtime.This allows commonly used libraries to be stored in only one location and not duplicated repeatedly.  
	Also, if a library is modified, all programs using it will be able to access the changes without being re-linked first.  In addition, this 
	allows, the executable to be smaller than its static counterpart.


2. Compare the sizes of str-static and str-dynamic, which one is larger? Why?

	After running the ls -l command, it was determined that str-static contains 774413 bytes, and str-dynamic 
	contains 13968 bytes, so str-static is larger.  This is because with a static library (i.e. a .a file), 
	all of the library's code is directly linked at compile time (i.e. it is copied to the top of the program).
	With a shared library, all of the library's code remains in the file, and is later referenced at run-time, so it is not added to the 
	executable file (this would increase the executable file size). With a dynamic executable, loading the program loads needed libraries 
	at runtime, so commonly used libraries can be stored in only one location and not duplicated repeatedly.  So, this allows the dynamic
	executable to be smaller than its static counterpart.


3. Login into a new shell and try to execute str-dynamic. Why doesn't str-dynamic work? Explain what you had to do in order for str-dynamic to actually run.

	str-dynamic doesn't work because it cannot find the appropriate library it needs to load in order to work.  To solve this I updated the 
	LD_LIBRARY_PATH shell variable to include the path to this library by using the export command in bash.   


4. Login into a new shell and try to execute str-static. Why does str-static work, but str-dynamic does not in a brand new shell session?

	str-static works because all of the libraries needed by the program for it to run are already copied and pasted into the program.
	This means no further linking needs to occur before the program can successfully run, as its dependencies are self contained.


