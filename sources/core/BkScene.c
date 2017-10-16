#include "core\BkScene.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

static struct BkList*	__BkScene_Entities = NULL;

// ~~~~~ Def(ALL) ~~~~~

void	BkScene_AddEntity(struct BkEntity* entity)
{
	if (BK_ISNULL(entity))
	{
		BK_ERROR(BK_ERROR_LOCATION "pEntity == NULL");
		return;
	}

	__BkScene_Entities = BkList_PushBack(__BkScene_Entities, entity);
}

void	BkScene_RemoveEntity(struct BkEntity* entity)
{
	if (BK_ISNULL(entity))
	{
		BK_ERROR(BK_ERROR_LOCATION "pEntity == NULL");
		return;
	}

	__BkScene_Entities = BkList_Erase(__BkScene_Entities, entity);
}

struct BkList const*	BkScene_GetEntities(void)
{
	return __BkScene_Entities;
}