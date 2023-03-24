FLAGS := -g -Wall -std=gnu99 -ggdb

SOURCES = $(wildcard *.c codeGen/*.c operations/addOperation.c operations/callOperation.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.c=.o)

.PHONY = all clean cleanall

build: gramar all

all: gramar main.c
	gcc  $(FLAGS) -o kompilator $(SOURCES) 


gramar: parser.bison scanner.flex
	bison -v -d -o parser.c -d parser.bison
	flex -o scanner.c scanner.flex


clean:
	@rm -f *.o
	@rm -f *.gch
	@rm -f parser.c scanner.c
	@rm -f parse.output
	@rm -f *_tests/*_tests/*.out
	@rm -f main
	@rm -f out
	@rm -f kompilator

test: test.sh
	./test.sh