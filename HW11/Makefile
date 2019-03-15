GCC = gcc -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror -fprofile-arcs -ftest-coverage

FLAGS = -DJOSEPHUS

SRCS = pe11.c main.c

OBJS = $(SRCS:%.c=%.o)

all: pe11 testcase coverage

pe11: $(OBJS) 
	$(GCC) $(FLAGS) $(OBJS) -o pe11
.c.o: 
	$(GCC) $(FLAGS) -c $*.c

testcase: pe11
	./pe11 test1.txt > case1.txt
	./pe11 test2.txt > case2.txt
	./pe11 test3.txt > case3.txt
coverage: testcase
	gcov $(SRCS)

clean: # remove all machine generated files
	rm -f pe10 *.o *.out *gcda *gcno *gcov
