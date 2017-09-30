#ifndef __BK_LIST_H__
#define __BK_LIST_H__

#include "pil\BkAtomicDataType.h"
#include "pil\__BkExport.h"

#include "core\BkError.h"

/*! \brief Checks if the BkList has no elements
*
* \param pList Any BkLIst element
* \return TRUE if the BkList is empty, FALSE otherwise
*/
#define BkList_Empty(pList)		(BK_ISNULL(pList))

/*! \brief Gets the element's data in a BkList
*
* \param pList Any BkLIst element
* \return The element's data, or NULL if there are no element's data
*/
#define BkList_Data(pList)		(pList->elem)

/*! \brief Gets the previous element in a BkList
*
* \param pList Any BkLIst element
* \return The previous element, or NULL if there are no previous elements
*/
#define BkList_Previous(pList)	(pList->previous)

/*! \brief Gets the next element in a BkList
*
* \param pList Any BkLIst element
* \return The next element, or NULL if there are no next elements
*/
#define BkList_Next(pList)		(pList->next)

struct sList
{
	void*			elem;
	struct sList*	next;
	struct sList*	previous;
};

typedef struct sList	BkList;

// ~~~~~ Dcl(PUBLIC) ~~~~~

/*! \brief Gets the first element in a BkList
 *
 * \param pList Any BkLIst element
 * \return The first element in the BkList, or NULL if the BkList has no elements
 */
extern BK_API BkList*	BkList_Front(BkList const* pList);

/*! \brief Gets the last element in a BkList
*
* \param pList Any BkLIst element
* \return The last element in the BkList, or NULL if the BkList has no elements
*/
extern BK_API BkList*	BkList_Back(BkList const* pList);

/*! \brief Gets the number of elements in a BkList
*
* \param pList Any BkLIst element
* \return The number of elements in the BkList
*/
extern BK_API uint32	BkList_Size(BkList const* pList);

/*! \brief Frees all of the memory used by a BkList
* If list elements contain dynamically-allocated memory, you should either use BkList_ClearFull() or free them manually first
* \param pList Any BkLIst element
*/
extern BK_API void		BkList_Clear(BkList* pList);

/*! \brief Gets the element at a given position in a BkList
*
* \param pList Any BkLIst element
* \param index The position of the element
* \return The element, or NULL if the position is of the end of the BkList
*/
extern BK_API BkList*	BkList_Get(BkList* pList, uint32 const index);

/*! \brief Inserts a new element into the list at the given position
*
* \param pList Any BkLIst element
* \param pData The data for the new element
* \param index The position to insert the element. If this is larger than the number of elements in the list, the new element is added on to the end of the list
* \return The start of the BkList
*/
extern BK_API BkList*	BkList_Insert(BkList* pList, void const* pData, uint32 const index);

/*! \brief Remove an element from a BkList
* If two elements contain the same pData, only the fist is removed. If none of the elements contain the pData, the BkList is unchanged
* \param pList Any BkLIst element
* \param pData The data of the element to remove
* \return The start of the BkList
*/
extern BK_API BkList*	BkList_Erase(BkList* pList, void const* pData);

/*! \brief Remove an element from a BkList
* If two elements contain the same pData, only the fist is removed. If none of the elements contain the pData, the BkList is unchanged
* \param pLink the link to remove from the BkList
* \return The start of the BkList
*/
extern BK_API BkList*	BkList_EraseLink(BkList* pLink);

/*! \brief Prepends a new element on to the start of the list
*
* \param pList Any BkLIst element
* \param pData The data for the new element
* \return The start of the BkList
*/
extern BK_API BkList*	BkList_PushFront(BkList* pList, void const* pData);

/*! \brief Prepends a new element on to the end of the list
*
* \param pList Any BkLIst element
* \param pData The data for the new element
* \return The start of the BkList
*/
extern BK_API BkList*	BkList_PushBack(BkList* pList, void const* pData);

/*! \brief Remove the first element from a BkList
*
* \param pList Any BkLIst element
* \return The start of the BkList
*/
extern BK_API BkList*	BkList_PopFront(BkList* pList);

/*! \brief Remove the last element from a BkList
*
* \param pList Any BkLIst element
* \return The start of the BkList
*/
extern BK_API BkList*	BkList_PopBack(BkList* pList);

/*! \brief Allocates space for one BkList element
*
* \return a pointer to the newly-allocated BkList element
*/
extern BK_API BkList*	BkList_Alloc(void);

#endif