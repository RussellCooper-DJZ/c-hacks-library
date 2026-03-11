# C Hacks Library

This is a collection of various "clever tricks," advanced techniques, hacks, and performance optimization methods in C language, gathered from both domestic and international sources. It aims to provide reusable, high-performance, and inspiring code snippets.

## Directory Structure

- `include/`: Core header files, categorized by function.
  - `bit_hacks.h`: Bit manipulation hacks (fast range check, fast division, bit scanning, etc.).
  - `macro_hacks.h`: Macro definitions and preprocessor tricks (`container_of`, C11 `_Generic`, branch prediction, etc.).
  - `memory_hacks.h`: Memory and pointer techniques (pointer tagging, alignment, flexible array members, etc.).
  - `perf_hacks.h`: Performance optimization and compiler-specific features (Duff's Device, loop unrolling, prefetching, etc.).
- `examples/`: Usage examples demonstrating integration into projects.
- `docs/`: Detailed technical principle documentation.

## Key Highlights

### 1. Bit Manipulation (Bit Twiddling Hacks)
- **Fast Range Check**: `(uint32_t)(x - min) <= (uint32_t)(max - min)`. Utilizes unsigned overflow properties to combine two comparisons into one, reducing branches.
- **Fast Division by 255**: `(x + ((x + 257) >> 8)) >> 8`. Replaces expensive division operations in scenarios like image processing.
- **Next Power of 2**: Classic bit shift and fill algorithm, often used for alignment calculations in memory allocators.

### 2. Macro and Preprocessor (Macro Magic)
- **`container_of`**: The iconic macro from the Linux kernel. Infers the starting address of a structure from a member's pointer, fundamental for implementing generic linked lists, trees, and other containers.
- **C11 `_Generic`**: Achieves pseudo-overloading, automatically selecting processing logic based on parameter types, enhancing code genericity.
- **`likely/unlikely`**: Explicit branch prediction optimization, guiding the compiler to adjust instruction pipelines and reduce pipeline stalls.

### 3. Memory and Pointers
- **Pointer Tagging**: Utilizes the unused lower 3 bits of 64-bit aligned pointers to store metadata (e.g., reference counts, type tags), significantly saving space.
- **Flexible Array Member (FAM)**: A C99 standard trick for implementing variable-length buffers, reducing memory fragmentation and improving cache locality.
- **Anonymous Unions**: Allows accessing the same memory region in multiple ways (e.g., `v.x` or `v.v[0]`), highly useful in math libraries and protocol parsing.

### 4. Performance Optimization
- **Duff's Device**: A classic loop unrolling technique that uses the fall-through characteristic of `switch-case` statements to handle remaining data not divisible by 8.
- **Automatic Resource Release (`__cleanup__`)**: Mimics C++'s RAII, using GCC extensions to automatically release resources (e.g., close files, free memory) when a variable goes out of scope.
- **Memory Barriers and Prefetching**: Essential tools for low-level concurrent programming and cache optimization.

## How to Use

1. Copy the header files from `include/` into your project.
2. Include the necessary header files, e.g., `#include "macro_hacks.h"`.
3. Refer to `examples/main.c` for usage examples.
4. **Configure Compilation Environment**: Configure your compiler to correctly locate header files based on your development environment. For details, please refer to [COMPILATION_GUIDE.md](docs/COMPILATION_GUIDE.md).

## Compile Example

```bash
gcc -O3 -I./include examples/main.c -o c_hacks_demo
./c_hacks_demo
```

For more detailed compilation instructions, please refer to [COMPILATION_GUIDE.md](docs/COMPILATION_GUIDE.md).

## Notes

- Some techniques rely on specific compiler extensions (e.g., GCC/Clang's `__attribute__`). Please ensure compatibility handling with macros when using across different platforms.
- While clever tricks are powerful, always add sufficient comments to your code to avoid increasing maintenance costs.

## How to Contribute

We welcome contributions to this library! To contribute, please follow these steps:

1. **Fork** the repository.
2. Create a new **branch** for your feature or bug fix.
3. Implement your changes and **add relevant tests** and **documentation**.
4. Ensure your code adheres to the existing style.
5. Submit a **Pull Request (PR)** to the `master` branch. Your PR will be reviewed before merging.

---
*Generated and organized by Manus AI.*
