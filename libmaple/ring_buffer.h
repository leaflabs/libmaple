/**
 * @file ring_buffer.h
 * @brief simple circular buffer
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
    uint32 head;
    uint32 tail;
    uint8 size;
    uint8 *buf;
} ring_buffer;

static inline void rb_init(ring_buffer *rb, uint8 size, uint8 *buf) {
    ASSERT(IS_POWER_OF_TWO(size));
    rb->head = 0;
    rb->tail = 0;
    rb->size = size;
    rb->buf = buf;
}

static inline void rb_insert(ring_buffer *rb, uint8 element) {
    rb->buf[(rb->tail)++] = element;
    rb->tail &= (rb->size - 1);
}

static inline uint8 rb_remove(ring_buffer *rb) {
    uint8 ch = rb->buf[rb->head++];
    rb->head &= (rb->size - 1);
    return ch;
}

static inline uint32 rb_full_count(ring_buffer *rb) {
    return rb->tail - rb->head;
}

static inline void  rb_reset(ring_buffer *rb) {
    rb->tail = rb->head;
}

#ifdef __cplusplus
} // extern "C"
#endif



#endif

