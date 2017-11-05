#include "core\BkScene.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

static struct BkVector	__BkScene_Entities;

// ~~~~~ Def(ALL) ~~~~~

void	BkScene_AddEntity(struct BkEntity* entity)
{
	if (BK_ISNULL(entity))
	{
		BK_ERROR(BK_ERROR_LOCATION "pEntity == NULL");
		return;
	}

	BkVector_PushBack(__BkScene_Entities, entity);
}

void	BkScene_RemoveEntity(struct BkEntity* entity)
{
	//if (BK_ISNULL(entity))
	//{
	//	BK_ERROR(BK_ERROR_LOCATION "pEntity == NULL");
	//	return;
	//}

	//__BkScene_Entities = BkList_Erase(__BkScene_Entities, entity);
}

struct BkVector const*	BkScene_GetEntities(void)
{
	return &__BkScene_Entities;
}