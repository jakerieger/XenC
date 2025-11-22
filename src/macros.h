// Author: Jake Rieger
// Created: 11/21/2025.
//

#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * macros.h - Graphics and Game Development Utility Macros (C11)
 *
 * A collection of general-purpose and domain-specific macros
 * with emphasis on memory safety and convenience.
 */

/* ============================================================================
 * GENERAL PURPOSE MACROS
 * ============================================================================ */

/* Array size calculation */
#define X_ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/* Min/Max macros with type safety */
#define X_MIN(a, b)                                                                                                    \
    ({                                                                                                                 \
        __typeof__(a) _a = (a);                                                                                        \
        __typeof__(b) _b = (b);                                                                                        \
        _a < _b ? _a : _b;                                                                                             \
    })

#define X_MAX(a, b)                                                                                                    \
    ({                                                                                                                 \
        __typeof__(a) _a = (a);                                                                                        \
        __typeof__(b) _b = (b);                                                                                        \
        _a > _b ? _a : _b;                                                                                             \
    })

/* Clamp a value between min and max */
#define X_CLAMP(x, min, max) X_MAX((min), X_MIN((x), (max)))

/* Swap two values */
#define X_SWAP(a, b)                                                                                                   \
    do {                                                                                                               \
        __typeof__(a) _tmp = (a);                                                                                      \
        (a)                = (b);                                                                                      \
        (b)                = _tmp;                                                                                     \
    } while (0)

/* Absolute value */
#define X_ABS(x)                                                                                                       \
    ({                                                                                                                 \
        __typeof__(x) _x = (x);                                                                                        \
        _x < 0 ? -_x : _x;                                                                                             \
    })

/* Check if number is power of 2 */
#define X_IS_POW2(x) (((x) != 0) && (((x) & ((x) - 1)) == 0))

/* Align value up to nearest power of 2 boundary */
#define X_ALIGN_UP(x, align) (((x) + ((align) - 1)) & ~((align) - 1))

/* Align value down to nearest power of 2 boundary */
#define X_ALIGN_DOWN(x, align) ((x) & ~((align) - 1))

/* Get offset of a field in a struct */
#define X_OFFSET_OF(type, member) offsetof(type, member)

/* Get container struct from member pointer */
#define X_CONTAINER_OF(ptr, type, member)                                                                              \
    ({                                                                                                                 \
        const __typeof__(((type*)0)->member)* _mptr = (ptr);                                                           \
        (type*)((char*)_mptr - X_OFFSET_OF(type, member));                                                             \
    })

/* Bit manipulation */
#define X_BIT(n) (1U << (n))
#define X_BIT_SET(x, n) ((x) |= X_BIT(n))
#define X_BIT_CLEAR(x, n) ((x) &= ~X_BIT(n))
#define X_BIT_TOGGLE(x, n) ((x) ^= X_BIT(n))
#define X_BIT_CHECK(x, n) (((x) & X_BIT(n)) != 0)

/* Create bitmask */
#define X_BITMASK(nbits) ((1U << (nbits)) - 1)

/* Safe boolean conversion */
#define X_BOOL(x) (!!(x))

/* Stringify */
#define X_STRINGIFY_IMPL(x) #x
#define X_STRINGIFY(x) X_STRINGIFY_IMPL(x)

/* Concatenate */
#define X_CONCAT_IMPL(a, b) a##b
#define X_CONCAT(a, b) X_CONCAT_IMPL(a, b)

/* Unused variable/parameter marker */
#define X_UNUSED(x) ((void)(x))

/* Static assertion with message */
#define X_STATIC_ASSERT(cond, msg) _Static_assert(cond, msg)

/* Likely/Unlikely branch prediction hints */
#if defined(__GNUC__) || defined(__clang__)
    #define X_LIKELY(x) __builtin_expect(!!(x), 1)
    #define X_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
    #define X_LIKELY(x) (x)
    #define X_UNLIKELY(x) (x)
#endif

/* Force inline */
#if defined(__GNUC__) || defined(__clang__)
    #define X_FORCE_INLINE __attribute__((always_inline)) inline
#elif defined(_MSC_VER)
    #define X_FORCE_INLINE __forceinline
#else
    #define X_FORCE_INLINE inline
#endif

/* No inline */
#if defined(__GNUC__) || defined(__clang__)
    #define X_NO_INLINE __attribute__((noinline))
#elif defined(_MSC_VER)
    #define X_NO_INLINE __declspec(noinline)
#else
    #define X_NO_INLINE
#endif

/* ============================================================================
 * MEMORY MANAGEMENT MACROS (SAFETY FOCUSED)
 * ============================================================================ */

/* Safe malloc with type */
#define X_MALLOC(type, count) ((type*)malloc(sizeof(type) * (count)))

/* Safe calloc with type (zeroed memory) */
#define X_CALLOC(type, count) ((type*)calloc((count), sizeof(type)))

/* Safe realloc with type */
#define X_REALLOC(ptr, type, count) ((type*)realloc((ptr), sizeof(type) * (count)))

/* Allocate single object */
#define X_NEW(type) X_CALLOC(type, 1)

/* Safe free that nullifies pointer */
#define X_FREE(ptr)                                                                                                    \
    do {                                                                                                               \
        free(ptr);                                                                                                     \
        (ptr) = NULL;                                                                                                  \
    } while (0)

/* Safe free with type check */
#define X_DELETE(ptr)                                                                                                  \
    do {                                                                                                               \
        if ((ptr) != NULL) {                                                                                           \
            free(ptr);                                                                                                 \
            (ptr) = NULL;                                                                                              \
        }                                                                                                              \
    } while (0)

/* Zero memory */
#define X_ZERO(ptr, type) memset((ptr), 0, sizeof(type))

/* Zero array */
#define X_ZERO_ARRAY(arr) memset((arr), 0, sizeof(arr))

/* Zero struct by pointer */
#define X_ZERO_STRUCT(ptr) memset((ptr), 0, sizeof(*(ptr)))

/* Safe memcpy with bounds checking */
#define X_MEMCPY_SAFE(dest, src, dest_size, src_size)                                                                  \
    do {                                                                                                               \
        size_t _copy_size = X_MIN((dest_size), (src_size));                                                            \
        memcpy((dest), (src), _copy_size);                                                                             \
    } while (0)

/* Duplicate memory */
#define X_MEMDUP(src, size)                                                                                            \
    ({                                                                                                                 \
        void* _new = malloc(size);                                                                                     \
        if (_new != NULL) memcpy(_new, (src), (size));                                                                 \
        _new;                                                                                                          \
    })

/* Check if pointer is aligned */
#define X_IS_ALIGNED(ptr, alignment) ((((uintptr_t)(ptr)) & ((alignment) - 1)) == 0)

/* Safe pointer arithmetic */
#define X_PTR_ADD(ptr, offset) ((void*)((char*)(ptr) + (offset)))
#define X_PTR_SUB(ptr, offset) ((void*)((char*)(ptr) - (offset)))
#define X_PTR_DIFF(ptr1, ptr2) ((size_t)((char*)(ptr1) - (char*)(ptr2)))

/* ============================================================================
 * GRAPHICS & GAME SPECIFIC MACROS
 * ============================================================================ */

/* Color manipulation (RGBA) */
#define X_COLOR_RGBA(r, g, b, a)                                                                                       \
    ((uint32_t)(((uint8_t)(r)) | ((uint8_t)(g) << 8) | ((uint8_t)(b) << 16) | ((uint8_t)(a) << 24)))

#define X_COLOR_RGB(r, g, b) X_COLOR_RGBA(r, g, b, 255)

#define X_COLOR_GET_R(color) ((uint8_t)((color) & 0xFF))
#define X_COLOR_GET_G(color) ((uint8_t)(((color) >> 8) & 0xFF))
#define X_COLOR_GET_B(color) ((uint8_t)(((color) >> 16) & 0xFF))
#define X_COLOR_GET_A(color) ((uint8_t)(((color) >> 24) & 0xFF))

/* Convert float color (0.0-1.0) to byte (0-255) */
#define X_COLOR_F2B(f) ((uint8_t)X_CLAMP((f) * 255.0f, 0.0f, 255.0f))

/* Convert byte color (0-255) to float (0.0-1.0) */
#define X_COLOR_B2F(b) ((float)(b) / 255.0f)

/* Rectangle operations */
#define X_RECT_CONTAINS(rect_x, rect_y, rect_w, rect_h, px, py)                                                        \
    (((px) >= (rect_x)) && ((px) < (rect_x) + (rect_w)) && ((py) >= (rect_y)) && ((py) < (rect_y) + (rect_h)))

/* Check if two rectangles intersect */
#define X_RECT_INTERSECTS(x1, y1, w1, h1, x2, y2, w2, h2)                                                              \
    (!((x1) + (w1) <= (x2) || (x2) + (w2) <= (x1) || (y1) + (h1) <= (y2) || (y2) + (h2) <= (y1)))

/* Degrees to radians */
#define X_DEG2RAD(deg) ((deg) * 0.017453292519943295f)

/* Radians to degrees */
#define X_RAD2DEG(rad) ((rad) * 57.29577951308232f)

/* Linear interpolation */
#define X_LERP(a, b, t) ((a) + ((b) - (a)) * (t))

/* Inverse lerp (find t given a, b, and value) */
#define X_INV_LERP(a, b, v) (((v) - (a)) / ((b) - (a)))

/* Remap value from one range to another */
#define X_REMAP(val, in_min, in_max, out_min, out_max)                                                                 \
    X_LERP((out_min), (out_max), X_INV_LERP((in_min), (in_max), (val)))

/* Smoothstep interpolation */
#define X_SMOOTHSTEP(t) ((t) * (t) * (3.0f - 2.0f * (t)))

/* Check if float values are approximately equal */
#define X_FLOAT_EQ(a, b, epsilon) (X_ABS((a) - (b)) < (epsilon))

/* Default epsilon for float comparison */
#define X_EPSILON 1e-6f

/* Normalize value to 0.0-1.0 range */
#define X_NORMALIZE(val, min, max) X_CLAMP(((val) - (min)) / ((max) - (min)), 0.0f, 1.0f)

/* Convert normalized value back to range */
#define X_DENORMALIZE(val, min, max) ((val) * ((max) - (min)) + (min))

/* 2D Vector operations (requires vec2 struct with x, y) */
#define X_VEC2_DOT(v1, v2) ((v1).x * (v2).x + (v1).y * (v2).y)
#define X_VEC2_LENGTH_SQ(v) ((v).x * (v).x + (v).y * (v).y)

/* 3D Vector operations (requires vec3 struct with x, y, z) */
#define X_VEC3_DOT(v1, v2) ((v1).x * (v2).x + (v1).y * (v2).y + (v1).z * (v2).z)
#define X_VEC3_LENGTH_SQ(v) ((v).x * (v).x + (v).y * (v).y + (v).z * (v).z)

/* ============================================================================
 * ASSET & RESOURCE MANAGEMENT
 * ============================================================================ */

/* Safe string duplication */
#define X_STRDUP_SAFE(str)                                                                                             \
    ({                                                                                                                 \
        const char* _s = (str);                                                                                        \
        char* _dup     = NULL;                                                                                         \
        if (_s != NULL) {                                                                                              \
            size_t _len = strlen(_s) + 1;                                                                              \
            _dup        = (char*)malloc(_len);                                                                         \
            if (_dup != NULL) memcpy(_dup, _s, _len);                                                                  \
        }                                                                                                              \
        _dup;                                                                                                          \
    })

/* Safe string copy with null termination guarantee */
#define X_STRCPY_SAFE(dest, dest_size, src)                                                                            \
    do {                                                                                                               \
        if ((dest) != NULL && (src) != NULL && (dest_size) > 0) {                                                      \
            strncpy((dest), (src), (dest_size) - 1);                                                                   \
            (dest)[(dest_size) - 1] = '\0';                                                                            \
        }                                                                                                              \
    } while (0)

/* String comparison shortcuts */
#define X_STREQ(s1, s2) (strcmp((s1), (s2)) == 0)
#define X_STRNEQ(s1, s2, n) (strncmp((s1), (s2), (n)) == 0)

/* ============================================================================
 * DEBUG & LOGGING MACROS
 * ============================================================================ */

#ifndef NDEBUG
    #define X_DEBUG_PRINT(fmt, ...) fprintf(stderr, "[DEBUG] %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)

    #define X_ASSERT(cond)                                                                                             \
        do {                                                                                                           \
            if (X_UNLIKELY(!(cond))) {                                                                                 \
                fprintf(stderr, "Assertion failed: %s, file %s, line %d\n", #cond, __FILE__, __LINE__);                \
                abort();                                                                                               \
            }                                                                                                          \
        } while (0)

    #define X_ASSERT_MSG(cond, msg)                                                                                    \
        do {                                                                                                           \
            if (X_UNLIKELY(!(cond))) {                                                                                 \
                fprintf(stderr, "Assertion failed: %s (%s), file %s, line %d\n", #cond, msg, __FILE__, __LINE__);      \
                abort();                                                                                               \
            }                                                                                                          \
        } while (0)
#else
    #define X_DEBUG_PRINT(fmt, ...) ((void)0)
    #define X_ASSERT(cond) ((void)0)
    #define X_ASSERT_MSG(cond, msg) ((void)0)
#endif

#define X_PRINT_ERROR(fmt, ...) fprintf(stderr, "[ERROR] %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)

/* Runtime error checking (always active) */
#define X_CHECK(cond)                                                                                                  \
    do {                                                                                                               \
        if (X_UNLIKELY(!(cond))) {                                                                                     \
            fprintf(stderr, "Check failed: %s, file %s, line %d\n", #cond, __FILE__, __LINE__);                        \
            abort();                                                                                                   \
        }                                                                                                              \
    } while (0)

#define X_CHECK_MSG(cond, msg)                                                                                         \
    do {                                                                                                               \
        if (X_UNLIKELY(!(cond))) {                                                                                     \
            fprintf(stderr, "Check failed: %s (%s), file %s, line %d\n", #cond, msg, __FILE__, __LINE__);              \
            abort();                                                                                                   \
        }                                                                                                              \
    } while (0)

/* Verify allocation succeeded */
#define X_CHECK_ALLOC(ptr) X_CHECK_MSG((ptr) != NULL, "Memory allocation failed")

/* ============================================================================
 * PERFORMANCE & OPTIMIZATION
 * ============================================================================ */

/* Prefetch memory (compiler-specific) */
#if defined(__GNUC__) || defined(__clang__)
    #define X_PREFETCH(addr) __builtin_prefetch(addr)
    #define X_PREFETCH_WRITE(addr) __builtin_prefetch(addr, 1)
#else
    #define X_PREFETCH(addr) ((void)0)
    #define X_PREFETCH_WRITE(addr) ((void)0)
#endif

/* Restrict pointer keyword */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define X_RESTRICT restrict
#elif defined(__GNUC__) || defined(__clang__)
    #define X_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define X_RESTRICT __restrict
#else
    #define X_RESTRICT
#endif

/* Function attributes */
#if defined(__GNUC__) || defined(__clang__)
    #define X_PURE __attribute__((pure))
    #define X_CONST __attribute__((const))
    #define X_HOT __attribute__((hot))
    #define X_COLD __attribute__((cold))
#else
    #define X_PURE
    #define X_CONST
    #define X_HOT
    #define X_COLD
#endif

/* ============================================================================
 * FOREACH LOOP HELPERS
 * ============================================================================ */

/* Iterate over array with automatic size detection */
#define X_FOREACH(type, var, array) for (type* var = (array); var < (array) + X_ARRAY_SIZE(array); ++var)

/* Iterate with index */
#define X_FOREACH_I(type, var, array, index_var)                                                                       \
    for (size_t index_var = 0, _keep = 1; _keep && index_var < X_ARRAY_SIZE(array); _keep = !_keep, ++index_var)       \
        for (type* var = &(array)[index_var]; _keep; _keep = !_keep)

/* ============================================================================
 * TIMER MACROS
 * ============================================================================ */

/* Simple frame time calculation helper */
#define X_DELTA_TIME(last_time, current_time) ((float)((current_time) - (last_time)))

/* Convert seconds to milliseconds */
#define X_SEC_TO_MS(sec) ((sec) * 1000.0f)

/* Convert milliseconds to seconds */
#define X_MS_TO_SEC(ms) ((ms) / 1000.0f)

/* FPS calculation from delta time */
#define X_FPS_FROM_DT(dt) (1.0f / (dt))
