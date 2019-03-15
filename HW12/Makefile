GCC = gcc -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror -fprofile-arcs -ftest-coverage

FLAGS = -DJOSEPHUS

SRCS = pa12.c main.c

OBJS = $(SRCS:%.c=%.o)

all: pa12 testcase coverage

pa12: $(OBJS) 
	$(GCC) $(FLAGS) $(OBJS) -o pa12
.c.o: 
	$(GCC) $(FLAGS) -c $*.c

testcase: pa12
	./pa12 -J 10 3 1 > out1.txt
	./pa12 -J 10 4 2 > out2.txt
	./pa12 -J 8 5 3 > out3.txt
coverage: testcase
	gcov $(SRCS)

clean: # remove all machine generated files
	rm -f pe10 *.o *.out *gcda *gcno *gcov
