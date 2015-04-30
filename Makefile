COMPILER = gcc
FLAGS = -Wall -Werror -g
OBJECTS = mymalloc.o TestCase1.o FragTest.o Node.o sorted-list.o

all: $(OBJECTS)
	$(COMPILER) $(CCFLAGS) mymalloc.o TestCase1.o  -o mymalloc
	$(COMPILER) $(CCFLAGS) mymalloc.o FragTest.o  -o mymallocfrag
	ar -rcs libsl.a Node.o sorted-list.o
	$(COMPILER) $(CCFLAGS) mymalloc.o  pa2_test.o -L libsl.a -o mymallocedlist


test1: mymalloc.o TestCase1.o
	$(COMPILER) $(CCFLAGS) mymalloc.o TestCase1.o  -o mymalloc

testf: mymalloc.o FragTest.o
	$(COMPILER) $(CCFLAGS) mymalloc.o FragTest.o  -o mymallocfrag

testsl: mymalloc.o Node.o sorted-list.o
	ar -rcs libsl.a Node.o sorted-list.o
	$(COMPILER) $(CCFLAGS) mymalloc.o  $@ $^ -o pa2_test

mymalloc.o: mymalloc.c mymalloc.h
	$(COMPILER) $(FLAGS) -c mymalloc.c

TestCase1.o: TestCase1.c
	$(COMPILER) $(FLAGS) -c TestCase1.c

FragTest.o: FragTest.c
	$(COMPILER) $(FLAGS) -c FragTest.c

Node.o: Node.c Node.h
	$(COMPILER) $(CCFLAGS) -c Node.c

sorted-list.o: sorted-list.c sorted-list.h
	$(COMPILER) $(CCFLAGS) -c sorted-list.c



clean:
	rm libsl.a
	rm pa2_test
	rm -f mymalloc
	rm -f mymallocfrag
	rm -f mymallocedlist
	rm -f *.o
clean_test1:
	rm mymalloc
	rm -f *.o
clean_testf: 
	rm mymallocfrag
	rm -f *.o
clean_testsl:
	rm pa2_test
	rm -f *.o
	rm libsl.a
