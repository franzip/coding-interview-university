CFLAGS = -Wall

SRC=$(wildcard *.c)

.PHONY: pretty clean all run-all binary_search binary_tree hash_map linked_list queue_array queue_list vector

pretty:
		clang-format -i *.c

clean:
		for target in $(SRC); do rm -f $$(basename "$${target}" .c); done

binary_search:
	clang $(CFLAGS) binary_search.c -o binary_search

binary_tree:
	clang $(CFLAGS) binary_tree.c -o binary_tree

hash_map:
	clang $(CFLAGS) hash_map.c -o hash_map

linked_list:
	clang $(CFLAGS) linked_list.c -o linked_list

queue_array:
	clang $(CFLAGS) queue_array.c -o queue_array

queue_list:
	clang $(CFLAGS) queue_list.c -o queue_list

vector:
	clang $(CFLAGS) vector.c -o vector

all:
		for target in $(SRC); do clang $(CFLAGS) $$target -o $$(basename "$${target}" .c); done

run-all: all
		for target in $(SRC); do ./$$(basename "$${target}" .c); done

