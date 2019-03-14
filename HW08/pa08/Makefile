GCC = gcc -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror -fprofile-arcs -ftest-coverage

#FLAGS = -DCDOUBLE -DCVID

SRCS = pa08.c main.c

OBJS = $(SRCS:%.c=%.o)


pa08: $(OBJS) 
	$(GCC) $(OBJS) -o pa08
.c.o: 
	$(GCC) -c $*.c

testall: testcase

testcase: pa08
	./pa08 -D 0 2 3 | sort > test_case_Double1.txt
	diff test_case_Double1.txt outSortedDouble.txt
	./pa08 -D 4 9 5 | sort > test_case_Double2.txt
	diff test_case_Double2.txt outSortedDouble2.txt
	./pa08 -D 3 6 4 | sort > test_case_Double3.txt
	diff test_case_Double3.txt outSortedDouble3.txt
	./pa08 -D 0 1 4 | sort > test_case_Double4exp.txt
	#diff test_case_Double4.txt test_case_Double4exp.txt
	./pa08 -D 5 6 2 | sort > test_case_Double5exp.txt
	#diff test_case_Double5.txt test_case_Double5exp.txt
	./pa08 -D 0 2 8 | sort > test_case_Double6exp.txt
	#diff test_case_Double6.txt test_case_Double6exp.txt
	./pa08 -D 4 4 4 | sort > test_case_Double7exp.txt
	#diff test_case_Double7.txt test_case_Double7exp.txt
	./pa08 -D 1 2 3 | sort > test_case_Double8exp.txt
	#diff test_case_Double8.txt test_case_Double8exp.txt
	./pa08 -D 9 8 7 | sort > test_case_Double9exp.txt
	#diff test_case_Double4.txt test_case_Double4exp.txt
	./pa08 -VID a b C D 1 3 2 | sort > test_case_VID.txt
	diff test_case_VID.txt outSortedVID.txt
coverage: testcase
	gcov $(SRCS)

clean: # remove all machine generated files
	rm -f pa08 *.o *.out *gcda *gcno *gcov
