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
    Tree * t = calloc(1, sizeof(Tree));
    t->root = NULL;
    for(int i = 0; i < TREE_COUNTS_SIZE; i++){
        t->counts[i] = '\0';
    }
    
    return t;
}

/**
 * Delete Tree structure.
 * @param   t           Tree structure.
 * @return  NULL.
 */
Tree *  tree_delete(Tree *t) {

    node_delete(t->root);
    t->root = NULL;
    free(t);
    t = NULL;
    return t;
}

/**
 * Build internal Tree structure.
 * @param   t           Tree structure.
 * @param   stream      I/O stream to read from.
 * @return  Whether or not the operation succeeded.
 */
bool	tree_build(Tree *t, FILE *stream) {
    tree_count(t, stream);
    Queue * q = tree_queue(t);
    if(q == NULL || q->size < 1){
        return false;
    }
    while(q->size > 1)
    {
        Node * n1 = queue_pop(q);
        if(n1 == NULL){
            return false;
        }
        Node * n2 = queue_pop(q);
        if(n2 == NULL){
            return false;
        }
        size_t newCount = n1->count + n2->count;
        Node * newNode = node_create(NODE_NOT_SYMBOL, newCount, n1, n2);
        if(newNode == NULL)
        {
            return false;
        }
        if(queue_push(q, newNode) == false)
        {
            return false;
        }
    }
    t->root = queue_pop(q);
    queue_delete(q);
    return true;
}

/**
 * Walk Tree structure.
 * @param   t           Tree structure.
 * @param   f           Node function.
 * @param   arg         Ndoe function argument.
 * @return  Whether or not the operation succeeded.
 */
void	tree_walk(const Tree *t, NodeFunc f, void *arg) {
    
    char encoding[BUFSIZ];
    encoding[0] = '\0';
    tree_walk_node(t->root, f, arg, encoding);

}

/* Internal Tree Functions */

/**
 * Build internal counts table in Tree structure.
 * @param   t           Tree structure.
 * @param   stream      I/O stream to read from.
 * @return
 */
void	tree_count(Tree *t, FILE *stream) {

    char c = fgetc(stream);
    while(c != EOF)
    {
        t->counts[(int)c]++;
        c = fgetc(stream);
    }

}

/**
 * Create Priority Queue out of counts table in Tree structure.
 * @param   t           Tree structure.
 * @return  Priority Queue of Nodes corresponding to counts in Tree.
 */
Queue *	tree_queue(Tree *t) {

    Queue * q = queue_create(0);
    if(q == NULL)
    {
        return NULL;
    }
    for(int i = 0; i < TREE_COUNTS_SIZE; i++)
    {
        if(t->counts[i] != 0)
        {
            Node * n = node_create((int64_t)i, (size_t)t->counts[i], NULL, NULL);
            if(n==NULL)
            {
                return NULL;
            }
            if(queue_push(q, n) == false)
            {
                return NULL;
            }
        }
    }

    return q;
}

/**
 * Recursively walk Tree nodes.
 * @param   n           Node structure.
 * @param   f           Node function.
 * @param   arg         Node function argument.
 * @param   encoding    Node encoding.
 */
void	tree_walk_node(const Node *n, NodeFunc f, void *arg, char *encoding) {

    if(!n){
        f(n, encoding, arg);
        return;
    }

    if((char) n->symbol.letter != NODE_NOT_SYMBOL)
    {
        if(!strcmp(encoding, ""))
        {
            strcat(encoding, "0");
        }
        f(n, encoding, arg);       
    }

    if(n->left){
        char new_encoding[BUFSIZ];
        strcpy(new_encoding, encoding);
        strcat(new_encoding, "0");
        tree_walk_node(n->left, f, arg, new_encoding);

    }

    if(n->right){
        strcat(encoding, "1");
        tree_walk_node(n->right, f, arg, encoding);
    }
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
