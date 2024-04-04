all: install
	../build/maze generate 10 10 ../build/a.txt
	../build/maze solve ../build/a.txt 0 0 9 9
	../build/maze cave caves/cave.txt 2 5 100 auto

install: uninstall
	mkdir ../build
	gcc -Wall -Werror -Wextra *.c -o ../build/maze

uninstall: style
	rm -rf ../build
	rm -rf a.out

clean: uninstall

tests: uninstall
	mkdir ../build
	mkdir ../build/tests
	gcc generator.c maze.c solver.c cave.c tests/generator_tests.c tests/solver_tests.c tests/main_tests.c tests/caves_tests.c -lcheck -o ../build/tests/maze_tests
	../build/tests/maze_tests

style:
	clang-format -style=Google -i *.c *.h tests/*.c tests/*.h
