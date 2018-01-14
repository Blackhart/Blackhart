#ifndef __BK_QUEUE_H__
#define __BK_QUEUE_H__

// Blackhart.foundation headers.
#include "foundation\__BkExport.h"
#include "foundation\BkError.h"
#include "foundation\BkList.h"

struct BkQueue
{
	struct BkList*	list;
	size_t		size;
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/*! \brief Initializes the queue. Must be called before using the container!
 *
 * \param queue The queue to initialize.
 */
inline BK_API void	BkQueue_Initialize(struct BkQueue* queue)
{
	BK_ASSERT(BK_ISNULL(queue));

	queue->list = NULL;
	queue->size = 0;
}

/*! \brief Returns whether the queue is empty: i.e. whether its size is zero.
 *
 * \param queue The queue to evaluate.
 * \return true if the queue's size is 0, false otherwise.
 */
inline BK_API bool	BkQueue_Empty(struct BkQueue const* queue)
{
	BK_ASSERT(BK_ISNULL(queue));

	return queue->size == 0;
}

/*! \brief Returns the number of elements in the queue.
 *
 * \param queue The queue.
 * \return The number of elements in the queue.
 */
inline BK_API size_t	BkQueue_Size(struct BkQueue const* queue)
{
	BK_ASSERT(BK_ISNULL(queue));

	return queue->size;
}

/*! \brief Returns the first element in the queue.
 *
 * The first element is the oldest element in the queue.
 *
 * \param queue The queue.
 * \return A pointer to the first element in the queue.
 */
extern BK_API void*	BkQueue_Front(struct BkQueue* queue);

/*! \brief Returns the last element in the queue.
 *
 * The last element is the newest element in the queue.
 *
 * \param queue The queue.
 * \return A pointer to the last element in the queue.
 */
extern BK_API void*	BkQueue_Back(struct BkQueue* queue);

/*! \brief Inserts a new element at the end of the queue.
 *
 * \param queue The queue.
 * \param data The element to insert.
 */
inline BK_API void	BkQueue_Push(struct BkQueue* queue, void* data)
{
	BK_ASSERT(BK_ISNULL(queue));

	queue->list = BkList_PushBack(queue->list, data);
	queue->size++;
}

/*! \brief Removes the first element in the queue.
 *
 * The element removed is the oldest element in the queue.
 *
 * \param queue The queue.
 */
inline BK_API void	BkQueue_Pop(struct BkQueue* queue)
{
	BK_ASSERT(BK_ISNULL(queue));

	if (!(BK_ISTRUE(BkQueue_Empty(queue))))
	{
		queue->list = BkList_PopFront(queue->list);
		queue->size--;
	}
}

/*! \brief Clear the queue: i.e. delete all the elements in the queue.
 *
 * \param queue The queue.
 */
inline BK_API void	BkQueue_Clear(struct BkQueue* queue)
{
	BK_ASSERT(BK_ISNULL(queue));

	BkList_Clear(queue->list);
	queue->size = 0;
}

#endif