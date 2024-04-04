CC = gcc
FLAGS = 

TEST_FLAGS = -lcheck -lpthread -pthread -lm 

all: clean install

install:
	mkdir build && cd build && cmake .. && make

uninstall:
	rm -rf build

test:
	gcc calculator.c tests.c stack.c -lcheck -lpthread -pthread -lm -o test.out
	./test.out

clean: uninstall
	rm -rf *.o *.out *.info gcov_report

gcov_report: clean
	$(CC) $(FLAGS) -fprofile-arcs -ftest-coverage calculator.c tests.c stack.c -o test.out $(TEST_FLAGS)
	./test.out
	lcov --ignore-errors unused --ignore-errors empty -t "smartcalc.a" -o smartcalc.a.info -c -d . 
	lcov --ignore-errors unused --ignore-errors empty --extract smartcalc.a.info -o filtered.info
	genhtml --ignore-errors unused --ignore-errors empty -o gcov_report filtered.info
	rm -rf *.gcno *.gcda *.out

style:
	clang-format -style=Google -n *.[ch]
	clang-format -style=Google -n *.cpp

fix_style:
	clang-format -style=Google -i *.[ch]
	clang-format -style=Google -i *.cpp

	
dvi:
	cat text.txt

dist:
	tar -czvf smartcalc.a.tar.gz *