#ifndef MEMORY_HACKS_H
#define MEMORY_HACKS_H

#include <stdint.h>
#include <stddef.h>

/**
 * @brief 指针标记 (Pointer Tagging)
 * @brief Pointer Tagging
 * @brief Zeiger-Tagging
 * 
 * 在 64 位系统中，指针通常是对齐的（如 8 字节对齐），
 * 这意味着指针的低 3 位总是 0。我们可以利用这 3 位存储额外信息。
 * In 64-bit systems, pointers are typically aligned (e.g., 8-byte aligned),
 * meaning the lower 3 bits of a pointer are always 0. We can use these 3 bits to store extra information.
 * In 64-Bit-Systemen sind Zeiger typischerweise ausgerichtet (z.B. 8-Byte-Ausrichtung),
 * was bedeutet, dass die unteren 3 Bits eines Zeigers immer 0 sind. Wir können diese 3 Bits nutzen, um zusätzliche Informationen zu speichern.
 */
#define TAG_MASK 0x7
#define SET_TAG(ptr, tag) ((void *)((uintptr_t)(ptr) | ((tag) & TAG_MASK)))
#define GET_TAG(ptr) ((uintptr_t)(ptr) & TAG_MASK)
#define GET_PTR(ptr) ((void *)((uintptr_t)(ptr) & ~TAG_MASK))

/**
 * @brief 内存对齐 (Alignment)
 * @brief Memory Alignment
 * @brief Speicherausrichtung
 * 
 * 向上对齐到指定的 size (必须是 2 的幂)。
 * Align up to the specified size (must be a power of 2).
 * Auf die angegebene Größe ausrichten (muss eine Zweierpotenz sein).
 */
#define ALIGN_UP(addr, size) (((uintptr_t)(addr) + (size) - 1) & ~((size) - 1))
#define ALIGN_DOWN(addr, size) ((uintptr_t)(addr) & ~((size) - 1))

/**
 * @brief 变长结构体 (Flexible Array Member)
 * @brief Flexible Array Member
 * @brief Flexibles Array-Mitglied
 * 
 * C99 标准允许结构体最后一个成员是未知大小的数组。
 * 这种技巧常用于网络协议包或动态分配的缓冲区。
 * The C99 standard allows the last member of a struct to be an array of unknown size.
 * This technique is often used for network protocol packets or dynamically allocated buffers.
 * Der C99-Standard erlaubt, dass das letzte Mitglied einer Struktur ein Array unbekannter Größe ist.
 * Diese Technik wird oft für Netzwerkprotokollpakete oder dynamisch zugewiesene Puffer verwendet.
 */
typedef struct {
    size_t len;
    char data[]; // 柔性数组，不占结构体大小 / Flexible array, does not occupy space in the struct / Flexibles Array, nimmt keinen Platz in der Struktur ein
} flex_buffer_t;

/**
 * @brief 匿名联合体与结构体 (C11)
 * @brief Anonymous Unions and Structs (C11)
 * @brief Anonyme Unions und Strukturen (C11)
 * 
 * 允许直接访问内部成员，常用于数学库（如向量表示）。
 * Allows direct access to internal members, often used in math libraries (e.g., vector representation).
 * Ermöglicht den direkten Zugriff auf interne Mitglieder, oft in Mathematikbibliotheken (z.B. Vektordarstellung) verwendet.
 */
typedef struct {
    union {
        struct { float x, y, z; };
        float v[3];
    };
} vec3_t;

/**
 * @brief 内存屏障 (Memory Barrier)
 * @brief Memory Barrier
 * @brief Speicherbarriere
 * 
 * 防止编译器对内存操作进行重排序。
 * Prevents the compiler from reordering memory operations.
 * Verhindert, dass der Compiler Speicheroperationen neu anordnet.
 */
#define COMPILER_BARRIER() __asm__ __volatile__("" ::: "memory")

/**
 * @brief 获取结构体成员偏移量 (offsetof 的底层实现原理)
 * @brief Get structure member offset (underlying principle of offsetof)
 * @brief Strukturmitglied-Offset abrufen (zugrunde liegendes Prinzip von offsetof)
 */
#define MY_OFFSETOF(type, member) ((size_t)&(((type *)0)->member))

/**
 * @brief 结构体打包 (Packed)
 * @brief Structure Packing
 * @brief Struktur-Packing
 * 
 * 告诉编译器不要在结构体成员间添加填充字节。
 * Tells the compiler not to add padding bytes between structure members.
 * Weist den Compiler an, keine Füllbytes zwischen Strukturmitgliedern hinzuzufügen.
 */
#define PACKED __attribute__((packed))

#endif // MEMORY_HACKS_H
