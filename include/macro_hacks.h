#ifndef MACRO_HACKS_H
#define MACRO_HACKS_H

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Linux 内核中最著名的宏：container_of
 * 
 * 根据结构体成员的地址，获取结构体本身的起始地址。
 * ptr: 成员指针, type: 结构体类型, member: 成员名
 */
#define container_of(ptr, type, member) ({                      \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) );})

/**
 * @brief 编译时断言 (C11 之前常用技巧)
 * 
 * 如果 condition 为假，数组大小为负，导致编译错误。
 */
#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))

/**
 * @brief 分支预测优化
 * 
 * 告诉编译器该分支极大概率(likely)或极小概率(unlikely)发生。
 */
#if defined(__GNUC__) || defined(__clang__)
#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#else
#define likely(x)   (x)
#define unlikely(x) (x)
#endif

/**
 * @brief C11 泛型选择 (伪重载)
 * 
 * 根据传入参数的类型选择不同的函数。
 */
#define print_type(x) _Generic((x), \
    _Bool: "bool",                  \
    char: "char",                   \
    int: "int",                     \
    float: "float",                 \
    double: "double",               \
    default: "unknown")

/**
 * @brief 自动资源释放 (GCC/Clang 扩展)
 * 
 * 变量离开作用域时自动调用指定的清理函数。
 */
#define __cleanup(func) __attribute__((cleanup(func)))

/**
 * @brief 静态数组大小获取 (类型安全版)
 */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/**
 * @brief 宏定义中的 do { ... } while(0)
 * 
 * 确保宏在 if/else 等语句中表现得像单条语句，且必须带分号。
 */
#define SAFE_MACRO(x) do { \
    /* 逻辑代码 */ \
} while (0)

/**
 * @brief 字符串化与连接
 */
#define STR(x) #x
#define CONCAT(a, b) a##b

#endif // MACRO_HACKS_H
