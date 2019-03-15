GCC = gcc -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror -fprofile-arcs -ftest-coverage

FLAGS = -DJOSEPHUS

SRCS = pe10.c main.c

OBJS = $(SRCS:%.c=%.o)

all: pe10 testcase coverage

pe10: $(OBJS) 
	$(GCC) $(FLAGS) $(OBJS) -o pe10
.c.o: 
	$(GCC) $(FLAGS) -c $*.c

testcase: pe10
	./pe10 10 3 1 > case1.txt
	./pe10 10 4 2 > case2.txt
	./pe10 8 5 3 > case3.txt
	./pe10 8 9 1 > case4.txt
coverage: testcase
	gcov $(SRCS)

clean: # remove all machine generated files
	rm -f pe10 *.o *.out *gcda *gcno *gcov
