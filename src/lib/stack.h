#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack stack;
typedef struct Node node;

struct Node {
    int val;
    node* next;
};

struct Stack {
    node* top;

    void (*push)(stack*, int);
    int (*pop)(stack*);
    int (*peek)(stack*);
    bool (*is_empty)(stack*);
};

node*
make_node(int val) {
    node* n = malloc(sizeof(node));
    n->val = val;
    n->next = NULL;
    return n;
}

void
push(stack* s, int val) {
    node* n = make_node(val);

    n->next = s->top;
    s->top = n;
}

int
pop(stack* s) {
    if (s->is_empty(s)) {
        perror("Stack is empty");
        exit(1);
    }

    node* temp;

    temp = s->top;
    int val = temp->val;
    s->top = s->top->next;
    free(temp);

    return val;
}

bool
is_empty(stack* s) {
    return s->top == NULL;
}

int
peek(stack* s) {
    if (s->is_empty(s)) {
        return s->top->val;
    } else {
        perror("Stack is empty");
        exit(1);
    }
}

void
debug_stack(stack* s) {
    node* n = s->top;

    if (!n) {
        printf("Stack is empty\n");
        return;
    } else {
        printf("Stack: [");
    }

    while (n) {
        printf("%d", n->val);
        if (n->next) {
            printf(", ");
        }
        n = n->next;
    }
    printf("]\n");
}

stack*
make_stack() {
    stack* s = (stack*) malloc(sizeof(stack));

    s->push = push;
    s->pop = pop;
    s->is_empty = is_empty;
    s->peek = peek;

    return s;
}
