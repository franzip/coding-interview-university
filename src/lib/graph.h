#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue_list.h"
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
typedef struct GraphMatrix graph_matrix;

struct GraphList {
    int vertices;
    adj_list* list;

    void (*add_edge)(graph_list*, int, int, int);
    void (*add_undirected_edge)(graph_list*, int, int, int);
};

struct GraphMatrix {
    int vertices;
    int* matrix;

    void (*add_edge)(graph_matrix*, int, int, int);
};

void
add_edge_to_list(graph_list* g, int src, int dst, int weight) {
    assert(weight >= 0);
    assert(src != dst);

    graph_node* dst_node = make_graph_node(dst, weight);
    dst_node->next = g->list[src].head;
    g->list[src].head = dst_node;
};

void
add_undirected_edge_to_list(graph_list* g, int v1, int v2, int weight) {
    assert(weight >= 0);
    assert(v1 != v2);

    graph_node* new_node = make_graph_node(v2, weight);
    new_node->next = g->list[v1].head;
    g->list[v1].head = new_node;

    new_node = make_graph_node(v1, weight);
    new_node->next = g->list[v2].head;
    g->list[v2].head = new_node;
}

graph_list*
make_graph_list(int vertices) {
    graph_list* g = malloc(sizeof(graph_list));
    g->vertices = vertices;
    g->list = malloc(vertices * sizeof(adj_list));

    for (int i = 0; i < vertices; i++) {
        g->list[i].head = NULL;
    }

    g->add_edge = add_edge_to_list;
    g->add_undirected_edge = add_undirected_edge_to_list;

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
_make_bool_list(int size) {
    bool* visited = malloc(size * sizeof(bool));
    for (int i = 0; i < size; i++) {
        visited[i] = false;
    }

    return visited;
}

int*
_make_distance_list(int size) {
    int* distance = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        distance[i] = INT_MAX;
    }

    return distance;
}

void
dfs_graph_list_rec(graph_list* g, int start_vertex) {
    printf("DFS: ");
    bool* visited = _make_bool_list(g->vertices);
    _dfs_graph_list_rec_imp(g, start_vertex, visited);

    printf("\n");
    free(visited);
}

