// blackhart headers.
#include "foundation/BkError.h"
#include "renderer/BkScene.h"

// ~~~~~ Def(PUBLIC) ~~~~~

struct BkScene	BkScene_Initialize(void)
{
	struct BkScene scene;
	scene.clouds = NULL;
	return scene;
}

void	BkScene_Uninitialize(struct BkScene* obj)
{
	BK_ASSERT(BK_ISNULL(obj));

	BkList_Clear(obj->clouds);
	obj->clouds = NULL;
}

void	BkScene_AddCloud(struct BkScene* scene, struct BkPointCloud* cloud)
{
	BK_ASSERT(BK_ISNULL(scene));
	BK_ASSERT(BK_ISNULL(cloud));

	scene->clouds = BkList_PushBack(scene->clouds, cloud);
}

void	BkScene_RemoveCloud(struct BkScene* scene, struct BkPointCloud* cloud)
{
	BK_ASSERT(BK_ISNULL(scene));

	scene->clouds = BkList_Erase(scene->clouds, cloud);
}
