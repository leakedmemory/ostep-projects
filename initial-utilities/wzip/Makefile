all: wzip

test: wzip
	./test-wzip.sh

wzip: wzip.c
	gcc $< -std=c17 -Wall -Werror -o $@
