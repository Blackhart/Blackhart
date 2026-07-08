// blackhart headers.
#include "foundation/BkError.h"
#include "renderer/BkScene.h"

// ~~~~~ Def(PUBLIC) ~~~~~

struct BkScene	BkScene_Initialize(void)
{
	struct BkScene scene;
	scene.models = NULL;
	return scene;
}

void	BkScene_Uninitialize(struct BkScene* obj)
{
	BK_ASSERT(BK_ISNULL(obj));

	BkList_Clear(obj->models);
	obj->models = NULL;
}

void	BkScene_AddModel(struct BkScene* scene, struct BkModel* model)
{
	BK_ASSERT(BK_ISNULL(scene));
	BK_ASSERT(BK_ISNULL(model));

	scene->models = BkList_PushBack(scene->models, model);
}

void	BkScene_RemoveModel(struct BkScene* scene, struct BkModel* model)
{
	BK_ASSERT(BK_ISNULL(scene));

	scene->models = BkList_Erase(scene->models, model);
}
