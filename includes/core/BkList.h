#ifndef __BK_LIST_H__
#define __BK_LIST_H__

#include "pil\BkAtomicDataType.h"
#include "BkError.h"

#include "pil\__BkExport.h"

struct sSimpleLinkedList
{
	struct sSimpleLinkedList*	next;
	void*						elem;
};

typedef struct sSimpleLinkedList	BkSimpleLinkedList;

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API void		BkSimpleLinkedList_Create(BkSimpleLinkedList** ppList, void* pElem);
extern BK_API void		BkSimpleLinkedList_PushBack(BkSimpleLinkedList** ppList, void* pElem);
extern BK_API void		BkSimpleLinkedList_RemoveAll(BkSimpleLinkedList** ppList);
extern BK_API void		BkSimpleLinkedList_RemoveElem(BkSimpleLinkedList** ppList, void** ppElement);
extern BK_API void		BkSimpleLinkedList_Length(BkSimpleLinkedList const* pList, uint32* pLength);
extern BK_API BkResult	BkSimpleLinkedList_Get(BkSimpleLinkedList const* pList, void** ppElement, uint32 const pIndex);

#endif