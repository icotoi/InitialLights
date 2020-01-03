#pragma once

#include <QtCore/qglobal.h>

#if defined(INITIALLIGHTS_LIBRARY)
#  if defined(_MSC_VER)
#    define INITIALLIGHTSSHARED_EXPORT
#  else
#    define INITIALLIGHTSSHARED_EXPORT Q_DECL_EXPORT
#  endif
#else
#  if defined(_MSC_VER)
#    define INITIALLIGHTSSHARED_EXPORT
#  else
#    define INITIALLIGHTSSHARED_EXPORT Q_DECL_IMPORT
#  endif
#endif

#define SCENE_COUNT 6
