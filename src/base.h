#pragma once

#include <concepts>
#include <cstdint>
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;
typedef double f64;

template <typename T>
concept UNum = std::same_as<T, u8> || std::same_as<T, u16> ||
               std::same_as<T, u32> || std::same_as<T, u64>;

template <UNum N> static inline void SetBit(N &num, N bit_num, bool b) {
    num = (num & ~((N)1 << bit_num)) | ((N)b << bit_num);
}

template <UNum N> static inline bool GetBit(N num, N bit_num) {
    return (num & (1 << bit_num)) != 0;
}
