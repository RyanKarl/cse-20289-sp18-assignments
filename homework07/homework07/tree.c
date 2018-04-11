/* tree.c: Huffman Tree */

#include "queue.h"
#include "tree.h"

#include <string.h>

/* Internal Huffman Tree Prototyes */

void	tree_count(Tree *t, FILE *stream);
Queue *	tree_queue(Tree *t);
void	tree_walk_node(const Node *n, NodeFunc f, void *arg, char *encoding);

/* External Huffman Tree Functions */

/**
 * Create Tree structure.
 * @return  Newly allocated and initialized Tree structure.
 */
Tree *  tree_create() {
    return NULL;
}

/**
 * Delete Tree structure.
 * @param   t           Tree structure.
 * @return  NULL.
 */
Tree *  tree_delete(Tree *t) {
    return NULL;
}

/**
 * Build internal Tree structure.
 * @param   t           Tree structure.
 * @param   stream      I/O stream to read from.
 * @return  Whether or not the operation succeeded.
 */
bool	tree_build(Tree *t, FILE *stream) {
    return false;
}

/**
 * Walk Tree structure.
 * @param   t           Tree structure.
 * @param   f           Node function.
 * @param   arg         Ndoe function argument.
 * @return  Whether or not the operation succeeded.
 */
void	tree_walk(const Tree *t, NodeFunc f, void *arg) {
}

/* Internal Tree Functions */

/**
 * Build internal counts table in Tree structure.
 * @param   t           Tree structure.
 * @param   stream      I/O stream to read from.
 * @return
 */
void	tree_count(Tree *t, FILE *stream) {
}

/**
 * Create Priority Queue out of counts table in Tree structure.
 * @param   t           Tree structure.
 * @return  Priority Queue of Nodes corresponding to counts in Tree.
 */
Queue *	tree_queue(Tree *t) {
    return NULL;
}

/**
 * Recursively walk Tree nodes.
 * @param   n           Node structure.
 * @param   f           Node function.
 * @param   arg         Node function argument.
 * @param   encoding    Node encoding.
 */
void	tree_walk_node(const Node *n, NodeFunc f, void *arg, char *encoding) {
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
