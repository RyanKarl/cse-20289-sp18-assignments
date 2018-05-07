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

# TODO: Rules for search and intermediate object files
