MKDIR_P := mkdir -p
BIN_DIR := ./bin
QT_DIR = /opt/homebrew/opt/qt

all: install
	./bin/launcher

install:
	@$(MKDIR_P) $(BIN_DIR)
	gcc make/launcher.c -o bin/launcher
	$(MAKE) -C make install
	cd bin && cmake ../make -B ./ && cmake --build . --target s21_snake

uninstall:
	rm -rf bin/*

clean:
	rm -rf bin/*
	cd make && $(MAKE) clean

dvi:
	open doc/index.html

dist: clean
	tar -czvf tetris.tar.gz . makefile

test:
	cd bin && cmake ../make -B ./ && cmake --build . --target s21_snake_tests && ./s21_snake_tests
	$(MAKE) -C make test

style:
	clang-format --style=google -i brick_game/*/*.[c|cpp|h] make/*.[c|cpp|h] src/*.[c|cpp|h] tests/*.[c|cpp|h] ui/*.[c|cpp|h] gui/*/*.[c|cpp|h]

style-test:
	clang-format --style=google -i brick_game/*/*.[ch] make/*.[ch] src/*.[ch] tests/*.[ch] ui/*.[ch] gui/*/*.[ch] brick_game/*/*.cpp make/*.cpp src/*.cpp tests/*.cpp ui/*.cpp gui/*/*.cpp
