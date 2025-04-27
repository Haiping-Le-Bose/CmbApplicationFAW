#ifndef __ENDIAN_H
#define __ENDIAN_H 1

#include "compat_endian.h"

#ifndef __LINUX__
#define 			__LITTLE_ENDIAN		'L'
#define 			__BIG_ENDIAN		'B'
#endif

#if defined(__LITTLEENDIAN__)
#define				__BYTE_ORDER		__LITTLE_ENDIAN
#else
#define				__BYTE_ORDER		__BIG_ENDIAN
#endif



#endif /* ENDIAN_H */
