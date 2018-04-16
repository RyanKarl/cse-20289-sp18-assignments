CC=             gcc
CFLAGS=         -g -gdwarf-2 -Wall -Werror -std=gnu99
TARGETS=        doit

all:            $(TARGETS)

# TODO: Add rule for doit

doit: doit.c 
	$(CC) $(CFLAGS) -o doit doit.c

test:
	        @$(MAKE) -sk test-all

test-all:	test-doit

test-doit:	doit
	curl -sLO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/reading11/test_doit.sh
	chmod +x test_doit.sh
	./test_doit.sh

clean:
	rm -f $(TARGETS)

.SUFFIXES:
