#include "core\BkScene.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

static BkList* __BkScene_Entities = NULL;

// ~~~~~ Def(ALL) ~~~~~

void	BkScene_AddEntity(BkEntity* pEntity)
{
	if (BK_ISNULL(pEntity))
	{
		BK_ERROR(BK_ERROR_LOCATION "pEntity == NULL");
		return;
	}

	__BkScene_Entities = BkList_PushBack(__BkScene_Entities, pEntity);
}

void	BkScene_RemoveEntity(BkEntity* pEntity)
{
	if (BK_ISNULL(pEntity))
	{
		BK_ERROR(BK_ERROR_LOCATION "pEntity == NULL");
		return;
	}

	__BkScene_Entities = BkList_Erase(__BkScene_Entities, pEntity);
}

BkList const*	BkScene_GetEntities(void)
{
	return __BkScene_Entities;
}