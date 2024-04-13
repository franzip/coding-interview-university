#include "lib/vector.h"

#include <assert.h>

int
main(int argc, char **argv) {
    vector *vec = make_vector();
    assert(vec->length == 0);
    assert(vec->capacity == 4);
    for (int i = 0; i < 20; i++) {
        vec->push(vec, i * 3);
    }
    assert(vec->capacity == 32);
    assert(vec->length == 20);
    vec->print(vec);
    vec->insert(vec, 1, 50);
    vec->insert(vec, 10, 125);
    assert(vec->at(vec, 1) == 50);
    assert(vec->at(vec, 10) == 125);
    assert(vec->length == 22);

    vec->prepend(vec, 1000);
    vec->prepend(vec, 1000);
    vec->print(vec);
    assert(vec->length == 24);
    assert(vec->pop(vec) == 57);
    assert(vec->pop(vec) == 54);
    assert(vec->length == 22);
    assert(vec->delete (vec, 15) == 33);
    assert(vec->length == 21);

    vec->insert(vec, 10, 42);
    vec->insert(vec, 10, 42);
    vec->insert(vec, 10, 42);

    assert(vec->length == 24);
    assert(vec->at(vec, 10) == 42);
    vec->print(vec);
    vec->remove(vec, 42);
    assert(vec->at(vec, 10) != 42);
    vec->print(vec);

    assert(vec->find(vec, 125) == 15);
    assert(vec->find(vec, 1000) == 0);
    assert(vec->find(vec, 1001) == -1);
    for (int i = 0; i < 20; i++) {
        vec->pop(vec);
    }
    assert(vec->capacity == 8);
    vec->delete (vec, 0);
    vec->delete (vec, 1);
    assert(vec->capacity == 4);
    vec->print(vec);

    free(vec->items);
    free(vec);
    return 0;
}