void
dfs_graph_list_stack(graph_list* g, int start_vertex) {
    printf("DFS: ");
    bool* visited = _make_bool_list(g->vertices);
    stack* s = make_stack();
    s->push(s, start_vertex);

    while (!s->is_empty(s)) {
        int curr = s->pop(s);

        if (!visited[curr]) {
            printf("%d", curr);
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

        if (!s->is_empty(s)) {
            printf(" -> ");
        }
    }

    printf("\n");
    free(visited);
    free(s);
}

void
bfs_graph_list(graph_list* g, int start_vertex) {
    printf("BFS: ");
    bool* visited = _make_bool_list(g->vertices);
    queue* q = make_queue();

    q->enqueue(q, start_vertex);
    visited[start_vertex] = true;

    while (!q->empty(q)) {
        int curr = q->dequeue(q);

        printf("%d", curr);

        graph_node* node = g->list[curr].head;

        while (node) {
            int adj = node->value;
            if (!visited[adj]) {
                q->enqueue(q, adj);
                visited[adj] = true;
            }
            node = node->next;
        }

        if (!q->empty(q)) {
            printf(" -> ");
        }
    }

    free(visited);
    free(q);
    printf("\n");
}

void
debug_graph_list(graph_list* g) {
    for (int vertex = 0; vertex < g->vertices; vertex++) {
        printf("vertex %d: ", vertex);
        graph_node* node = g->list[vertex].head;
        if (node == NULL) {
            printf("NULL\n");
            continue;
        }
        while (node) {
            printf("(node: %d, weight: %d)", node->value, node->weight);
            node = node->next;
            if (node) {
                printf(" -> ");
            }
        }
        printf("\n");
    }
}

void
add_edge_to_matrix(graph_matrix* g, int src, int dst, int weight) {
    assert(weight >= 0);
    assert(src != dst);
    assert(src < g->vertices);
    assert(dst < g->vertices);

    int cols = g->vertices;

    g->matrix[src * cols + dst] = weight;
}

void
debug_graph_matrix(graph_matrix* g, bool raw) {
    int vertices = g->vertices;

    if (raw) {
        for (int row = 0; row < vertices; row++) {
            printf("[");
            for (int col = 0; col < vertices; col++) {
                printf("%d", g->matrix[row * vertices + col]);
                if (col != vertices - 1) {
                    printf(", ");
                }
            }
            printf("]\n");
        }
        printf("\n");
        return;
    }

    for (int vertex = 0; vertex < vertices; vertex++) {
        printf("vertex %d: ", vertex);
        bool is_empty = true;

        for (int target = 0; target < vertices; target++) {
            int weight = g->matrix[vertex * vertices + target];
            if (weight != 0) {
                is_empty = false;
                printf("(node: %d, weight: %d) -> ", target, weight);
            }
        }

        if (is_empty) {
            printf("NULL");
        }
        printf("\n");
    }
}

graph_matrix*
make_graph_matrix(int vertices) {
    graph_matrix* graph = malloc(sizeof(graph_matrix));
    graph->vertices = vertices;
    int* matrix = malloc(vertices * vertices * sizeof(int));
    for (int i = 0; i < vertices * vertices; i++) {
        matrix[i] = 0;
    }

    graph->matrix = matrix;
    graph->add_edge = add_edge_to_matrix;

    return graph;
}

void
_dfs_graph_matrix_rec_imp(graph_matrix* g, int vertex, bool* visited) {
    int vertices = g->vertices;
    visited[vertex] = true;
    printf("%d", vertex);
    for (int i = 0; i < vertices; i++) {
        int adj = i;
        int weight = g->matrix[vertex * vertices + adj];
        if (weight != -1 && !visited[adj]) {
            printf(" -> ");
            _dfs_graph_matrix_rec_imp(g, adj, visited);
        }
    }
}

void
dfs_graph_matrix_rec(graph_matrix* g, int start_vertex) {
    printf("DFS: ");
    bool* visited = _make_bool_list(g->vertices);
    _dfs_graph_matrix_rec_imp(g, start_vertex, visited);
    free(visited);
    printf("\n");
}

void
dfs_graph_matrix_stack(graph_matrix* g, int start_vertex) {
    printf("DFS: ");
    bool* visited = _make_bool_list(g->vertices);
    stack* s = make_stack();
    int vertices = g->vertices;

    s->push(s, start_vertex);

    while (!s->is_empty(s)) {
        int curr = s->pop(s);

        if (!visited[curr]) {
            printf("%d -> ", curr);
            visited[curr] = true;
        }

        for (int i = 0; i < vertices; i++) {
            int adj = i;
            int weight = g->matrix[curr * vertices + i];

            if (weight != -1 && !visited[adj]) {
                s->push(s, adj);
            }
        }
    }

    free(visited);
    free(s);
    printf("\n");
}

bool
check_graph_cycle_imp(graph_list* g, int vertex, bool* visited, bool* stack) {
    if (stack[vertex]) {
        return true;
    }

    if (visited[vertex]) {
        return false;
    }

    visited[vertex] = true;
    stack[vertex] = true;

    graph_node* adj = g->list[vertex].head;

    while (adj) {
        if (check_graph_cycle_imp(g, adj->value, visited, stack)) {
            return true;
        }
        adj = adj->next;
    }

    stack[vertex] = false;

    return false;
}

bool
check_graph_cycle(graph_list* graph, int src) {
    int vertices = graph->vertices;
    bool* visited = _make_bool_list(vertices);
    bool* stack = _make_bool_list(vertices);

    for (int vertex = 0; vertex < vertices; vertex++) {
        if (check_graph_cycle_imp(graph, vertex, visited, stack)) {
            return true;
        }
    }

    return false;
}

void
bfs_graph_matrix(graph_matrix* g, int start_vertex) {
    printf("BFS: ");
    bool* visited = _make_bool_list(g->vertices);
    queue* q = make_queue();
    int vertices = g->vertices;

    q->enqueue(q, start_vertex);
    visited[start_vertex] = true;

    while (!q->empty(q)) {
        int curr = q->dequeue(q);

        printf("%d", curr);

        for (int i = 0; i < vertices; i++) {
            int adj = i;
            int weight = g->matrix[vertices * curr + i];

            if (weight != -1 && !visited[adj]) {
                q->enqueue(q, adj);
                visited[adj] = true;
            }
        }

        if (!q->empty(q)) {
            printf(" -> ");
        }
    }

    free(visited);
    free(q);
    printf("\n");
}

void
destroy_graph_list(graph_list* g) {
    for (int i = 0; i < g->vertices; i++) {
        graph_node* ptr = g->list[i].head;
        graph_node* next;
        while (ptr) {
            next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }
    free(g);
}

void
destroy_graph_matrix(graph_matrix* g) {
    free(g->matrix);
    free(g);
}
