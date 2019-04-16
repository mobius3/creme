#ifndef CREME_CIRCULAR_QUEUE_H
#define CREME_CIRCULAR_QUEUE_H

/**
 * This file contains a function-macro to declare and another to
 * define a simple circular queue. Its purpose is mainly to facilitate
 * dealing with finite storage where things can be written and later, read.
 *
 * It is not really inteded for public use.
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CM_CIRQUE_DECLARE(Name, Type) \
\
struct Name { \
  Type * buffer; \
  uint16_t size; \
  uint16_t count; \
  int read_head; \
  int write_head; \
}; \
\
enum Name##_enqueue_result {  \
Name##_enqueue__ok, \
Name##_enqueue__full \
}; \
\
enum Name##_dequeue_result { \
Name##_dequeue__ok, \
Name##_dequeue__empty \
}; \
 \
extern void Name##_construct(struct Name * queue, Type buffer[], uint16_t size); \
extern enum Name##_enqueue_result Name##_enqueue(struct Name * q, Type const * item); \
extern enum Name##_dequeue_result Name##_dequeue(struct Name * q, Type * item); \
extern int8_t Name##_is_full(struct Name const * q); \
extern int8_t Name##_is_empty(struct Name const * q); \
extern uint16_t Name##_count(struct Name const * q); \
extern void Name##_flush(struct Name * q); \
extern uint16_t Name##_free_space(struct Name const * q);

#include <stdio.h>
#include <stdint.h>

#define CM_CIRQUE_DEFINE(Name, Type) \
\
void Name##_construct(struct Name * queue, Type buffer[], uint16_t size) { \
  queue->buffer = buffer; \
  queue->size = size; \
  queue->read_head = -1; \
  queue->write_head = -1; \
} \
\
enum Name##_enqueue_result Name##_enqueue(struct Name * q, Type const * item) { \
  if (Name##_is_full(q)) return Name##_enqueue__full; \
  if (q->write_head == -1) { \
    q->write_head = 0; \
    q->read_head = 0; \
  } \
  q->buffer[q->write_head] = *item; \
  q->write_head = (q->write_head + 1) % q->size; \
  q->count += 1; \
  return Name##_enqueue__ok; \
} \
\
enum Name##_dequeue_result Name##_dequeue(struct Name * q, Type * item) { \
  if (Name##_is_empty(q)) return Name##_dequeue__empty; \
  *item = q->buffer[q->read_head]; \
  q->read_head = (q->read_head + 1) % q->size; \
  if (q->read_head == q->write_head) q->write_head = q->read_head = -1; \
  q->count -= 1; \
  return Name##_dequeue__ok; \
} \
\
int8_t Name##_is_full(struct Name const * q) { \
  return (q->write_head != -1) && \
         (((q->size - (q->write_head - q->read_head)) % q->size) == 0); \
} \
\
int8_t Name##_is_empty(struct Name const * q) { \
  return q->write_head == -1 && q->read_head == -1; \
} \
\
uint16_t Name##_count(struct Name const * q) { \
  return q->count; \
}\
uint16_t Name##_free_space(struct Name const * q) { \
  return q->size - q->count;\
}\
\
void Name##_flush(struct Name * q) { \
  q->count = 0; \
  q->write_head = -1; \
  q->read_head = -1; \
}

#ifdef __cplusplus
}
#endif

#endif /* CREME_CIRCULAR_QUEUE_H */
