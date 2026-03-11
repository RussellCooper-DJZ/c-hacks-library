#ifndef BIT_HACKS_H
#define BIT_HACKS_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief 快速范围判断 [min, max]
 * @brief Fast range check [min, max]
 * @brief Schnelle Bereichsprüfung [min, max]
 * 
 * 原理：利用无符号数溢出特性，将两次判断合并为一次。
 * 如果 x < min，(uint32_t)(x - min) 会变成一个很大的正数。
 * 如果 x > max，(uint32_t)(x - min) 也会大于 (max - min)。
 * Principle: Uses unsigned integer overflow properties to combine two comparisons into one.
 * If x < min, (uint32_t)(x - min) becomes a very large positive number.
 * If x > max, (uint32_t)(x - min) will also be greater than (max - min).
 * Prinzip: Nutzt Eigenschaften des vorzeichenlosen Überlaufs, um zwei Vergleiche zu einem zusammenzufassen.
 * Wenn x < min, wird (uint32_t)(x - min) zu einer sehr großen positiven Zahl.
 * Wenn x > max, wird (uint32_t)(x - min) ebenfalls größer als (max - min).
 */
static inline bool in_range(int32_t x, int32_t min, int32_t max) {
    return (uint32_t)(x - min) <= (uint32_t)(max - min);
}

/**
 * @brief 快速除以 255 (适用于 [0, 65535] 范围)
 * @brief Fast division by 255 (for range [0, 65535])
 * @brief Schnelle Division durch 255 (für den Bereich [0, 65535])
 * 
 * 误差为 0，比直接除法快得多。
 * Error is 0, much faster than direct division.
 * Fehler ist 0, viel schneller als direkte Division.
 */
#define div_255_fast(x) (((x) + (((x) + 257) >> 8)) >> 8)

/**
 * @brief 常数裁剪到 [0, 255]
 * @brief Clamp to constant range [0, 255]
 * @brief Beschneiden auf konstanten Bereich [0, 255]
 * 
 * 无分支实现，避免 CPU 分支预测失败。
 * Branchless implementation to avoid CPU branch prediction failures.
 * Verzweigungslose Implementierung zur Vermeidung von CPU-Branch-Prediction-Fehlern.
 */
static inline int32_t clamp_to_255(int32_t x) {
    return (((255 - x) >> 31) | x) & 255;
}

/**
 * @brief 向上取最近的 2 的幂
 * @brief Get the next power of 2
 * @brief Nächste Zweierpotenz
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
 * @brief Swap two integers (without a temporary variable)
 * @brief Zwei Ganzzahlen tauschen (ohne temporäre Variable)
 * 
 * 注意：如果 a 和 b 指向同一个内存地址，结果会变为 0。
 * Note: If a and b point to the same memory address, the result will be 0.
 * Hinweis: Wenn a und b auf dieselbe Speicheradresse zeigen, wird das Ergebnis 0 sein.
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
 * @brief Check if a number is a power of 2
 * @brief Prüfen, ob eine Zahl eine Zweierpotenz ist
 */
#define is_power_of_2(x) ((x) > 0 && ((x) & ((x) - 1)) == 0)

#endif // BIT_HACKS_H
