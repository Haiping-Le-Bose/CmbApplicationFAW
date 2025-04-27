/*
 * $QNXLicenseC:
 * Copyright 2018, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.   Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

#ifndef _LIB_COMPAT_ENDIAN_H_INCLUDED
#define _LIB_COMPAT_ENDIAN_H_INCLUDED


/*
 * This header makes the endian macros defined in Neutrino's gulliver.h available on supported host platforms (darwin, linux and
 * win64).
 *
 * This header also makes BSD's endian conversion API available for use on Neutrino and supported host platforms for the following
 * reasons:
 *
 *     1.  While most OSes (including Neutrino) define a unique API for fixed-size integer endian conversion, Neutrino and
 *         GNU/Linux both make BSD's htole<n>, le<n>toh, htobe<n> and be<n>toh functions available, making them a defacto standard.
 *
 *     2.  The htole<n>, le<n>toh, htobe<n> and be<n>toh functions use a to-host/from-host notation which expresses the intent of
 *         each conversion more clearly than do the ENDIAN_LE<n> and ENDIAN_BE<n> macros.
 *
 *     3.  The le<n>enc, le<n>dec, be<n>enc and be<n>dec functions provide a combined unaligned access + endian conversion
 *         capability not offered by Neutrino's gulliver.h API. They are useful for marshalling/unmarshalling values to/from a
 *         serialized form.
 *
 *     4.  BSD's endian conversion API is composed of functions rather than macros, so the developer doesn't need to worry about
 *         multiple evaluations of arguments when using it.
 *
 * Refer to the following manual page for documentation of BSD's endian conversion API:
 *
 *     https://www.freebsd.org/cgi/man.cgi?query=htole16&manpath=FreeBSD+11.1-RELEASE+and+Ports
 */


#include <stdint.h>

#if defined(__QNX__)
#include <gulliver.h>
#include <net/netbyte.h>
#elif defined(__LINUX__)
#include <byteswap.h>
#include <endian.h>
#elif defined(__DARWIN__)
#include <libkern/OSByteOrder.h>
#elif defined(__MINGW32__)
#include <sys/param.h>
#endif


/* --- Neutrino's __LITTLEENDIAN__ and __BIGENDIAN__ macros ---
 *
 * Currently, the build infrastructure is responsible for defining either the __LITTLEENDIAN__ or __BIGENDIAN__ macro. The following
 * preprocessor logic verifies that exactly one of these macros is defined. If this is a host platform, verify that the relevant
 * toolchain's indicator of endianness is consistent with the state of the __LITTLEENDIAN__/__BIGENDIAN__ macros. */

#if defined(__LITTLEENDIAN__) && defined(__BIGENDIAN__)
#error "Both __LITTLEENDIAN__ and __BIGENDIAN__ are defined"
#elif !defined(__LITTLEENDIAN__) && !defined(__BIGENDIAN__)
#error "Neither __LITTLEENDIAN__ nor __BIGENDIAN__ is defined"
#elif defined(__LINUX__)
#if ( defined(__LITTLEENDIAN__) && ( __BYTE_ORDER != __LITTLE_ENDIAN ) ) || \
        ( defined(__BIGENDIAN__) && ( __BYTE_ORDER != __BIG_ENDIAN ) )
#error "Mismatch between __BYTE_ORDER and __BIGENDIAN__/__LITTLEENDIAN__ macros"
#endif
#elif defined(__DARWIN__)
#if ( defined(__LITTLEENDIAN__) && ( !defined(__LITTLE_ENDIAN__) || defined(__BIG_ENDIAN__) ) ) || \
        ( defined(__BIGENDIAN__) && ( defined(__LITTLE_ENDIAN__) || !defined(__BIG_ENDIAN__) ) )
#error "Mismatch between __BIG_ENDIAN__/__LITTLE_ENDIAN__ and __BIGENDIAN__/__LITTLEENDIAN__ macros"
#endif
#elif defined(__MINGW32__)
#if ( defined(__LITTLEENDIAN__) && ( BYTE_ORDER != LITTLE_ENDIAN ) ) || \
        ( defined(__BIGENDIAN__) && ( BYTE_ORDER != BIG_ENDIAN ) )
#error "Mismatch between BYTE_ORDER and __BIGENDIAN__/__LITTLEENDIAN__ macros"
#endif
#endif


