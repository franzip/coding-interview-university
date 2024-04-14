#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

// START HEAP
#define INITIAL_CAPACITY 8

typedef struct Tuple {
    int key;     // edge weight
    int value;   // edge label
} tuple;

typedef struct Heap heap;

struct Heap {
    tuple** items;
    int size;
    int capacity;
    void (*heapify)(heap*, int);
    void (*insert)(heap*, int, int);
    tuple* (*extract_min)(heap*);
    bool (*is_empty)(heap*);
};

void
insert_helper(heap* h, int index) {
    int parent = (index - 1) / 2;

    if (h->items[parent]->key > h->items[index]->key) {
        tuple* temp = h->items[parent];
        h->items[parent] = h->items[index];
        h->items[index] = temp;

        insert_helper(h, parent);
    }
}

void
heapify(heap* h, int index) {
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int min = index;

    if (left >= h->size || left < 0)
        left = -1;
    if (right >= h->size || right < 0)
        right = -1;

    if (left != -1 && h->items[left]->key < h->items[index]->key)
        min = left;
    if (right != -1 && h->items[right]->key < h->items[min]->key)
        min = right;

    if (min != index) {
        tuple* temp = h->items[min];
        h->items[min] = h->items[index];
        h->items[index] = temp;

        heapify(h, min);
    }
}

tuple*
extract_min(heap* h) {
    tuple* result;

    if (h->size == 0) {
        perror("Heap is empty\n");
        exit(1);
    }

    result = h->items[0];

    h->items[0] = h->items[h->size - 1];
    h->size--;
    heapify(h, 0);

    return result;
}

tuple*
make_tuple(int key, int value) {
    tuple* t = malloc(sizeof(tuple));
    t->key = key;
    t->value = value;
    return t;
}

void
_resize_heap(heap* h) {
    int new_capacity = h->capacity * 2;
    h->items = realloc(h->items, new_capacity * sizeof(tuple));
    h->capacity = new_capacity;
}

void
insert_into_heap(heap* h, int key, int value) {
    if (h->size >= h->capacity) {
        _resize_heap(h);
    }

    tuple* t = make_tuple(key, value);

    h->items[h->size] = t;
    insert_helper(h, h->size);
    h->size++;
}

bool
is_heap_empty(heap* h) {
    return h->size == 0;
}

heap*
make_heap() {
    heap* h = (heap*) malloc(sizeof(heap));
    h->size = 0;
    h->capacity = INITIAL_CAPACITY;
    h->items = malloc(h->capacity * sizeof(tuple));
    h->heapify = heapify;
    h->insert = insert_into_heap;
    h->extract_min = extract_min;
    h->is_empty = is_heap_empty;
    return h;
}

void
destroy_heap(heap* h) {
    for (int i = 0; i < h->size; i++) {
        free(h->items[i]);
    }
    free(h);
}

// END HEAP

int
get_min_node(int* distances, bool* visited, int vertices) {
    int min = INT_MAX;
    int result;

    for (int i = 0; i < vertices; i++) {
        if (!visited[i] && distances[i] <= min) {
            min = distances[i];
            result = i;
        }
    }

    return result;
}

void
dijkstra_matrix(graph_matrix* graph, int src) {
    int vertices = graph->vertices;
    int* distances = _make_distance_list(vertices);
    bool* visited = _make_bool_list(vertices);
    int* matrix = graph->matrix;

    distances[src] = 0;

    for (int i = 0; i < vertices; i++) {
        int curr = get_min_node(distances, visited, vertices);

        visited[curr] = true;

        for (int dist = 0; dist < vertices; dist++) {
            int distance = matrix[curr * vertices + dist];

            if (!distance || visited[dist]) {
                continue;
            }

            if (distances[curr] + distance < distances[dist]) {
                distances[dist] = distances[curr] + distance;
            }
        }
    }

    for (int i = 0; i < vertices; i++) {
        printf("Shortest distance from %d to %d is: %d\n", src, i,
               distances[i]);
    }

    free(distances);
    free(visited);
}

void
dijkstra_list(graph_list* graph, int src) {
    int vertices = graph->vertices;
    assert(src < vertices);
    int* distances = _make_distance_list(vertices);
    bool* visited = _make_bool_list(vertices);
    heap* h = make_heap();
    distances[src] = 0;
    tuple* t;

    h->insert(h, distances[src], src);

    while (!h->is_empty(h)) {
        t = h->extract_min(h);
        visited[t->value] = true;
        graph_node* adj = graph->list[t->value].head;
        while (adj) {
            if (!visited[adj->value]) {
                int distance = t->key + adj->weight;
                if (distance < distances[adj->value]) {
                    distances[adj->value] = distance;
                    h->insert(h, distance, adj->value);
                }
            }
            adj = adj->next;
        }
    }

    for (int i = 0; i < vertices; i++) {
        printf("Shortest distance from %d to %d is: %d\n", src, i,
               distances[i]);
    }

    free(distances);
    free(visited);
    destroy_heap(h);
}

void
minimum_spanning_tree(graph_list* graph, int src) {
    int vertices = graph->vertices;
    assert(src < vertices);
    bool* tree = _make_bool_list(vertices);
    int* distances = _make_distance_list(vertices);
    int* parent = malloc(sizeof(int) * vertices);

    for (int i = 0; i < vertices; i++) {
        parent[i] = -1;
    }

    int dist = 0;

    int vertex = src;
    distances[src] = 0;

    while (!tree[vertex]) {
        tree[vertex] = true;

        graph_node* n = graph->list[vertex].head;

        while (n) {
            int adj = n->value;

            if ((distances[adj] > n->weight) && (!tree[adj])) {
                distances[adj] = n->weight;
                parent[adj] = vertex;
            }

            n = n->next;
        }

        dist = INT_MAX;

        for (int i = 0; i < vertices; i++) {
            if (!tree[i] && dist > distances[i]) {
                dist = distances[i];
                vertex = i;
            }
        }
    }

    for (int i = 0; i < vertices; i++) {
        if (parent[i] != -1) {
            printf("Parent of %d = %d\n", i, parent[i]);
        }
    }

    free(tree);
    free(distances);
}

int
compute_in_degree(graph_node* g_node) {
    int count = 0;
    while (g_node) {
        count++;
        g_node = g_node->next;
    }

    return count;
}

void
topological_sort(graph_list* graph) {
    if (check_graph_cycle(graph, 0)) {
        perror("Graph has a cycle");
        exit(1);
    }

    int vertices = graph->vertices;
    int* in_degrees = malloc(vertices * sizeof(int));
    graph_node* node;

    for (int vertex = 0; vertex < vertices; vertex++) {
        node = graph->list[vertex].head;
        while (node) {
            in_degrees[node->value] += 1;
            node = node->next;
        }
    }

    queue* q = make_queue();
    for (int vertex = 0; vertex < vertices; vertex++) {
        if (in_degrees[vertex] == 0) {
            q->enqueue(q, vertex);
        }
    }

    printf("Topological sort results:\n");
    while (!q->empty(q)) {
        int vertex = q->dequeue(q);
        printf("%d -> ", vertex);
        node = graph->list[vertex].head;
        while (node) {
            in_degrees[node->value] -= 1;
            if (in_degrees[node->value] == 0) {
                q->enqueue(q, node->value);
            }
            node = node->next;
        }
    }
    printf("\n");
    free(in_degrees);
    free(q);
}

void
_connected_components_dfs(graph_list* graph, bool* visited, int source) {
    visited[source] = true;
    graph_node* ptr = graph->list[source].head;

    while (ptr) {
        if (!visited[ptr->value]) {
            _connected_components_dfs(graph, visited, ptr->value);
        }
        ptr = ptr->next;
    }
}

int
count_connected_components(graph_list* graph) {
    int vertices = graph->vertices;
    int count = 0;
    bool* visited = _make_bool_list(vertices);
    for (int vertex = 0; vertex < vertices; vertex++) {
        if (!visited[vertex]) {
            _connected_components_dfs(graph, visited, vertex);
            count += 1;
        }
    }

    free(visited);

    return count;
}

void
visit_dfs(graph_list* graph, int vertex, bool* visited, stack* stack) {
    visited[vertex] = true;
    graph_node* g_node;

    for (g_node = graph->list[vertex].head; g_node; g_node = g_node->next) {
        if (visited[g_node->value]) {
            continue;
        }
        visit_dfs(graph, g_node->value, visited, stack);
    }

    stack->push(stack, vertex);
}

void
collect_components_dfs(graph_list* graph, int vertex, bool* visited,
                       linkedlist* list) {
    visited[vertex] = true;
    graph_node* g_node;
    list->push_back(list, vertex);

    for (g_node = graph->list[vertex].head; g_node; g_node = g_node->next) {
        if (!visited[g_node->value]) {
            collect_components_dfs(graph, g_node->value, visited, list);
        }
    }
}

void
kosaraju(graph_list* graph) {
    int vertices = graph->vertices;
    bool* visited = _make_bool_list(vertices);
    stack* stack = make_stack();

    for (int vertex = 0; vertex < vertices; vertex++) {
        if (visited[vertex]) {
            continue;
        }
        visit_dfs(graph, vertex, visited, stack);
    }

    graph_list* reversed = make_graph_list(vertices);
    for (int vertex = 0; vertex < vertices; vertex++) {
        for (graph_node* node = graph->list[vertex].head; node;
             node = node->next) {
            reversed->add_edge(reversed, node->value, vertex, node->weight);
        }
    }

    visited = _make_bool_list(vertices);
    linkedlist* list;

    if (!stack->is_empty(stack)) {
        printf("Strongly connected components found:\n");
    }
    while (!stack->is_empty(stack)) {
        int vertex = stack->pop(stack);
        list = make_linked_list();
        if (!visited[vertex]) {
            collect_components_dfs(reversed, vertex, visited, list);
        }
        if (!list->empty(list)) {
            debug_list(list);
        }
    }

    free(visited);
    free(stack);
    free(list);
}
