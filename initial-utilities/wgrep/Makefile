all: wgrep

test: wgrep
	./test-wgrep.sh

wgrep: wgrep.c
	gcc $< -std=c17 -Wall -Werror -o $@
