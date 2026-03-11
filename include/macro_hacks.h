#ifndef MACRO_HACKS_H
#define MACRO_HACKS_H

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Linux 内核中最著名的宏：container_of
 * @brief The most famous macro in the Linux kernel: container_of
 * @brief Das bekannteste Makro im Linux-Kernel: container_of
 * 
 * 根据结构体成员的地址，获取结构体本身的起始地址。
 * ptr: 成员指针, type: 结构体类型, member: 成员名
 * Retrieves the base address of a structure given a pointer to one of its members.
 * ptr: pointer to the member, type: type of the structure, member: name of the member
 * Ruft die Basisadresse einer Struktur ab, gegeben einen Zeiger auf eines ihrer Mitglieder.
 * ptr: Zeiger auf das Mitglied, type: Typ der Struktur, member: Name des Mitglieds
 */
#define container_of(ptr, type, member) ({                      \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) );})

/**
 * @brief 编译时断言 (C11 之前常用技巧)
 * @brief Compile-time assertion (common trick before C11)
 * @brief Kompilierzeit-Assertion (häufiger Trick vor C11)
 * 
 * 如果 condition 为假，数组大小为负，导致编译错误。
 * If condition is false, array size becomes negative, leading to a compile error.
 * Wenn die Bedingung falsch ist, wird die Array-Größe negativ, was zu einem Kompilierungsfehler führt.
 */
#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))

/**
 * @brief 分支预测优化
 * @brief Branch prediction optimization
 * @brief Branch-Prediction-Optimierung
 * 
 * 告诉编译器该分支极大概率(likely)或极小概率(unlikely)发生。
 * Informs the compiler that a branch is highly likely or unlikely to be taken.
 * Informiert den Compiler, dass ein Branch sehr wahrscheinlich oder unwahrscheinlich genommen wird.
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
 * @brief C11 Generic selection (pseudo-overloading)
 * @brief C11 Generische Auswahl (Pseudo-Überladung)
 * 
 * 根据传入参数的类型选择不同的函数。
 * Selects different functions based on the type of the passed argument.
 * Wählt verschiedene Funktionen basierend auf dem Typ des übergebenen Arguments aus.
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
 * @brief Automatic resource release (GCC/Clang extension)
 * @brief Automatische Ressourcenfreigabe (GCC/Clang-Erweiterung)
 * 
 * 变量离开作用域时自动调用指定的清理函数。
 * Automatically calls a specified cleanup function when a variable goes out of scope.
 * Ruft automatisch eine angegebene Bereinigungsfunktion auf, wenn eine Variable den Gültigkeitsbereich verlässt.
 */
#define __cleanup(func) __attribute__((cleanup(func)))

/**
 * @brief 静态数组大小获取 (类型安全版)
 * @brief Get static array size (type-safe version)
 * @brief Statische Array-Größe abrufen (typensichere Version)
 */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/**
 * @brief 宏定义中的 do { ... } while(0)
 * @brief do { ... } while(0) in macro definitions
 * @brief do { ... } while(0) in Makrodefinitionen
 * 
 * 确保宏在 if/else 等语句中表现得像单条语句，且必须带分号。
 * Ensures the macro behaves like a single statement in if/else constructs and requires a semicolon.
 * Stellt sicher, dass sich das Makro in if/else-Konstrukten wie eine einzelne Anweisung verhält und ein Semikolon erfordert.
 */
#define SAFE_MACRO(x) do { \
    /* 逻辑代码 */ \
} while (0)

/**
 * @brief 字符串化与连接
 * @brief Stringification and concatenation
 * @brief Stringifizierung und Verkettung
 */
#define STR(x) #x
#define CONCAT(a, b) a##b

#endif // MACRO_HACKS_H
