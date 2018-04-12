CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -Werror -std=gnu99 -fPIC
LD=		gcc
LDFLAGS=	-L.
AR=		ar
ARFLAGS=	rcs
TARGETS=	duplicate search

all:		$(TARGETS)

test:		
	@$(MAKE) -sk test-all

test-all:	test-duplicate test-search

test-duplicate:	duplicate
	@curl -sLO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/homework08/test_duplicate.sh
	@chmod +x test_duplicate.sh
	@./test_duplicate.sh

test-search:	search
	@curl -sLO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/homework08/test_search.sh
	@chmod +x test_search.sh
	@./test_search.sh

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) *.o

.SUFFIXES:

# TODO: Rules for duplicate and intermediate object files

duplicate: duplicate_main.o duplicate_options.o
		$(LD) $(LDFLAGS) -o duplicate duplicate_main.o duplicate_options.o

duplicate_main.o: duplicate.h duplicate_main.c
		$(CC) $(CFLAGS) -o duplicate_main.o -c duplicate_main.c

duplicate_options.o: duplicate.h duplicate_options.c
		$(CC) $(CFLAGS) -o duplicate_options.o -c duplicate_options.c



# TODO: Rules for duplicate and intermediate object files

search: search_filter.o search_main.o search_options.o search_utilities.o search_walk.o
		$(LD) $(LDFLAGS) -o search search_main.o search_filter.o search_options.o search_utilities.o search_walk.o

search_filter.o: 
		$(CC) $(CFLAGS) -o search_filter.o -c search_filter.c		

search_main.o: 
		$(CC) $(CFLAGS) -o search_main.o -c search_main.c

search_options.o:
		$(CC) $(CFLAGS) -o search_options.o -c search_options.c

search_utilities.o:
		$(CC) $(CFLAGS) -o search_utilities.o -c search_utilities.c

search_walk.o:
		$(CC) $(CFLAGS) -o search_walk.o -c search_walk.c


