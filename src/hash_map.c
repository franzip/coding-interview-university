#include "lib/hash_map.h"

#include <assert.h>

void
debug(hashtable *table) {
    printf("size %d, taken %d, load factor: %f\n", table->size, table->count,
           (table->count + 1) / (float) table->size);
    printf("{\n");
    for (int i = 0; i < table->size; i++) {
        if (table->items[i] != NULL) {
            bool removed = strcmp(table->items[i]->key, EMPTY_VALUE) == 0;
            printf("\tindex %i: %s -> %s\n", i,
                   removed ? "REMOVED" : table->items[i]->key,
                   removed ? "REMOVED" : table->items[i]->value);
        }
    }
    printf("}\n\n");
}

int
main(int argc, char **argv) {
    hashtable *table = make_hashtable();
    assert(strcmp(table->get(table, "123"), "NOT_FOUND") == 0);
    table->add(table, "foo", "bar");
    table->add(table, "bar", "foo");
    table->add(table, "john", "doe");
    table->add(table, "crazy", "baz");
    assert(strcmp(table->get(table, "crazy"), "baz") == 0);
    table->add(table, "crazy", "bar");
    assert(strcmp(table->get(table, "crazy"), "bar") == 0);
    assert(table->count == 4);
    assert(table->size == 8);
    table->add(table, "123", "baz");
    // doubles
    table->add(table, "456", "ba12");
    assert(table->count == 6);
    assert(table->size == 16);
    debug(table);

    table->add(table, "789", "ba12");
    table->add(table, "random", "ba12");
    table->add(table, "foobar", "ba12");
    table->add(table, "barfoo", "ba12");
    assert(table->exists(table, "barfoo") == 1);
    assert(table->remove(table, "nonexisting") == -1);
    assert(table->remove(table, "barfoo") == 0);
    assert(table->exists(table, "barfoo") == 0);
    debug(table);

    table->remove(table, "foo");
    table->remove(table, "bar");
    table->remove(table, "john");
    table->remove(table, "crazy");
    table->remove(table, "123");
    table->remove(table, "456");
    // shrinks
    table->remove(table, "789");
    debug(table);
    assert(table->count == 2);
    assert(table->size == 8);
    table->remove(table, "random");
    debug(table);
    assert(table->count == 1);
    assert(table->size == 8);
    return 0;
}
