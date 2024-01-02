#define max(a, b)               \
    ({                          \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a > _b ? _a : _b;      \
    })

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct BinaryTreeNode binary_tree_node;

struct BinaryTreeNode {
    binary_tree_node *parent;
    binary_tree_node *left;
    binary_tree_node *right;
    int value;
};

binary_tree_node *
_make_node(int value) {
    binary_tree_node *node =
        (binary_tree_node *) malloc(sizeof(binary_tree_node));
    node->value = value;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void
_destroy_node(binary_tree_node *node) {
    free(node);
}

typedef struct BinaryTree binary_tree;

struct BinaryTree {
    binary_tree_node *root;
    size_t node_count;
    int (*get_node_count)(binary_tree *);
    void (*insert)(binary_tree *, int);
    bool (*is_in_tree)(binary_tree *, int);
    bool (*is_binary_search_tree)(binary_tree *);
    int (*get_height)(binary_tree *);
    int (*delete_value)(binary_tree *, int);
    binary_tree_node *(*get_min)(binary_tree *);
    binary_tree_node *(*get_max)(binary_tree *);
    binary_tree_node *(*get_successor)(binary_tree *, int);
    void (*print_values)(binary_tree *);
    void (*print)(binary_tree *);
    void (*delete_tree)(binary_tree *);
};

void
_print(binary_tree_node *node, int level) {
    if (node == NULL)
        return;

    for (int i = 0; i < level; i++) {
        printf(i == level - 1 ? "|-" : "  ");
    }
    printf("%d\n", node->value);

    _print(node->right, level + 1);
    _print(node->left, level + 1);
}

void
print(binary_tree *tree) {
    _print(tree->root, 0);
}

void
_print_node(binary_tree_node *node) {
    printf("%d ", node->value);
}

void
_traverse(binary_tree_node *node, void (*cb)(binary_tree_node *)) {
    if (node != NULL) {
        _traverse(node->left, cb);
        cb(node);
        _traverse(node->right, cb);
    }
}

bool
_is_empty_tree(binary_tree *tree) {
    return tree->root == NULL;
}

binary_tree_node *
_insert(binary_tree *tree, binary_tree_node *node, binary_tree_node *prev,
        int value) {
    if (node == NULL) {
        tree->node_count++;
        return _make_node(value);
    }

    if (node->value < value) {
        node->right = _insert(tree, node->right, node, value);
        node->right->parent = node;
    } else if (node->value > value) {
        node->left = _insert(tree, node->left, node, value);
        node->left->parent = node;
    }

    return node;
}

binary_tree_node *
_find_node(binary_tree_node *node, int value) {
    if (node == NULL) {
        return NULL;
    }

    if (node->value == value) {
        return node;
    }

    return _find_node(node->value > value ? node->left : node->right, value);
}

void
print_values(binary_tree *tree) {
    _traverse(tree->root, _print_node);
    printf("\n");
}

void
insert(binary_tree *tree, int value) {
    if (_is_empty_tree(tree)) {
        tree->root = _make_node(value);
        tree->node_count++;
        return;
    }

    _insert(tree, tree->root, NULL, value);
}

binary_tree_node *
_get_max(binary_tree_node *node) {
    while (node->right != NULL) {
        node = node->right;
    }

    return node;
}

binary_tree_node *
_get_min(binary_tree_node *node) {
    if (node == NULL) {
        return NULL;
    }

    while (node->left != NULL) {
        node = node->left;
    }

    return node;
}

void
_detach_from_parent(binary_tree_node *node) {
    if (node->parent == NULL) {
        return;
    }

    if (node->parent->left == node) {
        node->parent->left = NULL;
    } else if (node->parent->right == node) {
        node->parent->right = NULL;
    }

    node->left = node->right = node->parent = NULL;
    free(node);
}

binary_tree_node *
_get_successor(binary_tree_node *node) {
    return _get_min(node->right);
}

binary_tree_node *
get_successor(binary_tree *tree, int value) {
    binary_tree_node *node = _find_node(tree->root, value);

    if (node == NULL) {
        return NULL;
    }

    return _get_min(node->right);
}

binary_tree_node *
_get_predecessor(binary_tree_node *node) {
    return _get_max(node->left);
}

binary_tree_node *
get_predecessor(binary_tree *tree, int value) {
    binary_tree_node *node = _find_node(tree->root, value);

    if (node == NULL) {
        return NULL;
    }

    return _get_predecessor(node);
}

void
_delete_value(binary_tree_node *node) {
    if (node->left == NULL && node->right == NULL) {
        _detach_from_parent(node);
        return;
    }

    binary_tree_node *next =
        node->left != NULL ? _get_predecessor(node) : _get_successor(node);

    node->value = next->value;
    _delete_value(next);
}

int
delete_value(binary_tree *tree, int value) {
    binary_tree_node *node = _find_node(tree->root, value);
    if (node == NULL) {
        return -1;
    }

    _delete_value(node);
    tree->node_count--;

    return 0;
}

int
_get_height(binary_tree_node *node) {
    if (node == NULL) {
        return 0;
    }

    int l_subtree_height = _get_height(node->left);
    int r_subtree_height = _get_height(node->right);

    return 1 + max(l_subtree_height, r_subtree_height);
}

int
get_height(binary_tree *tree) {
    return _get_height(tree->root);
}

bool
is_in_tree(binary_tree *tree, int value) {
    return (bool) _find_node(tree->root, value);
}

bool
_is_binary_search_tree(binary_tree_node *node, int min_val, int max_val) {
    if (node == NULL) {
        return true;
    }

    if (min_val < node->value < max_val &&
        _is_binary_search_tree(node->left, min_val, node->value) &&
        _is_binary_search_tree(node->right, node->value, max_val)) {
        return true;
    }

    return false;
}

bool
is_binary_search_tree(binary_tree *tree) {
    return _is_binary_search_tree(tree->root, INFINITY, -INFINITY);
}

int
get_node_count(binary_tree *tree) {
    return tree->node_count;
}

binary_tree_node *
get_max(binary_tree *tree) {
    if (_is_empty_tree(tree)) {
        return 0;
    }

    return _get_max(tree->root);
}

binary_tree_node *
get_min(binary_tree *tree) {
    if (_is_empty_tree(tree)) {
        return 0;
    }

    return _get_min(tree->root);
}

void
delete_tree(binary_tree *tree) {
    _traverse(tree->root, _destroy_node);
    free(tree);
}

binary_tree *
make_binary_tree() {
    binary_tree *tree = (binary_tree *) malloc(sizeof(binary_tree));

    tree->node_count = 0;
    tree->get_node_count = get_node_count;
    tree->print_values = print_values;
    tree->print = print;
    tree->insert = insert;
    tree->is_in_tree = is_in_tree;
    tree->is_binary_search_tree = is_binary_search_tree;
    tree->get_max = get_max;
    tree->get_min = get_min;
    tree->get_height = get_height;
    tree->get_successor = get_successor;
    tree->delete_value = delete_value;
    tree->delete_tree = delete_tree;

    return tree;
}
