#ifndef __BK_QUEUE_H__
#define __BK_QUEUE_H__

// Blackhart.foundation headers.
#include "foundation\BkExport.h"
#include "foundation\BkError.h"
#include "foundation\BkList.h"

struct BkQueue
{
	struct BkList*	list;
	size_t	size;
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/*! \brief Initializes the queue. Must be called before using the container!
 *
 * \param obj The queue to initialize.
 */
static inline void	BkQueue_Initialize(struct BkQueue* obj)
{
	BK_ASSERT(BK_ISNULL(obj));

	obj->list = NULL;
	obj->size = 0;
}

/*! \brief Returns whether the queue is empty: i.e. whether its size is zero.
 *
 * \param obj The queue to evaluate.
 * \return true if the queue's size is 0, false otherwise.
 */
static inline bool	BkQueue_Empty(struct BkQueue const* obj)
{
	BK_ASSERT(BK_ISNULL(obj));

	return obj->size == 0;
}

/*! \brief Returns the number of elements in the queue.
 *
 * \param obj The queue.
 * \return The number of elements in the queue.
 */
static inline size_t	BkQueue_Size(struct BkQueue const* obj)
{
	BK_ASSERT(BK_ISNULL(obj));

	return obj->size;
}

/*! \brief Returns the first element in the queue.
 *
 * The first element is the oldest element in the queue.
 *
 * \param obj The queue.
 * \return A pointer to the first element in the queue.
 */
extern BK_API void*	BkQueue_Front(struct BkQueue* obj);

/*! \brief Returns the last element in the queue.
 *
 * The last element is the newest element in the queue.
 *
 * \param obj The queue.
 * \return A pointer to the last element in the queue.
 */
extern BK_API void*	BkQueue_Back(struct BkQueue* obj);

/*! \brief Inserts a new element at the end of the queue.
 *
 * \param obj The queue.
 * \param data The element to insert.
 */
static inline void	BkQueue_Push(struct BkQueue* obj, void* data)
{
	BK_ASSERT(BK_ISNULL(obj));

	obj->list = BkList_PushBack(obj->list, data);
	obj->size++;
}

/*! \brief Removes the first element in the queue.
 *
 * The element removed is the oldest element in the queue.
 *
 * \param obj The queue.
 */
static inline void	BkQueue_Pop(struct BkQueue* obj)
{
	BK_ASSERT(BK_ISNULL(obj));

	if (!(BK_ISTRUE(BkQueue_Empty(obj))))
	{
		obj->list = BkList_PopFront(obj->list);
		obj->size--;
	}
}

/*! \brief Clear the queue: i.e. delete all the elements in the queue.
 *
 * \param obj The queue.
 */
static inline void	BkQueue_Clear(struct BkQueue* obj)
{
	BK_ASSERT(BK_ISNULL(obj));

	BkList_Clear(obj->list);
	obj->size = 0;
}

#endif