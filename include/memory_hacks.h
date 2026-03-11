#ifndef MEMORY_HACKS_H
#define MEMORY_HACKS_H

#include <stdint.h>
#include <stddef.h>

/**
 * @brief 指针标记 (Pointer Tagging)
 * 
 * 在 64 位系统中，指针通常是对齐的（如 8 字节对齐），
 * 这意味着指针的低 3 位总是 0。我们可以利用这 3 位存储额外信息。
 */
#define TAG_MASK 0x7
#define SET_TAG(ptr, tag) ((void *)((uintptr_t)(ptr) | ((tag) & TAG_MASK)))
#define GET_TAG(ptr) ((uintptr_t)(ptr) & TAG_MASK)
#define GET_PTR(ptr) ((void *)((uintptr_t)(ptr) & ~TAG_MASK))

/**
 * @brief 内存对齐 (Alignment)
 * 
 * 向上对齐到指定的 size (必须是 2 的幂)。
 */
#define ALIGN_UP(addr, size) (((uintptr_t)(addr) + (size) - 1) & ~((size) - 1))
#define ALIGN_DOWN(addr, size) ((uintptr_t)(addr) & ~((size) - 1))

/**
 * @brief 变长结构体 (Flexible Array Member)
 * 
 * C99 标准允许结构体最后一个成员是未知大小的数组。
 * 这种技巧常用于网络协议包或动态分配的缓冲区。
 */
typedef struct {
    size_t len;
    char data[]; // 柔性数组，不占结构体大小
} flex_buffer_t;

/**
 * @brief 匿名联合体与结构体 (C11)
 * 
 * 允许直接访问内部成员，常用于数学库（如向量表示）。
 */
typedef struct {
    union {
        struct { float x, y, z; };
        float v[3];
    };
} vec3_t;

/**
 * @brief 内存屏障 (Memory Barrier)
 * 
 * 防止编译器对内存操作进行重排序。
 */
#define COMPILER_BARRIER() __asm__ __volatile__("" ::: "memory")

/**
 * @brief 获取结构体成员偏移量 (offsetof 的底层实现原理)
 */
#define MY_OFFSETOF(type, member) ((size_t)&(((type *)0)->member))

/**
 * @brief 结构体打包 (Packed)
 * 
 * 告诉编译器不要在结构体成员间添加填充字节。
 */
#define PACKED __attribute__((packed))

#endif // MEMORY_HACKS_H
