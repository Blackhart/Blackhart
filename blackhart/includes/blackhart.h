#ifndef __BK_BLACKHART_H__
#define __BK_BLACKHART_H__

/**
 * @file blackhart.h
 * @brief The main header file for the Blackhart library.
 *
 * This file includes all the necessary headers for the Blackhart library and
 * provides the public API for initializing and uninitializing the library.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkExport.h"
#include "foundation/BkFoundation.h"
#include "renderer/BkPointCloud.h"
#include "renderer/BkRenderer.h"
#include "renderer/BkScene.h"

// ~~~~~ Dcl(PUBLIC) ~~~~~

/*! \brief Initializes Blackhart.
 */
extern BK_API void BkInitialize(void);

/*! \brief Uninitializes Blackhart.
 */
extern BK_API void BkUninitialize(void);

#endif