Homework 05: Processing Data
==================================

By: Ryan Karl


1) Describe how you implemented the hulk.py script. In particular, briefly discuss:
------------------------------------------------------------------------------------------------


1a) How you generated all the candidate password combinations.

	First, I used a generator with a yield statement in my permutations function to recursively generate all 
of the possible permutations of the specified length using the specified alphabet.  I concatenated various 
values of the alphabet to increase the length when neccessary.  I used a generator comprehension to add prefixes
to the permutations if a customized attack was desired by the user.  


1b) How you filtered the candidates to only contain valid passwords.

	To filter the candidates to only contain valid passwords I then used a list comprehension to 
build a list of values containing valid sha1sums found within the file contatining the hashes.  Note a conditional
statement is used in the list comprehension to verify the password is valid.  This computes all password 
permutations of a given length that are found inside the hashes file.  


1c) How you handled processing on multiple cores.

	To allow for processing on multiple cores, I first used an if statement to verify the user specified
to use more than one core and that the length of the passsword was greater than one.  I then used thefunctools.partial 
function to curry the arguments to enable me to use the he multiprocessing.Pool object, which only allows passing
one argument to the function.  I then used itertools.chain.from_iterable along with imap to distribute the work.


1d) How you verified that your code works properly.

	To verify my code worked properly I made use of test_hulk.sh, which returned a 7/7 after much trial and error.
Furthermore, the embedded doctests greatly aided my evaluation of the coreectness of the individual functions within the
program.  Lastly, simply running the program allowed me to verify it worked properly, as it successfully returned 
reasonable values consistently.


2) Complete the following table for passwords of length 5:
--------------------------------------------------------------------------------------------------

---------------------------------------
|   Processes	|   Real Time (min.)   |
|--------------------------------------
|     1	        |      3:53.08         |
|--------------------------------------
|     2	        |      1:52.50         |
|--------------------------------------
|     4	        |      0:42.19         |
|--------------------------------------
|     6	        |      0:26.87         |
|--------------------------------------
|     8	        |      0:22.66         |
|--------------------------------------

2a) How does the number of processes utilized affect the amount of time required to crack passwords?

	As we increase the number of processes, the amount of time needed to crack the passwords decreases substantially,
as it takes almost 4 minutes with just one process, but only about 20 seconds with eight.  Generally speaking, the amount of 
time tends to decrease by a factor of how many cores are used, indicating that this program is highly parallelizable.
Of course, it is important to note that eventually adding more cores will not speedup the completion of the program due
to the overhead incurred, so it is important to find the sweet spot for the number of cores (Amdahl's law may help).


3) From your experience in this project and recalling your Discrete Math knowledge, what would make a password more difficult to brute-force: more complex alphabet or longer password? Explain.
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	It is more difficult to brute-force a longer password, than one that uses a complex alphabet, as the number of permutations 
one must check grows substantially faster as the length increases, as compared to the number of characters used, as we essentially
take the number of characters in the alphabet raised to the length of the password to calculate the number of permutations to check.  
We can test this using hulk.py, and note that the time required to brute-force passwords with longer length grows at a rate that is 
significantly higher than the rate of time associated with more complex alphabets.

