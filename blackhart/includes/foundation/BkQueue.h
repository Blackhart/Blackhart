#ifndef __BK_QUEUE_H__
#define __BK_QUEUE_H__

/**
 * @file BkQueue.h
 * @brief Defines the BkQueue structure and functions for queue operations.
 *
 * This file provides the definition of the BkQueue struct, a first-in-first-out
 * (FIFO) container implemented using a linked list. Elements are inserted at
 * the back and removed from the front.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkError.h"
#include "foundation/BkExport.h"
#include "foundation/BkList.h"

// ~~~~~ Type Definitions ~~~~~

/**
 * @struct BkQueue
 * @brief Structure representing a queue (FIFO container).
 *
 * The queue is implemented using a linked list (BkList) and maintains a count
 * of elements. Elements are added to the back and removed from the front.
 */
struct BkQueue {
  struct BkList*
      list; /**< Internal linked list used to store queue elements. */
  size_t size; /**< The number of elements currently in the queue. */
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Initializes the queue.
 *
 * Must be called before using the container. Sets the list to NULL and size to
 * 0.
 *
 * @param obj Pointer to the BkQueue object to initialize.
 */
static inline void BkQueue_Initialize(struct BkQueue* obj) {
  BK_ASSERT(BK_ISNULL(obj));

  obj->list = NULL;
  obj->size = 0;
}

/**
 * @brief Returns whether the queue is empty.
 *
 * Checks if the queue contains no elements (size is zero).
 *
 * @param obj Pointer to the queue to evaluate.
 * @return true if the queue's size is 0, false otherwise.
 */
static inline bool BkQueue_Empty(struct BkQueue const* obj) {
  BK_ASSERT(BK_ISNULL(obj));

  return obj->size == 0;
}

/**
 * @brief Returns the number of elements in the queue.
 *
 * @param obj Pointer to the queue.
 * @return The number of elements in the queue.
 */
static inline size_t BkQueue_Size(struct BkQueue const* obj) {
  BK_ASSERT(BK_ISNULL(obj));

  return obj->size;
}

/**
 * @brief Returns a pointer to the first element in the queue.
 *
 * The first element is the oldest element in the queue (next to be removed).
 *
 * @param obj Pointer to the queue.
 * @return A pointer to the first element in the queue, or NULL if the queue is
 * empty.
 */
extern BK_API void* BkQueue_Front(struct BkQueue* obj);

/**
 * @brief Returns a pointer to the last element in the queue.
 *
 * The last element is the newest element in the queue (most recently added).
 *
 * @param obj Pointer to the queue.
 * @return A pointer to the last element in the queue, or NULL if the queue is
 * empty.
 */
extern BK_API void* BkQueue_Back(struct BkQueue* obj);

/**
 * @brief Inserts a new element at the end of the queue.
 *
 * Adds the data to the back of the queue. The queue size is increased by one.
 *
 * @param obj Pointer to the queue.
 * @param data Pointer to the element to insert.
 */
static inline void BkQueue_Push(struct BkQueue* obj, void* data) {
  BK_ASSERT(BK_ISNULL(obj));

  obj->list = BkList_PushBack(obj->list, data);
  obj->size++;
}

/**
 * @brief Removes the first element in the queue.
 *
 * The element removed is the oldest element in the queue (first to be removed).
 * The queue size is decreased by one. If the queue is empty, this function has
 * no effect.
 *
 * @param obj Pointer to the queue.
 */
static inline void BkQueue_Pop(struct BkQueue* obj) {
  BK_ASSERT(BK_ISNULL(obj));

  if (!(BK_ISTRUE(BkQueue_Empty(obj)))) {
    obj->list = BkList_PopFront(obj->list);
    obj->size--;
  }
}

/**
 * @brief Clears the queue, removing all elements.
 *
 * Removes all elements from the queue and resets the size to zero.
 * The internal list is cleared but may retain allocated memory.
 *
 * @param obj Pointer to the queue.
 */
static inline void BkQueue_Clear(struct BkQueue* obj) {
  BK_ASSERT(BK_ISNULL(obj));

  BkList_Clear(obj->list);
  obj->size = 0;
}

#endif