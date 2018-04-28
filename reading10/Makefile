CC=             gcc
CFLAGS=         -g -gdwarf-2 -Wall -Werror -std=gnu99
TARGETS=        walk

all:            $(TARGETS)

# TODO: Add rule for walk

walk:walk.c
	$(CC) $(CFLAGS) -o walk walk.c

test:
	        @$(MAKE) -sk test-all

test-all:	test-walk

test-walk:	walk
	curl -sLO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/reading10/test_walk.sh
	curl -sLO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/reading10/walk.py
	chmod +x test_walk.sh walk.py
	./test_walk.sh

clean:
	rm -f $(TARGETS)

.SUFFIXES:
