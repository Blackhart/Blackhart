#ifndef __BK_SCENE_H__
#define __BK_SCENE_H__

#include "pil\__BkExport.h"

#include "core\BkEntity.h"
#include "core\BkList.h"

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API void			BkScene_AddEntity(BkEntity* pEntity);
extern BK_API void			BkScene_RemoveEntity(BkEntity* pEntity);
extern BK_API BkList const*	BkScene_GetEntities(void);

#endif