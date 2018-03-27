/* node.c: Huffman Node */

#include "node.h"

/* Internal Node Functions */

void    node_set_symbol(Node *n, int64_t letter);

/* External Node Functions */

/**
 * Create Node structure.
 * @param   symbol      Symbol letter.
 * @param   count       Initial count.
 * @param   left        Left Node child.
 * @param   right       Right Node child.
 * @return  Newly allocated Node structure with specified attributes.
 */
Node *  node_create(int64_t symbol, size_t count, Node *left, Node *right) {
    return NULL;
}

/**
 * Delete Node structure.
 * @param   n           Node structure.
 * @return  NULL.
 */
Node *  node_delete(Node *n) {
    return NULL;
}

/**
 * Dump Node structure.
 * @param   n           Node structure.
 * @param   stream      I/O to write to.
 */
void    node_dump(const Node *n, FILE *stream) {
}

/* Internal Node Functions */

/**
 * Set symbol attribute of Node structure.
 * @param   n           Node structure.
 * @param   letter      Node symbol letter value.
 */
void    node_set_symbol(Node *n, int64_t letter) {                         
}                                                            

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
