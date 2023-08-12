#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_CAPACITY  8
#define MAX_LOAD_FACTOR 0.75
#define MIN_LOAD_FACTOR 0.25
#define EMPTY_VALUE     "___"

typedef struct Hashtable hashtable;

typedef struct Hash_Item {
    char *key;
    char *value;
} hash_item;

struct Hashtable {
    int count;
    int size;
    hash_item **items;
    int (*add)(hashtable *, char *, char *);
    bool (*exists)(hashtable *, char *);
    char *(*get)(hashtable *, char *);
    int (*remove)(hashtable *, char *);
};

/* djb2 */
unsigned long
hash(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

hash_item *
make_item(char *key, char *value) {
    hash_item *new_item = (hash_item *) malloc(sizeof(hash_item));
    new_item->key = (char *) malloc(strlen(key) + 1);
    new_item->value = (char *) malloc(strlen(value) + 1);
    strcpy(new_item->key, key);
    strcpy(new_item->value, value);

    return new_item;
}

int
_probe(hash_item **table_items, int start, int size) {
    int index = start;
    while (table_items[index] != NULL) {
        index = (index + 1) % size;
    }

    return index;
}

void
_resize(hashtable *table, int new_size) {
    hash_item **new_table_items = calloc(new_size, sizeof(hash_item *));

    for (int i = 0; i < new_size; i++) {
        new_table_items[i] = NULL;
    }

    for (int i = 0; i < table->size; i++) {
        if (table->items[i] != NULL &&
            strcmp(table->items[i]->key, EMPTY_VALUE) != 0) {
            int index = hash(table->items[i]->key) % new_size;
            hash_item *item = new_table_items[index];
            if (item == NULL) {
                new_table_items[index] = table->items[i];
            } else {
                new_table_items[_probe(new_table_items, index, new_size)] =
                    table->items[i];
            }
        }
    }

    free(table->items);
    table->items = new_table_items;
    table->size = new_size;
}

int
add(hashtable *table, char *key, char *value) {
    float load_factor = (table->count + 1) / (float) table->size;

    if (load_factor >= MAX_LOAD_FACTOR) {
        _resize(table, table->size * 2);
    }

    int index = hash(key) % table->size;

    hash_item *new_item = make_item(key, value);
    hash_item *current_item = table->items[index];

    if (current_item == NULL || strcmp(current_item->key, EMPTY_VALUE) == 0) {
        table->items[index] = new_item;
        table->count++;
    } else {
        if (strcmp(current_item->key, key) == 0) {
            table->items[index] = new_item;
        } else {
            // collision handling
            table->items[_probe(table->items, index, table->size)] = new_item;
            table->count++;
        }
    }

    return 0;
}

bool
exists(hashtable *table, char *key) {
    int index = hash(key) % table->size;

    while (table->items[index] != NULL) {
        if (strcmp(table->items[index]->key, key) == 0) {
            return true;
        }
        index = (index + 1) % table->size;
    }

    return false;
}

char *
get(hashtable *table, char *key) {
    int index = hash(key) % table->size;

    while (table->items[index] != NULL) {
        if (strcmp(table->items[index]->key, key) == 0) {
            return table->items[index]->value;
        }
        index = (index + 1) % table->size;
    }

    return "NOT_FOUND";
}

int
remove_item(hashtable *table, char *key) {
    float load_factor = (table->count + 1) / (float) table->size;

    if (table->size > START_CAPACITY && load_factor <= MIN_LOAD_FACTOR) {
        _resize(table, table->size / 2);
    }

    int index = hash(key) % table->size;

    while (table->items[index] != NULL) {
        if (strcmp(table->items[index]->key, key) == 0) {
            table->items[index]->key = EMPTY_VALUE;
            table->items[index]->value = EMPTY_VALUE;
            table->count--;
            return 0;
        }
        index = (index + 1) % table->size;
    }

    return -1;
}

hashtable *
make_hashtable() {
    hashtable *table = (hashtable *) malloc(sizeof(hashtable));
    table->size = START_CAPACITY;
    table->items = calloc(table->size, sizeof(hash_item *));
    table->count = 0;

    for (int i = 0; i < table->size; i++) {
        table->items[i] = NULL;
    }

    table->add = add;
    table->exists = exists;
    table->get = get;
    table->remove = remove_item;

    return table;
}
