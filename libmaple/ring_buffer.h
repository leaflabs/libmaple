/**
 *  @brief simple circular buffer
 */

#ifndef _RING_BUFFER_H_
#define _RING_BUFFER_H_

#ifdef __cplusplus
extern "C"{
#endif

/* The buffer is empty when head == tail.
 * The buffer is full when the head is one byte in front of the tail
 * The total buffer size must be a power of two
 * One byte is left free to distinguish empty from full */
typedef struct ring_buffer {
    /** Buffer items are stored into */
    volatile uint8 *buf;
    /** Index of the next item to remove */
    uint16 head;
    /** Index where the next item will get inserted */
    uint16 tail;
    /** Buffer capacity minus one */
    uint16 size;
} ring_buffer;

/** Initialise a ring buffer.
 *
 *  @param rb    instance to initialise
 *  @param size  number of items in the buffer
 *  @param buf   buffer to store items into
*/
static inline void rb_init(ring_buffer *rb, uint16 size, uint8 *buf) {
    rb->head = 0;
    rb->tail = 0;
    rb->size = size - 1;
    rb->buf = buf;
}

/** Append an item onto the end of the ring buffer */
static inline void rb_insert(ring_buffer *rb, uint8 element) {
    rb->buf[rb->tail] = element;
    rb->tail = (rb->tail == rb->size) ? 0 : rb->tail + 1;
}

/** Remove and return the first item from the ring buffer */
static inline uint8 rb_remove(ring_buffer *rb) {
    uint8 ch = rb->buf[rb->head];
    rb->head = (rb->head == rb->size) ? 0 : rb->head + 1;
    return ch;
}

static inline uint32 rb_full_count(ring_buffer *rb) {
    /* PENDING: Broken */
    volatile ring_buffer *arb = rb;
    return arb->tail - arb->head;
}

/** Discard all items from the buffer */
static inline void  rb_reset(ring_buffer *rb) {
    rb->tail = rb->head;
}

#ifdef __cplusplus
} // extern "C"
#endif



#endif

