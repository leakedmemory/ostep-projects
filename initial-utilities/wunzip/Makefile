all: wunzip

test: wunzip
	./test-wunzip.sh

wunzip: wunzip.c
	gcc $< -std=c17 -Wall -Werror -o $@
