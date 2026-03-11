#ifndef BIT_HACKS_H
#define BIT_HACKS_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief 快速范围判断 [min, max]
 * 
 * 原理：利用无符号数溢出特性，将两次判断合并为一次。
 * 如果 x < min，(uint32_t)(x - min) 会变成一个很大的正数。
 * 如果 x > max，(uint32_t)(x - min) 也会大于 (max - min)。
 */
static inline bool in_range(int32_t x, int32_t min, int32_t max) {
    return (uint32_t)(x - min) <= (uint32_t)(max - min);
}

/**
 * @brief 快速除以 255 (适用于 [0, 65535] 范围)
 * 
 * 误差为 0，比直接除法快得多。
 */
#define div_255_fast(x) (((x) + (((x) + 257) >> 8)) >> 8)

/**
 * @brief 常数裁剪到 [0, 255]
 * 
 * 无分支实现，避免 CPU 分支预测失败。
 */
static inline int32_t clamp_to_255(int32_t x) {
    return (((255 - x) >> 31) | x) & 255;
}

/**
 * @brief 向上取最近的 2 的幂
 */
static inline uint32_t next_power_of_2(uint32_t x) {
    if (x == 0) return 1;
    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x + 1;
}

/**
 * @brief 交换两个整数 (不使用临时变量)
 * 
 * 注意：如果 a 和 b 指向同一个内存地址，结果会变为 0。
 */
#define SWAP_XOR(a, b) do { \
    if (&(a) != &(b)) {     \
        (a) ^= (b);         \
        (b) ^= (a);         \
        (a) ^= (b);         \
    }                       \
} while (0)

/**
 * @brief 判断是否为 2 的幂
 */
#define is_power_of_2(x) ((x) > 0 && ((x) & ((x) - 1)) == 0)

#endif // BIT_HACKS_H
