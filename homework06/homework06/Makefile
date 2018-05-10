CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.
AR=		ar
ARFLAGS=	rcs

TARGETS=	libstr.a \
		libstr.so \
		str-static \
		str-dynamic

all:		$(TARGETS)

test:		
	@$(MAKE) -sk test-all
	
test-all:	test-libstr test-str

test-libstr:	libstr.so test_libstr.py
	curl -sLO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/homework06/test_libstr.py
	chmod +x test_libstr.py
	./test_libstr.py -v

test-str:	str-static str-dynamic test_str.sh
	curl -sLO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/homework06/test_str.sh
	chmod +x test_str.sh
	./test_str.sh

clean:
	rm -f $(TARGETS) *.o

# TODO: Add rules for libstr.a libstr.so

libstr.a:	library.o
	$(AR) $(ARFLAGS) libstr.a library.o

libstr.so:	library.o
	$(LD) $(LDFLAGS) -shared -o libstr.so library.o

library.o:  library.c
	$(CC) $(CFLAGS) -fPIC -c -o library.o library.c
# TODO: Add rules for str-dynamic str-static

str-dynamic: libstr.so main.o
	$(LD) $(LDFLAGS) -o str-dynamic main.o -lstr

str-static: libstr.a main.o
	$(LD) $(LDFLAGS) -static -o str-static main.o -lstr

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c 

