COMPILER = gcc
FLAGS = -Wall -Werror -g

all: clean  mymalloc

mymalloc: mymalloc.c mymalloc.h
	$(COMPILER) $(FLAGS) mymalloc.c -o mymalloc

clean:
	rm -f mymalloc
