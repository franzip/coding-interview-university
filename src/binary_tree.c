#include "lib/binary_tree.h"

#include <assert.h>

int
main(int argc, char const *argv[]) {
    binary_tree *tree = make_binary_tree();
    assert(tree->get_node_count(tree) == 0);
    assert(tree->is_in_tree(tree, 5) == false);
    assert(tree->get_height(tree) == 0);
    assert(tree->get_max(tree) == 0);
    assert(tree->get_min(tree) == 0);
    assert(tree->is_binary_search_tree(tree) == true);

    tree->insert(tree, 5);
    tree->insert(tree, 15);
    tree->insert(tree, 1);
    tree->insert(tree, 1);
    tree->insert(tree, 15);
    tree->insert(tree, 20);
    tree->insert(tree, 11);
    tree->insert(tree, 3);

    assert(tree->get_node_count(tree) == 6);
    assert(tree->is_in_tree(tree, 34) == false);
    assert(tree->is_in_tree(tree, 15) == true);
    assert(tree->get_height(tree) == 3);
    assert(tree->get_max(tree)->value == 20);
    assert(tree->get_min(tree)->value == 1);
    assert(tree->get_successor(tree, 1000) == NULL);
    assert(tree->get_successor(tree, 15)->value == 20);
    assert(tree->is_binary_search_tree(tree) == true);
    tree->print_values(tree);

    assert(tree->delete_value(tree, 100) == -1);
    assert(tree->delete_value(tree, 5) == 0);
    assert(tree->delete_value(tree, 1) == 0);
    assert(tree->delete_value(tree, 15) == 0);
    assert(tree->delete_value(tree, 20) == 0);
    assert(tree->delete_value(tree, 20) == -1);
    assert(tree->is_in_tree(tree, 20) == false);
    assert(tree->get_node_count(tree) == 2);
    assert(tree->get_height(tree) == 2);
    assert(tree->get_max(tree)->value == 11);
    assert(tree->get_min(tree)->value == 3);
    assert(tree->get_successor(tree, 3)->value == 11);
    assert(tree->get_successor(tree, 11) == NULL);
    tree->print_values(tree);
    tree->delete_tree(tree);

    return 0;
}
