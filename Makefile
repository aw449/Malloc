COMPILER = gcc
FLAGS = -Wall -Werror -g
OBJECTS = mymalloc.o TestCase1.o FragTest.o

all: $(OBJECTS)
	$(COMPILER) $(CCFLAGS) mymalloc.o TestCase1.o  -o mymalloc

test1: mymalloc.o TestCase1.o
	$(COMPILER) $(CCFLAGS) mymalloc.o TestCase1.o  -o mymalloc

testf: mymalloc.o FragTest.o
	$(COMPILER) $(CCFLAGS) mymalloc.o FragTest.o  -o mymalloc

mymalloc.o: mymalloc.c mymalloc.h
	$(COMPILER) $(FLAGS) -c mymalloc.c

TestCase1.o: TestCase1.c
	$(COMPILER) $(FLAGS) -c TestCase1.c
FragTest.o: FragTest.c
	$(COMPILER) $(FLAGS) -c FragTest.c

clean:
	rm -f mymalloc
	rm -f *.o
