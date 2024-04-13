#include "lib/graph.h"

void
test_graph_list() {
    /*
            0
           / \
          x   x
          1   2
             / \
            x   \
            3    x
            x    4
             \   |
              \  x
               --5
    */
    graph_list *g = make_graph_list(5);
    g->add_edge(g, 0, 1, 1);
    g->add_edge(g, 0, 2, 1);
    g->add_edge(g, 2, 3, 1);
    g->add_edge(g, 2, 4, 1);
    g->add_edge(g, 4, 5, 1);
    g->add_edge(g, 5, 3, 1);

    dfs_graph_list_rec(g, 0);
    debug_graph(g);
    dfs_graph_list_stack(g, 0);
}

int
main(int argc, char const *argv[]) {
    test_graph_list();
}
