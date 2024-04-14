#include "lib/graph.h"

void
test_graph_list() {
    /*

      /---> 1---> 6
     /
    0---> 2 ---> 3 <--------
           \               |
            \              |
             ----> 4 ----> 5
    */
    graph_list *g = make_graph_list(7);
    g->add_edge(g, 0, 1, 1);
    g->add_edge(g, 1, 6, 1);
    g->add_edge(g, 0, 2, 1);
    g->add_edge(g, 2, 3, 1);
    g->add_edge(g, 2, 4, 1);
    g->add_edge(g, 4, 5, 1);
    g->add_edge(g, 5, 3, 1);

    debug_graph_list(g);
    dfs_graph_list_rec(g, 0);
    dfs_graph_list_stack(g, 0);
    bfs_graph_list(g, 0);

    destroy_graph_list(g);
}

void
test_graph_matrix() {
    /*
      /----> 4 ---> 5
     /       ↑      ↑
    0------> 1 ---> 2 ---> 6
     \
      \---> 3
    */

    graph_matrix *g = make_graph_matrix(7);
    g->add_edge(g, 0, 1, 1);
    g->add_edge(g, 1, 2, 1);
    g->add_edge(g, 2, 6, 1);
    g->add_edge(g, 0, 3, 1);
    g->add_edge(g, 0, 4, 1);
    g->add_edge(g, 4, 5, 1);
    g->add_edge(g, 1, 4, 1);
    g->add_edge(g, 2, 5, 1);

    debug_graph_matrix(g, false);

    dfs_graph_matrix_rec(g, 0);
    dfs_graph_matrix_stack(g, 0);
    bfs_graph_matrix(g, 0);

    destroy_graph_matrix(g);
}

int
main(int argc, char const *argv[]) {
    test_graph_list();
    test_graph_matrix();
}