/* --- Neutrino's ENDIAN_RET<n> macros --- */

#if defined(__LINUX__)

#define ENDIAN_RET16(value)  bswap_16(value)
#define ENDIAN_RET32(value)  bswap_32(value)
#define ENDIAN_RET64(value)  bswap_64(value)

#elif defined(__DARWIN__)

#define ENDIAN_RET16(value)  OSSwapInt16(value)
#define ENDIAN_RET32(value)  OSSwapInt32(value)
#define ENDIAN_RET64(value)  OSSwapInt64(value)

#elif defined(__MINGW32__)

/* MinGW ("minimalist GNU for Windows") uses GCC by definition, so leverage GCC's byteswap builtins */
#define ENDIAN_RET16(value)  __builtin_bswap16(value)
#define ENDIAN_RET32(value)  __builtin_bswap32(value)
#define ENDIAN_RET64(value)  __builtin_bswap64(value)

#endif



#if !defined(__QNX__)

/* --- QNX's ENDIAN_SWAP<n>, ENDIAN_STRINGNAME, ENDIAN_LE<n>, ENDIAN_BE<n> and ENDIAN_DE<n> macros --- */
/* These macros were copied from gulliver.h. The types defined in QNX's sys/platform.h have been replaced with the
 * corresponding ones from stdint.h. Parameters in the ISO/IEC 9899 reserved namespace were renamed. */

#define ENDIAN_SWAP16(obj)  (*(uint16_t *)(obj) = (uint16_t)ENDIAN_RET16(*(uint16_t *)(obj)))
#define ENDIAN_SWAP32(obj)  (*(uint32_t *)(obj) = ENDIAN_RET32(*(uint32_t *)(obj)))
#define ENDIAN_SWAP64(obj)  (*(uint64_t *)(obj) = ENDIAN_RET64(*(uint64_t *)(obj)))

#if defined(__LITTLEENDIAN__)

#define ENDIAN_STRINGNAME   "le"

#define ENDIAN_LE16(value)  ((uint16_t)(value))
#define ENDIAN_LE32(value)  ((uint32_t)(value))
#define ENDIAN_LE64(value)  ((uint64_t)(value))
#define ENDIAN_BE16(value)  ((uint16_t)(ENDIAN_RET16(value)))
#define ENDIAN_BE32(value)  ((uint32_t)(ENDIAN_RET32(value)))
#define ENDIAN_BE64(value)  ((uint64_t)(ENDIAN_RET64(value)))

#elif defined(__BIGENDIAN__)

#define ENDIAN_STRINGNAME   "be"

#define ENDIAN_LE16(value)  ((uint16_t)(ENDIAN_RET16(value)))
#define ENDIAN_LE32(value)  ((uint32_t)(ENDIAN_RET32(value)))
#define ENDIAN_LE64(value)  ((uint64_t)(ENDIAN_RET64(value)))
#define ENDIAN_BE16(value)  ((uint16_t)(value))
#define ENDIAN_BE32(value)  ((uint32_t)(value))
#define ENDIAN_BE64(value)  ((uint64_t)(value))

#endif

#if defined(VARIANT_dev_be) && defined(VARIANT_dev_le)
#error "VARIANT_dev_le and VARIANT_dev_be cannot both be defined"
#elif (defined(VARIANT_dev_be) && defined(__LITTLEENDIAN__)) || (defined(VARIANT_dev_le) && defined(__BIGENDIAN__))
#define ENDIAN_DE16(value)  ENDIAN_RET16(value)
#define ENDIAN_DE32(value)  ENDIAN_RET32(value)
#define ENDIAN_DE64(value)  ENDIAN_RET64(value)
#else
#define ENDIAN_DE16(value)  (value)
#define ENDIAN_DE32(value)  (value)
#define ENDIAN_DE64(value)  (value)
#endif

#endif


/* --- Neutrino's UNALIGNED_RET<n> and UNALIGNED_PUT<n> macros --- */

#if defined(__LINUX__) || defined(__MINGW32__)

/* For some reason, the build infrastructure defines __X86__ but not __X86_64__ when targetting linux/x86_64, so check both */
#if defined(__X86__) || defined(__X86_64__)

/* Adapted from Neutrino's x86/cpuinline.h and x86_64/cpuinline.h */

