// Author: Jake Rieger
// Created: 11/21/2025.
//

#pragma once

#include "stdint.h"
#include "stdbool.h"

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef uintptr_t uptr;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef intptr_t iptr;

#if defined(__GNUC__) || defined(__clang__)
typedef __uint128_t u128;
typedef __int128_t s128;
#endif

typedef float f32;
typedef double f64;