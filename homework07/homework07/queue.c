/* queue.c: Priority Queue (Min Heap) */

#include "debug.h"
#include "queue.h"

/* Internal Priority Queue Prototypes */

bool    queue_resize(Queue *q, size_t capacity);
void    queue_bubble_up(Queue *q, size_t i);
void    queue_bubble_down(Queue *q, size_t i);
size_t  queue_minimum_child(Queue *q, size_t i);

/* External Priority Queue Functions */

/**
 * Create Queue structure.
 * @param   capacity        Initial capacity.
 * @return  Newly allocated Queue structure with specified capacity.
 */
Queue * queue_create(size_t capacity) {
    if(!capacity) {
        capacity = PRIORITY_QUEUE_CAPACITY;
    }
    Queue *q = calloc(1, sizeof(Queue));   
        if (q){
            q->size = 0;
            q->nodes = calloc(capacity, sizeof(Node*));
            if(!q->nodes){
                free(q);
                return NULL;
            }
            
            q->capacity = capacity;
         }

    return q;
}

/**
 * Delete Queue structure.
 * @param   q           Queue structure.
 * @return  NULL.
 */
Queue * queue_delete(Queue *q) {
    
    free(q->nodes);
    free(q);
    q = NULL;
    return q;
}

/**
 * Push Node into Queue structure.
 * @param   q           Queue structure.
 * @param   n           Node structure.
 * @return  Whether or not the operation was successful.
 */
bool    queue_push(Queue *q, Node *n) {
    
    if(n == NULL){
        return false;
    }
    if(q == NULL){
        return false;
    }
    if(q->size >= q->capacity){
        if(queue_resize(q, 2 * (q->capacity)) == false){
            
            return false;
        }
    }
            
    q->nodes[q->size] = n;
    queue_bubble_up(q, q->size);
    q->size += 1;
    
    return true;
}

/**
 * Pop minimum Node into Queue structure.
 * @param   q           Queue structure.
 * @return  Minimum Node structure (by count) or NULL.
 */
Node *	queue_pop(Queue *q) {
    
    if(q->size==0){
        return NULL;
    }

    Node * result = q->nodes[0];
    q->size-=1;
    q->nodes[0] = q->nodes[q->size];
    q->nodes[q->size] = NULL;
    queue_bubble_down(q,0);
    return result;
}

/**
 * Dump Queue structure.
 * @param   q           Queue structure.
 * @param   stream      I/O stream to write to.
 */
void    queue_dump(const Queue *q, FILE *stream) {

    if(q->nodes == NULL){
        return;
    }
    for(int i = 0; i < q->size; i++){
        node_dump(q->nodes[i], stream);
    }

}

/* Internal Priority Queue Functions */

/**
 * Resize Queue structure.
 * @param   q           Queue structure.
 * @param   capacity    New capacity.
 * @return  Whether or not operation succeeded.
 */
bool    queue_resize(Queue *q, size_t capacity) {
    
    q->capacity = capacity;
    q->nodes = realloc(q->nodes, q->capacity*sizeof(Node*));

    return q->nodes;
}

/**
 * Bubble up Node in Queue structure.
 * @param   q           Queue structure.
 * @param   i           Index to current Node structure.
 */
void    queue_bubble_up(Queue *q, size_t i) {

    while(i > 0) 
    {
        size_t parent = PARENT(i);
        if((q->nodes[i])->count < (q->nodes[parent])->count){
            Node * temp = q->nodes[i];
            q->nodes[i] = q->nodes[parent];
            q->nodes[parent] = temp;
        }
            i = parent;    
    }
}

/**
 * Bubble down Node in Queue structure.
 * @param   q           Queue structure.
 * @param   i           Index to current Node structure.
 */
void    queue_bubble_down(Queue *q, size_t i) {

    Node * temp;
    while(LEFT_CHILD(i) < q->size)
    {
        size_t min = queue_minimum_child(q, i);
        if(q->nodes[min]->count < (q->nodes[i])->count){
            temp = q->nodes[i];
            q->nodes[i] = q->nodes[min];
            q->nodes[min] = temp;
        }
    i = min;
    }
}

/**
 * Determines index of child with minimum value.
 * @param   q           Queue structure.
 * @param   i           Index to current Node structure.
 */
size_t  queue_minimum_child(Queue *q, size_t i) {
    
    size_t l = LEFT_CHILD(i);
    size_t r = RIGHT_CHILD(i);

    if(!q->nodes[r])
    {
        return l;
    }

    if(q->nodes[l]->count < q->nodes[r]->count){
        return l;
    }

    return r;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