typedef __attribute__((__may_alias__)) uint16_t lib_compat_endian_may_alias_uint16_t;
typedef __attribute__((__may_alias__)) uint32_t lib_compat_endian_may_alias_uint32_t;
typedef __attribute__((__may_alias__)) uint64_t lib_compat_endian_may_alias_uint64_t;

#define UNALIGNED_RET16(src)         ((uint16_t)*(const volatile lib_compat_endian_may_alias_uint16_t *)(src))
#define UNALIGNED_RET32(src)         ((uint32_t)*(const volatile lib_compat_endian_may_alias_uint32_t *)(src))
#define UNALIGNED_RET64(src)         ((uint64_t)*(const volatile lib_compat_endian_may_alias_uint64_t *)(src))
#define UNALIGNED_PUT16(dst, value)  \
        do { \
            *(volatile lib_compat_endian_may_alias_uint16_t *)(dst) = (value); \
        } while ( 0 )
#define UNALIGNED_PUT32(dst, value)  \
        do { \
            *(volatile lib_compat_endian_may_alias_uint32_t *)(dst) = (value); \
        } while ( 0 )
#define UNALIGNED_PUT64(dst, value)  \
        do { \
            *(volatile lib_compat_endian_may_alias_uint64_t *)(dst) = (value); \
        } while ( 0 )

#else
#error "Missing implementation of UNALIGNED_RET<n> and UNALIGNED_PUT<n> for architectures other than x86 and x86_64"
#endif

#elif defined(__DARWIN__)

#define UNALIGNED_RET16(src)         _OSReadInt16((src), 0)
#define UNALIGNED_RET32(src)         _OSReadInt32((src), 0)
#define UNALIGNED_RET64(src)         _OSReadInt64((src), 0)
#define UNALIGNED_PUT16(dst, value)  _OSWriteInt16((dst), 0, (value))
#define UNALIGNED_PUT32(dst, value)  _OSWriteInt32((dst), 0, (value))
#define UNALIGNED_PUT64(dst, value)  _OSWriteInt64((dst), 0, (value))

#endif


/* --- BSD's bswap<n> functions --- */

#if !defined(__QNX__) || (defined(__QNX__) && !defined(bswap16))
/* For __QNX__, bswap*() are defined in net/netbyte.h in the io-sock SDK headers */
static inline uint16_t bswap16(const uint16_t value__)
{
    return ENDIAN_RET16(value__);
}

static inline uint32_t bswap32(const uint32_t value__)
{
    return ENDIAN_RET32(value__);
}

static inline uint64_t bswap64(const uint64_t value__)
{
    return ENDIAN_RET64(value__);
}

#endif

/* --- BSD's htole<n>, le<n>toh, htobe<n> and be<n>toh functions --- */

#if defined(__QNX__)

/* Already defined by net/netbyte.h on Neutrino. */

#elif defined(__LINUX__) && defined(__GLIBC__) && ( defined(__USE_BSD) || defined(__USE_MISC) )

/* Already defined by endian.h on GNU/Linux. */

#else

static inline uint16_t htole16(const uint16_t value__)
{
    return ENDIAN_LE16(value__);
}

static inline uint32_t htole32(const uint32_t value__)
{
    return ENDIAN_LE32(value__);
}

static inline uint64_t htole64(const uint64_t value__)
{
    return ENDIAN_LE64(value__);
}

static inline uint16_t le16toh(const uint16_t value__)
{
    return ENDIAN_LE16(value__);
}

static inline uint32_t le32toh(const uint32_t value__)
{
    return ENDIAN_LE32(value__);
}

static inline uint64_t le64toh(const uint64_t value__)
{
    return ENDIAN_LE64(value__);
}

static inline uint16_t htobe16(const uint16_t value__)
{
    return ENDIAN_BE16(value__);
}

static inline uint32_t htobe32(const uint32_t value__)
{
    return ENDIAN_BE32(value__);
}

static inline uint64_t htobe64(const uint64_t value__)
{
    return ENDIAN_BE64(value__);
}

static inline uint16_t be16toh(const uint16_t value__)
{
    return ENDIAN_BE16(value__);
}

static inline uint32_t be32toh(const uint32_t value__)
{
    return ENDIAN_BE32(value__);
}

static inline uint64_t be64toh(const uint64_t value__)
{
    return ENDIAN_BE64(value__);
}

#endif


/* --- BSD's le<n>enc, le<n>dec, be<n>enc and be<n>dec functions --- */

/* Temporary macros for common logic */
#define LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_GET16(src)  \
        ((uint16_t)( \
                (uint_fast16_t)(((const uint8_t *)(src))[1]) | \
                ((uint_fast16_t)(((const uint8_t *)(src))[0]) << 8)))

#define LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_GET32(src)  \
        ((uint32_t)( \
                (uint_fast32_t)(((const uint8_t *)(src))[3]) | \
                ((uint_fast32_t)(((const uint8_t *)(src))[2]) << 8) | \
                ((uint_fast32_t)(((const uint8_t *)(src))[1]) << 16) | \
                ((uint_fast32_t)(((const uint8_t *)(src))[0]) << 24)))

#define LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_GET64(src)  \
        ((uint64_t)( \
                (uint_fast64_t)(((const uint8_t *)(src))[7]) | \
                ((uint_fast64_t)(((const uint8_t *)(src))[6]) << 8) | \
                ((uint_fast64_t)(((const uint8_t *)(src))[5]) << 16) | \
                ((uint_fast64_t)(((const uint8_t *)(src))[4]) << 24) | \
                ((uint_fast64_t)(((const uint8_t *)(src))[3]) << 32) | \
                ((uint_fast64_t)(((const uint8_t *)(src))[2]) << 40) | \
                ((uint_fast64_t)(((const uint8_t *)(src))[1]) << 48) | \
                ((uint_fast64_t)(((const uint8_t *)(src))[0]) << 56)))

static inline uint16_t le16dec(const void * const src__)
{
#if defined(__LITTLEENDIAN__)
/* Workaround for warning in gulliver.h macro (JI#2246919) */
#if defined(__QNX__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    return UNALIGNED_RET16(src__);
#if defined(__QNX__)
#pragma GCC diagnostic pop
#endif
#else
    return LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_GET16(src__);
#endif
}

static inline uint32_t le32dec(const void * const src__)
{
#if defined(__LITTLEENDIAN__)
/* Workaround for warning in gulliver.h macro (JI#2246919) */
#if defined(__QNX__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif
    return UNALIGNED_RET32(src__);
#if defined(__QNX__)
#pragma GCC diagnostic pop
#endif
#else
    return LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_GET32(src__);
#endif
}

static inline uint64_t le64dec(const void * const src__)
{
#if defined(__LITTLEENDIAN__)
/* Workaround for warning in gulliver.h macro (JI#2246919) */
#if defined(__QNX__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif
    return UNALIGNED_RET64(src__);
#if defined(__QNX__)
#pragma GCC diagnostic pop
#endif
#else
    return LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_GET64(src__);
#endif
}

static inline uint16_t be16dec(const void * const src__)
{
#if defined(__LITTLEENDIAN__)
    return LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_GET16(src__);
#else
/* Workaround for warning in gulliver.h macro (JI#2246919) */
#if defined(__QNX__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    return UNALIGNED_RET16(src__);
#if defined(__QNX__)
#pragma GCC diagnostic pop
#endif
#endif
}

static inline uint32_t be32dec(const void * const src__)
{
#if defined(__LITTLEENDIAN__)
    return LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_GET32(src__);
#else
/* Workaround for warning in gulliver.h macro (JI#2246919) */
#if defined(__QNX__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif
    return UNALIGNED_RET32(src__);
#if defined(__QNX__)
#pragma GCC diagnostic pop
#endif
#endif
}

static inline uint64_t be64dec(const void * const src__)
{
#if defined(__LITTLEENDIAN__)
    return LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_GET64(src__);
#else
/* Workaround for warning in gulliver.h macro (JI#2246919) */
#if defined(__QNX__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif
    return UNALIGNED_RET64(src__);
#if defined(__QNX__)
#pragma GCC diagnostic pop
#endif
#endif
}

#undef LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_GET16
#undef LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_GET32
#undef LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_GET64

/* Temporary macros for common logic */
#define LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_PUT16(dst, value)  \
        do { \
            ((uint8_t *)(dst))[0] = (uint8_t)(((value) >> 8) & 0xFF); \
            ((uint8_t *)(dst))[1] = (uint8_t)((value) & 0xFF); \
        } while ( 0 )

