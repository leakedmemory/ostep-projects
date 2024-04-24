all: wcat

test: wcat
	./test-wcat.sh

wcat: wcat.c
	gcc $< -std=c17 -Wall -Werror -o $@
