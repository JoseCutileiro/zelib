CC=gcc
CFLAGS=-Wall -Wextra -Werror -ansi -pedantic -g
all:: soma
	$(MAKE) $(MFLAGS) -C tests
soma: soma.c
clean::
	rm -f soma a.out *.o core tests/*.diff