CC=             gcc
CFLAGS=         -g -gdwarf-2 -Wall -Werror -std=gnu99
TARGETS=        ncat

all:            $(TARGETS)

ncat: ncat.c
	$(CC) $(CFLAGS) -o ncat ncat.c

# TODO: Add rule for ncat

test:
	        @$(MAKE) -sk test-all

test-all:	test-ncat

test-ncat:	ncat
	curl -sLO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/reading12/test_ncat.sh
	chmod +x test_ncat.sh
	./test_ncat.sh

clean:
	rm -f $(TARGETS)

.SUFFIXES:
