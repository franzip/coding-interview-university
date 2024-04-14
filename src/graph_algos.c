#include "lib/graph_algos.h"

#include <assert.h>
#include <stdbool.h>

void
run_dijkstra() {
    /*
                    8
                    ↑
                    | (5)
                    |
                (3) | (4)
        / --> 1 --> 6 ---> 7
       /                  |
  (2) /         |---------| (1)
     /          |
    / (1)       ↓
   0 ----> 2 ---> 3 <----|
   |      /\ (3)         |
   |     /  \            |
(5)| (3)/    \           | (1)
   ↓   /      \          |
   9←-/        --> 4 ---> 5
               (2)   (3)
   */
    graph_matrix *gm = make_graph_matrix(10);
    gm->add_edge(gm, 0, 1, 2);
    gm->add_edge(gm, 0, 2, 1);
    gm->add_edge(gm, 0, 9, 5);
    gm->add_edge(gm, 1, 6, 3);
    gm->add_edge(gm, 2, 3, 3);
    gm->add_edge(gm, 2, 4, 2);
    gm->add_edge(gm, 2, 9, 3);
    gm->add_edge(gm, 4, 5, 3);
    gm->add_edge(gm, 5, 3, 1);
    gm->add_edge(gm, 6, 8, 5);
    gm->add_edge(gm, 6, 7, 4);
    gm->add_edge(gm, 7, 3, 1);

    printf("Dijkstra using matrix:\n");
    dijkstra_matrix(gm, 0);
    printf("\n");

    graph_list *gl = make_graph_list(10);
    gl->add_edge(gl, 0, 1, 2);
    gl->add_edge(gl, 0, 2, 1);
    gl->add_edge(gl, 0, 9, 5);
    gl->add_edge(gl, 1, 6, 3);
    gl->add_edge(gl, 2, 3, 3);
    gl->add_edge(gl, 2, 4, 2);
    gl->add_edge(gl, 2, 9, 3);
    gl->add_edge(gl, 4, 5, 3);
    gl->add_edge(gl, 5, 3, 1);
    gl->add_edge(gl, 6, 8, 5);
    gl->add_edge(gl, 6, 7, 4);
    gl->add_edge(gl, 7, 3, 1);

    printf("Dijkstra using list:\n");
    dijkstra_list(gl, 0);
    printf("\n");

    destroy_graph_matrix(gm);
    destroy_graph_list(gl);
}

void
run_mst() {
    graph_list *gl = make_graph_list(10);
    gl->add_undirected_edge(gl, 0, 1, 2);
    gl->add_undirected_edge(gl, 0, 2, 1);
    gl->add_undirected_edge(gl, 0, 9, 5);
    gl->add_undirected_edge(gl, 1, 6, 3);
    gl->add_undirected_edge(gl, 2, 3, 3);
    gl->add_undirected_edge(gl, 2, 4, 2);
    gl->add_undirected_edge(gl, 2, 9, 3);
    gl->add_undirected_edge(gl, 4, 5, 3);
    gl->add_undirected_edge(gl, 5, 3, 1);
    gl->add_undirected_edge(gl, 6, 8, 5);
    gl->add_undirected_edge(gl, 6, 7, 4);
    gl->add_undirected_edge(gl, 7, 3, 1);
    printf("Minimum spaning tree: \n");
    minimum_spanning_tree(gl, 0);
    printf("\n");
    destroy_graph_list(gl);
}

void
test_cycle_detection() {
    graph_list *g = make_graph_list(3);
    g->add_edge(g, 0, 1, 1);
    g->add_edge(g, 1, 2, 1);
    g->add_edge(g, 2, 0, 1);
    assert(check_graph_cycle(g, 0) == true);
    graph_list *c = make_graph_list(3);
    c->add_edge(c, 0, 1, 1);
    c->add_edge(c, 1, 2, 1);
    assert(check_graph_cycle(c, 0) == false);
    destroy_graph_list(g);
    destroy_graph_list(c);
}

void
run_topological_sort() {
    /*
        0 ----> 1 ----> 3 ---> 5
        |              /       ↑
        |       -------        |
        ↓       ↓              |
        2 ----> 4 -------------|
    */
    graph_list *g = make_graph_list(6);
    g->add_edge(g, 0, 1, 1);
    g->add_edge(g, 0, 2, 1);
    g->add_edge(g, 1, 3, 1);
    g->add_edge(g, 2, 4, 1);
    g->add_edge(g, 3, 4, 1);
    g->add_edge(g, 3, 5, 1);
    g->add_edge(g, 4, 5, 1);

    topological_sort(g);
    destroy_graph_list(g);
}

void
run_connected_components() {
    graph_list *g = make_graph_list(6);
    assert(count_connected_components(g) == 6);
    free(g);
    /*
        0 --> 1
        |     ↑
        ↓     |
        2 ----|
                  3 <-- 4
           6      ↓     ↑
                  5 ----|
    */
    g = make_graph_list(7);
    g->add_edge(g, 0, 1, 1);
    g->add_edge(g, 0, 2, 1);
    g->add_edge(g, 2, 1, 1);
    g->add_edge(g, 3, 5, 1);
    g->add_edge(g, 5, 4, 1);
    g->add_edge(g, 4, 3, 1);
    assert(count_connected_components(g) == 3);
}

void
run_strongly_connected_components() {
    graph_list *g = make_graph_list(7);
    /*
        0 --> 1 --> 2 ----> 3 --> 4 --> 5 <--- 6
        ↑           |       ↑           |
        -------------       -------------
    */
    g->add_edge(g, 0, 1, 1);
    g->add_edge(g, 1, 2, 1);
    g->add_edge(g, 2, 0, 1);
    g->add_edge(g, 2, 3, 1);
    g->add_edge(g, 3, 4, 1);
    g->add_edge(g, 4, 5, 1);
    g->add_edge(g, 5, 3, 1);
    g->add_edge(g, 6, 5, 1);
    kosaraju(g);
}

int
main(int argc, char const *argv[]) {
    run_dijkstra();
    run_mst();
    test_cycle_detection();
    run_topological_sort();
    run_connected_components();
    run_strongly_connected_components();
}
