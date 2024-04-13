#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

typedef struct graph_node {
    int value;
    int weight;
    struct graph_node* next;
} graph_node;

typedef struct AdjList {
    graph_node* head;
} adj_list;

graph_node*
make_graph_node(int value, int weight) {
    graph_node* new_node = malloc(sizeof(graph_node));
    new_node->value = value;
    new_node->weight = weight;
    new_node->next = NULL;
    return new_node;
}

typedef struct GraphList graph_list;

struct GraphList {
    int vertices;
    adj_list* list;

    void (*add_edge)(graph_list*, int, int, int);
};

void
add_edge(graph_list* g, int src, int dst, int weight) {
    assert(weight >= 0);

    graph_node* dst_node = make_graph_node(dst, weight);
    dst_node->next = g->list[src].head;
    g->list[src].head = dst_node;
};

graph_list*
make_graph_list(int vertices) {
    graph_list* g = malloc(sizeof(graph_list));
    g->vertices = vertices;
    g->list = malloc(vertices * sizeof(adj_list));

    for (int i = 0; i < vertices; i++) {
        g->list[i].head = NULL;
    }

    g->add_edge = add_edge;

    return g;
};

void
_dfs_graph_list_rec_imp(graph_list* g, int vertex, bool* visited) {
    visited[vertex] = true;
    printf("%d", vertex);

    graph_node* curr = g->list[vertex].head;

    while (curr) {
        int adj = curr->value;
        if (!visited[adj]) {
            printf(" -> ");
            _dfs_graph_list_rec_imp(g, adj, visited);
        }
        curr = curr->next;
    }
}

bool*
_make_visited_list(int size) {
    bool* visited = malloc(size * sizeof(bool));
    for (int i = 0; i < size; i++) {
        visited[i] = false;
    }

    return visited;
}

void
dfs_graph_list_rec(graph_list* g, int start_vertex) {
    bool* visited = _make_visited_list(g->vertices);
    _dfs_graph_list_rec_imp(g, start_vertex, visited);

    printf("\n");
    free(visited);
}

void
_debug_node(graph_node* n) {
    while (n) {
        printf("%d", n->value);
        printf(" -> ");
        n = n->next;
    }
}

void
dfs_graph_list_stack(graph_list* g, int start_vertex) {
    bool* visited = _make_visited_list(g->vertices);
    stack* s = make_stack();
    s->push(s, start_vertex);

    while (!s->is_empty(s)) {
        int curr = s->pop(s);

        if (!visited[curr]) {
            printf("%d -> ", curr);
            visited[curr] = true;
        }

        graph_node* curr_node = g->list[curr].head;

        while (curr_node) {
            int adj = curr_node->value;
            if (!visited[adj]) {
                s->push(s, adj);
            }
            curr_node = curr_node->next;
        }
    }

    free(visited);
    free(g->list);
    free(g);
}

void
debug_graph(graph_list* g) {
    for (int i = 0; i < g->vertices; i++) {
        printf("vertex %d: ", i);
        graph_node* node = g->list[i].head;
        if (node == NULL) {
            printf("NULL\n");
            continue;
        }
        while (node) {
            printf("%d", node->value);
            node = node->next;
            if (node) {
                printf(" -> ");
            }
        }
        printf("\n");
    }
}
