#ifndef __BK_SCENE_H__
#define __BK_SCENE_H__

#include "pil\__BkExport.h"

#include "core\BkEntity.h"
#include "core\BkArray.h"

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API void			BkScene_AddEntity(struct BkEntity* entity);
extern BK_API void			BkScene_RemoveEntity(struct BkEntity* entity);
extern BK_API struct BkArray const*	BkScene_GetEntities(void);

#endif