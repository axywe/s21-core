FLAGS = -Wall -Werror -Wextra
SANITIZE = -fsanitize=address -fsanitize=leak
CC = gcc


all: clean s21_math

s21_math:
	${CC} *.c -o s21_math
	./s21_math

clean:
	rm -rf s21_math
