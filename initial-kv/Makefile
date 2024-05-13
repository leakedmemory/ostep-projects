all: kv

test: kv
	@rm -f ./kv.db
	./test-kv.sh

kv: kv.c
	gcc $< -std=c17 -Wall -Werror -o $@
