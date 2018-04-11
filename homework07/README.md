Homework 07
=======================
By Ryan Karl

# Activity 2 - Questions

--------------------------------------------------------
|        FILE        | OLD SIZE | NEW SIZE |   RATIO   |
|--------------------|----------|----------|-----------|
|   data/1342-0.ascii|   5712504|   3238750|     56.70%|
|     data/11-0.ascii|   1316256|    762209|     57.91%|
|    data/219-0.ascii|   1866304|   1065323|     57.08%|
|     data/84-0.ascii|   3579976|   2005480|     56.02%|
|     data/98-0.ascii|   6298296|   3575846|     56.77%|
--------------------------------------------------------

1. Describe how the symbol is stored in the Node struct by diagramming the memory layout of 
the following Node structure:
--------------------------------------------------------------------------------------------

Node *n = node_create('\n', 2, NULL, NULL);

Be sure to indicate how much memory each Node structure occupies and how much is allocated for 
each attribute in the struct.

	 _____  _____  _____  _____  _____  _____  _____  _____ 
	|     ||     ||     ||     ||     ||     ||     ||     |
	|  \  ||  n  ||  0  ||  0  ||  0  ||  0  ||  0  ||  0  |
	|_____||_____||_____||_____||_____||_____||_____||_____|
	 _____  _____  _____  _____  _____  _____  _____  _____ 
	|     ||     ||     ||     ||     ||     ||     ||     |
	|  2  ||  0  ||  0  ||  0  ||  0  ||  0  ||  0  ||  0  |
	|_____||_____||_____||_____||_____||_____||_____||_____|
	 _____  _____  _____  _____  _____  _____  _____  _____ 
	|     ||     ||     ||     ||     ||     ||     ||     |
	|  0  ||  0  ||  0  ||  0  ||  0  ||  0  ||  0  ||  0  |
	|_____||_____||_____||_____||_____||_____||_____||_____|
	 _____  _____  _____  _____  _____  _____  _____  _____ 
	|     ||     ||     ||     ||     ||     ||     ||     |
	|  0  ||  0  ||  0  ||  0  ||  0  ||  0  ||  0  ||  0  |
	|_____||_____||_____||_____||_____||_____||_____||_____|

	Node takes up 32 bytes in memory(each box represents a byte).  
	symbol takes 8 bytes, count takes 8 bytes (64 bit system), *left takes 8 bytes (pointer), and *right takes 8 bytes(pointer).


1a. Explain what the code assert(n->symbol.letter == '\n') would result in?
----------------------------------------------------------------------------------------------

	Below is the declaration for assert() Macro.

	void assert(int expression);

	expression can be a variable or any C expression. If expression evaluates to TRUE, assert() does nothing. 
	If expression evaluates to FALSE, assert() displays an error message on stderr (standard error stream to 
	display error messages and diagnostics) and aborts program execution.

	Since n would not have a symbol.letter field to point to that equals '\n', this line would display an error message 
	and abort the program.


1b. Given that symbol is a union type, is it ever possible for both the letter and string of t
he symbol \n to co-exist (that is, the string doesn't clobber the letter)?
---------------------------------------------------------------------------------------------------------

	This is possible in a Big Endian system, because because most significant bits are stored first.


2. To construct the Huffman code, you had to utilize both a priority queue (aka. min-heap) and a Huffman Tree, 
both of which were binary trees. For the former, you used an array representation while for the later 
you used a linked node representation. With this in mind, answer the following questions:
-------------------------------------------------------------------------------------------------------------------

2a. Would it have been easier to implement the priority queue with a linked node representation? 
Explain why this would be better or worse than the array representation.
--------------------------------------------------------------------------------------------------------------

	The Priority queue would be worse with linked nodes because it uses more memory.


2b. Would it have been easier to implement the Huffman Tree with an array representation? 
Explain why this would be better or worse than the linked node representation.
--------------------------------------------------------------------------------------------------------

	The Huffman Tree is worse with an array because the array would have lots 
	of wasted space resulting from holes.  Also using nodes is more complicated because 
	of all the swapping that takes place.

3. Analyze the results of your experiements with you huff.py Python script. What sort of compression ratios were 
you able to achieve? How does this compare to standard utilities such as gzip, bzip2, and xz?
------------------------------------------------------------------------------------------------------------------

	Based on the statistics below, it seems huff.py performs worse than all three standard utilities on average.
	Interestingly, some compression utilities were able to achieve better compression rates on different types of
	books, suggesting that the algorithms used for each are not universally superior.  

	huff.py:
		Alice...	11.ascii = 56.70%
		Tale...		98.ascii = 57.91%
		Frank...	84.ascii = 57.08%
		Heart...	219.ascii = 56.02%
		Pride...	1342.ascii = 56.77%
				Avg = ~56.7%

	gzip:
		Alice...	11.txt = 35.35%
		Tale...		98.txt = 37.56%
		Frank...	84.txt = 37.74%
		Heart...	219.txt = 39.86%
		Pride...	1342.txt = 36.42%
				Avg = ~37.5%
	
	bzip2:
		Alice...	11.txt = 28.30%
		Tale...		98.txt = 27.40%
		Frank...	84.txt = 28.15%
		Heart...	219.txt = 31.68%
		Pride...	1342.txt = 25.13%		
				Avg = ~27.9%
	
	xz:
		Alice...	11.txt = 31.14%
		Tale...		98.txt = 31.02%
		Frank...	84.txt = 31.80%
		Heart...	219.txt = 34.93%
		Pride...	1342.txt = 29.15%
				Avg = ~31.8%

