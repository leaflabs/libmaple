/**
 * @file ring_buffer.h
 * @brief Simple circular buffer
 *
 * This implementation is not thread-safe.  In particular, none of
 * these functions are guaranteed re-entrant.
 */

#ifndef _RING_BUFFER_H_
#define _RING_BUFFER_H_

#ifdef __cplusplus
extern "C"{
#endif

/* The buffer is empty when head == tail.
 *
 * The buffer is full when the head is one byte in front of the tail,
 * modulo buffer length.
 *
 * One byte is left free to distinguish empty from full. */
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

/**
 * Initialise a ring buffer.
 *
 *  @param rb   Instance to initialise
 *
 *  @param size Number of items in buf.  The ring buffer will always
 *              leave one element unoccupied, so the maximum number of
 *              elements it can store will be size - 1.  Thus, size
 *              must be at least 2.
 *
 *  @param buf  Buffer to store items into
 */
__attribute__((unused))
static void rb_init(ring_buffer *rb, uint16 size, uint8 *buf) {
    rb->head = 0;
    rb->tail = 0;
    rb->size = size - 1;
    rb->buf = buf;
}

/** Return the number of elements stored in the ring buffer. */
static inline uint16 rb_full_count(ring_buffer *rb) {
    volatile ring_buffer *arb = rb;
    int32 size = arb->tail - arb->head;
    if (arb->tail < arb->head) {
        size += arb->size + 1;
    }
    return (uint16)size;
}

/** Return true if and only if the ring buffer is full. */
static inline int rb_is_full(ring_buffer *rb) {
    return (rb->tail + 1 == rb->head) ||
        (rb->tail == rb->size && rb->head == 0);
}

/** Append element onto the end of the ring buffer. */
static inline void rb_insert(ring_buffer *rb, uint8 element) {
    rb->buf[rb->tail] = element;
    rb->tail = (rb->tail == rb->size) ? 0 : rb->tail + 1;
}

/** Remove and return the first item from the ring buffer. */
static inline uint8 rb_remove(ring_buffer *rb) {
    uint8 ch = rb->buf[rb->head];
    rb->head = (rb->head == rb->size) ? 0 : rb->head + 1;
    return ch;
}

/**
 * If rb is not full, appends element and returns true; otherwise,
 * does nothing and returns false. */
static inline int rb_safe_insert(ring_buffer *rb, uint8 element) {
    if (rb_is_full(rb)) {
        return 0;
    }
    rb_insert(rb, element);
    return 1;
}

/**
 * Append an item onto the end of a non-full ring buffer.  If the
 * buffer is full, removes its first item, then inserts the new
 * element at the end.
 *
 * On success, returns -1.  If an element was popped, returns the
 * popped value. */
static inline int rb_push_insert(ring_buffer *rb, uint8 element) {
    int ret = -1;
    if (rb_is_full(rb)) {
        ret = rb_remove(rb);
    }
    rb_insert(rb, element);
    return ret;
}

/** Discard all items from the buffer */
static inline void rb_reset(ring_buffer *rb) {
    rb->tail = rb->head;
}

#ifdef __cplusplus
} // extern "C"
#endif



#endif

