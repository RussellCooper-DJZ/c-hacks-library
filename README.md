# C Hacks Library

A collection of useful C utility functions, data structures, and low-level hacks for embedded systems and performance-critical applications.

## Features

- **Memory Management**: Custom allocators and pool allocators for deterministic allocation
- **Data Structures**: Lock-free ring buffers, intrusive linked lists, and hash maps
- **Bit Manipulation**: Fast bit-twiddling utilities (popcount, CLZ, bit reversal)
- **String Utilities**: Zero-allocation string processing for embedded targets
- **Math Utilities**: Fixed-point arithmetic, fast inverse square root, lookup tables

## Getting Started

### Prerequisites

- GCC >= 9.0 or Clang >= 10.0
- CMake >= 3.16
- Optional: Unity test framework for running tests

### Build

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

### Run Tests

```bash
cd build
ctest --output-on-failure
```

## Usage

```c
#include "hacks/ring_buffer.h"
#include "hacks/bit_utils.h"

// Lock-free ring buffer example
ring_buffer_t rb;
ring_buffer_init(&rb, buffer, sizeof(buffer));
ring_buffer_push(&rb, &data, sizeof(data));

// Fast bit counting
uint32_t val = 0xDEADBEEF;
int bits = hacks_popcount32(val);
```

## API Reference

See `docs/api.md` for full API documentation.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License

MIT License
