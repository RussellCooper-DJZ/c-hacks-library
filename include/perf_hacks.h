#ifndef PERF_HACKS_H
#define PERF_HACKS_H

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Duff's Device (达夫设备)
 * @brief Duff's Device
 * @brief Duff's Device
 * 
 * 经典的循环展开技巧，利用 switch-case 语句的 fall-through 特性。
 * 适用于处理剩余不足 8 个字节的情况。
 * A classic loop unrolling technique that uses the fall-through characteristic of switch-case statements.
 * Suitable for handling remaining data not divisible by 8.
 * Eine klassische Schleifenentrollungstechnik, die die Fall-Through-Eigenschaft von switch-case-Anweisungen nutzt.
 * Geeignet für die Verarbeitung von Restdaten, die nicht durch 8 teilbar sind.
 */
static inline void duff_copy(char *to, char *from, size_t count) {
    size_t n = (count + 7) / 8;
    switch (count % 8) {
        case 0: do { *to++ = *from++;
        case 7:      *to++ = *from++;
        case 6:      *to++ = *from++;
        case 5:      *to++ = *from++;
        case 4:      *to++ = *from++;
        case 3:      *to++ = *from++;
        case 2:      *to++ = *from++;
        case 1:      *to++ = *from++;
                } while (--n > 0);
    }
}

/**
 * @brief 更好的循环展开宏 (CPU_LOOP_UNROLL_4X)
 * @brief Better loop unrolling macro (CPU_LOOP_UNROLL_4X)
 * @brief Besseres Loop-Unrolling-Makro (CPU_LOOP_UNROLL_4X)
 * 
 * 分别定义 1x, 2x, 4x 的操作，减少循环次数。
 * Defines 1x, 2x, and 4x operations separately to reduce loop iterations.
 * Definiert 1x, 2x und 4x Operationen separat, um die Anzahl der Schleifendurchläufe zu reduzieren.
 */
#define CPU_LOOP_UNROLL_4X(actionx1, actionx2, actionx4, width) do { \
    unsigned long __width = (unsigned long)(width);    \
    unsigned long __increment = __width >> 2; \
    for (; __increment > 0; __increment--) { actionx4; }    \
    if (__width & 2) { actionx2; } \
    if (__width & 1) { actionx1; } \
} while (0)

/**
 * @brief 预取指令 (Prefetch)
 * @brief Prefetch instruction
 * @brief Prefetch-Anweisung
 * 
 * 告诉 CPU 提前将内存数据加载到缓存中。
 * Informs the CPU to load memory data into the cache in advance.
 * Informiert die CPU, Speicherdaten im Voraus in den Cache zu laden.
 */
#if defined(__GNUC__) || defined(__clang__)
#define PREFETCH(addr, rw, locality) __builtin_prefetch(addr, rw, locality)
#else
#define PREFETCH(addr, rw, locality)
#endif

/**
 * @brief 静态内联 (Static Inline)
 * @brief Static Inline
 * @brief Statische Inline
 * 
 * 建议编译器内联函数，减少函数调用开销。
 * Suggests to the compiler to inline the function, reducing function call overhead.
 * Schlägt dem Compiler vor, die Funktion zu inlinieren, wodurch der Funktionsaufruf-Overhead reduziert wird.
 */
#ifndef INLINE
#define INLINE static inline __attribute__((always_inline))
#endif

/**
 * @brief 零初始化 (Zero Init)
 * @brief Zero Initialization
 * @brief Nullinitialisierung
 * 
 * 利用 GCC 扩展或 C99 标准进行快速初始化。
 * Uses GCC extensions or C99 standard for fast initialization.
 * Verwendet GCC-Erweiterungen oder den C99-Standard für schnelle Initialisierung.
 */
#define ZERO_INIT(obj) memset(&(obj), 0, sizeof(obj))

/**
 * @brief 构造函数与析构函数 (GCC/Clang)
 * @brief Constructor and Destructor (GCC/Clang)
 * @brief Konstruktor und Destruktor (GCC/Clang)
 * 
 * 在 main 函数执行前/后自动调用的函数。
 * Functions automatically called before/after main function execution.
 * Funktionen, die automatisch vor/nach der Ausführung der main-Funktion aufgerufen werden.
 */
#define CONSTRUCTOR __attribute__((constructor))
#define DESTRUCTOR __attribute__((destructor))

#endif // PERF_HACKS_H
