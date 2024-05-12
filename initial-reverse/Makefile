all: reverse

test: reverse
	./test-reverse.sh

reverse: reverse.c
	gcc $< -std=c17 -Wall -Werror -o $@