#define LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_PUT32(dst, value)  \
        do { \
            ((uint8_t *)(dst))[0] = (uint8_t)(((value) >> 24) & 0xFF); \
            ((uint8_t *)(dst))[1] = (uint8_t)(((value) >> 16) & 0xFF); \
            ((uint8_t *)(dst))[2] = (uint8_t)(((value) >> 8) & 0xFF); \
            ((uint8_t *)(dst))[3] = (uint8_t)((value) & 0xFF); \
        } while ( 0 )

#define LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_PUT64(dst, value)  \
        do { \
            ((uint8_t *)(dst))[0] = (uint8_t)(((value) >> 56) & 0xFF); \
            ((uint8_t *)(dst))[1] = (uint8_t)(((value) >> 48) & 0xFF); \
            ((uint8_t *)(dst))[2] = (uint8_t)(((value) >> 40) & 0xFF); \
            ((uint8_t *)(dst))[3] = (uint8_t)(((value) >> 32) & 0xFF); \
            ((uint8_t *)(dst))[4] = (uint8_t)(((value) >> 24) & 0xFF); \
            ((uint8_t *)(dst))[5] = (uint8_t)(((value) >> 16) & 0xFF); \
            ((uint8_t *)(dst))[6] = (uint8_t)(((value) >> 8) & 0xFF); \
            ((uint8_t *)(dst))[7] = (uint8_t)((value) & 0xFF); \
        } while ( 0 )

static inline void le16enc(void * const dst__, const uint16_t value__)
{
#if defined(__LITTLEENDIAN__)
/* Workaround for warning in gulliver.h macro (JI#2246919) */
#if defined(__QNX__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    UNALIGNED_PUT16(dst__, value__);
#if defined(__QNX__)
#pragma GCC diagnostic pop
#endif
#else
    LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_PUT16(dst__, value__);
#endif
}

static inline void le32enc(void * const dst__, const uint32_t value__)
{
#if defined(__LITTLEENDIAN__)
/* Workaround for warning in gulliver.h macro (JI#2246919) */
#if defined(__QNX__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    UNALIGNED_PUT32(dst__, value__);
#if defined(__QNX__)
#pragma GCC diagnostic pop
#endif
#else
    LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_PUT32(dst__, value__);
#endif
}

static inline void le64enc(void * const dst__, const uint64_t value__)
{
#if defined(__LITTLEENDIAN__)
/* Workaround for warning in gulliver.h macro (JI#2246919) */
#if defined(__QNX__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    UNALIGNED_PUT64(dst__, value__);
#if defined(__QNX__)
#pragma GCC diagnostic pop
#endif
#else
    LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_PUT64(dst__, value__);
#endif
}

static inline void be16enc(void * const dst__, const uint16_t value__)
{
#if defined(__LITTLEENDIAN__)
    LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_PUT16(dst__, value__);
#else
/* Workaround for warning in gulliver.h macro (JI#2246919) */
#if defined(__QNX__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    UNALIGNED_PUT16(dst__, value__);
#if defined(__QNX__)
#pragma GCC diagnostic pop
#endif
#endif
}

static inline void be32enc(void * const dst__, const uint32_t value__)
{
#if defined(__LITTLEENDIAN__)
    LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_PUT32(dst__, value__);
#else
/* Workaround for warning in gulliver.h macro (JI#2246919) */
#if defined(__QNX__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    UNALIGNED_PUT32(dst__, value__);
#if defined(__QNX__)
#pragma GCC diagnostic pop
#endif
#endif
}

static inline void be64enc(void * const dst__, const uint64_t value__)
{
#if defined(__LITTLEENDIAN__)
    LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_PUT64(dst__, value__);
#else
/* Workaround for warning in gulliver.h macro (JI#2246919) */
#if defined(__QNX__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    UNALIGNED_PUT64(dst__, value__);
#if defined(__QNX__)
#pragma GCC diagnostic pop
#endif
#endif
}

#undef LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_PUT16
#undef LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_PUT32
#undef LIB_COMPAT_ENDIAN_UNALIGNED_SWAPPED_PUT64


#endif /* #ifndef _LIB_COMPAT_ENDIAN_H_INCLUDED */
