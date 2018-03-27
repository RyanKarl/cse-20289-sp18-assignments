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
    return NULL;
}

/**
 * Delete Queue structure.
 * @param   q           Queue structure.
 * @return  NULL.
 */
Queue * queue_delete(Queue *q) {
    return NULL;
}

/**
 * Push Node into Queue structure.
 * @param   q           Queue structure.
 * @param   n           Node structure.
 * @return  Whether or not the operation was successful.
 */
bool    queue_push(Queue *q, Node *n) {
    return false;
}

/**
 * Pop minimum Node into Queue structure.
 * @param   q           Queue structure.
 * @return  Minimum Node structure (by count) or NULL.
 */
Node *	queue_pop(Queue *q) {
    return NULL;
}

/**
 * Dump Queue structure.
 * @param   q           Queue structure.
 * @param   stream      I/O stream to write to.
 */
void    queue_dump(const Queue *q, FILE *stream) {
}

/* Internal Priority Queue Functions */

/**
 * Resize Queue structure.
 * @param   q           Queue structure.
 * @param   capacity    New capacity.
 * @return  Whether or not operation succeeded.
 */
bool    queue_resize(Queue *q, size_t capacity) {
    return false;
}

/**
 * Bubble up Node in Queue structure.
 * @param   q           Queue structure.
 * @param   i           Index to current Node structure.
 */
void    queue_bubble_up(Queue *q, size_t i) {
}

/**
 * Bubble down Node in Queue structure.
 * @param   q           Queue structure.
 * @param   i           Index to current Node structure.
 */
void    queue_bubble_down(Queue *q, size_t i) {
}

/**
 * Determines index of child with minimum value.
 * @param   q           Queue structure.
 * @param   i           Index to current Node structure.
 */
size_t  queue_minimum_child(Queue *q, size_t i) {
    return 0;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
