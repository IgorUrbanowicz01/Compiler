FLAGS := -g -Wall -std=gnu99 -ggdb

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

.PHONY = all clean cleanall

all: test2

test1: test.c
	gcc  $(FLAGS) -o main addOperation.c test.c ../codeGen/code.c ../codeGen/registerHandler.c

test2: test2.c
	gcc  $(FLAGS) -o main test2.c ../codeGen/code.c ../codeGen/registerHandler.c ../expr.c callOperation.c addOperation.c

clean:
	@rm -f *.o
	@rm -f *.gch
	@rm -f parser.c scanner.c
	@rm -f parse.output
	@rm -f *_tests/*_tests/*.out
	@rm -f main