![GitHub](https://img.shields.io/github/license/proxict/digital)
[![Tests](https://github.com/proxict/digital/actions/workflows/posix.yml/badge.svg)](https://github.com/proxict/digital/actions/workflows/posix.yml)
[![Tests](https://github.com/proxict/digital/actions/workflows/windows.yml/badge.svg)](https://github.com/proxict/digital/actions/workflows/windows.yml)

# `prox::digital::unit`

The `prox::digital::unit` class represents a quantity of digital size (e.g., bytes, kilobytes, gigabytes).
It offers type-safe operations for working with sizes of digital information.

```c++
#include <prox/digital.hpp>

namespace digital = prox::digital;
using namespace digital::unit_literals;

static constexpr auto MAX_UPLOAD_FILE_SIZE = 5_GiB;
if (digital::bytes(uploadFileSize) > MAX_UPLOAD_FILE_SIZE) {
    throw std::runtime_error("exceeded maximum file size");
}
```

---

## Features
- Represents digital sizes using a type-safe mechanism.
- Supports arithmetic operations like addition, subtraction, multiplication, and division.
- Allows for precise conversions between different units of digital size.
- Provides pre-defined units for common digital sizes (e.g., bytes, kilobytes, gibibytes).
- Includes user-defined literals for concise and readable initialization of unit types.

---

## Requirements
- **C++ Standard**: C++17 or later.
- **Header**: `#include <prox/digital.hpp>`

---

### Integration
The library can be used as a standalone header-only library.
However, integration with CMake build systems is easier using CMake's FetchContent mechanism:

```cmake
include(FetchContent)
FetchContent_Declare(digital
    GIT_REPOSITORY https://github.com/proxict/digital.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(digital)
target_link_libraries(your_target PRIVATE prox::digital)
```

Additionally, the CMake configuration allows changing the default namespace (`prox::digital`) to a user-defined namespace using the `PROJECT_NAMESPACE` CMake option:

```cmake
-DPROJECT_NAMESPACE=your_namespace
```

---

## Template Parameters

```cpp
template <typename TRep, typename TRatio = std::ratio<1>>
prox::digital::unit<TRep, TRatio>
```
- **`TRep`**: The underlying type used to represent the value (e.g., `int64_t`, `double`).
- **`TRatio`**: The ratio of the unit relative to a byte, represented as a `std::ratio` (e.g., `prox::digital::kilo` for kilobytes).

---

## Common Type Aliases

### Decimal Units
- `prox::digital::bytes`: Base unit (1 byte).
- `prox::digital::kilobytes`: Decimal kilobytes (1,000 bytes).
- `prox::digital::megabytes`: Decimal megabytes (1,000,000 bytes).
- `prox::digital::gigabytes`: Decimal gigabytes (1,000,000,000 bytes).
- `prox::digital::terabytes`: Decimal terabytes (1,000,000,000,000 bytes).
- `prox::digital::petabytes`: Decimal petabytes (1,000,000,000,000,000 bytes).
- `prox::digital::exabytes`: Decimal exabytes (1,000,000,000,000,000,000 bytes).

### Binary Units
- `prox::digital::kibibytes`: Binary kilobytes (1,024 bytes).
- `prox::digital::mebibytes`: Binary megabytes (1,048,576 bytes).
- `prox::digital::gibibytes`: Binary gigabytes (1,073,741,824 bytes).
- `prox::digital::tebibytes`: Binary terabytes (1,099,511,627,776 bytes).
- `prox::digital::pebibytes`: Binary petabytes (1,125,899,906,842,624 bytes).
- `prox::digital::exbibytes`: Binary exabytes (1,152,921,504,606,846,976 bytes).

---

## User-Defined Literals
The `prox::digital::unit_literals` namespace provides user-defined literals for concise initialization of digital units:

```cpp
using namespace prox::digital::unit_literals;

static constexpr auto size = 1_KiB + 500_B; // 1 KiB (1024 bytes) + 500 bytes
```

### Available Literals
- `_B` for `bytes`
- `_KB` for `kilobytes`
- `_MB` for `megabytes`
- `_GB` for `gigabytes`
- `_TB` for `terabytes`
- `_PB` for `petabytes`
- `_EB` for `exabytes`
- `_KiB` for `kibibytes`
- `_MiB` for `mebibytes`
- `_GiB` for `gibibytes`
- `_TiB` for `tebibytes`
- `_PiB` for `pebibytes`
- `_EiB` for `exbibytes`

---

## Examples

### Basic Usage
```cpp
#include <iostream>
#include <prox/digital.hpp>

int main() {
    namespace digital = prox::digital;

    // Creating units
    digital::bytes b(1024);       // 1024 bytes
    digital::kilobytes kb(1);     // 1 kilobyte (1000 bytes)

    // Arithmetic operations
    auto total = b + kb; // 2024 bytes

    std::cout << "Total size in bytes: " << total.value() << " bytes\n";

    // Explicit conversion
    auto total_in_kilobytes = digital::unit_cast<digital::kilobytes>(total);
    std::cout << "Total size in kilobytes: " << total_in_kilobytes.value() << " KB\n";
    // Output:
    // Total size in bytes: 2024 bytes
    // Total size in kilobytes: 2 KB

    return 0;
}
```

### Using Literals
```cpp
#include <iostream>
#include <prox/digital.hpp>

int main() {
    namespace digital = prox::digital;
    using namespace digital::unit_literals;

    static constexpr auto size = 2_GiB + 512_MiB; // 2 GiB + 512 MiB
    std::cout << "Total size in GiB: " << digital::unit_cast<digital::gibibytes>(size).value() << " GiB\n";
    // Output:
    // Total size in GiB: 2 GiB

    return 0;
}
```

### Best-fitting Common Type Deduction
```cpp
#include <iostream>
#include <prox/digital.hpp>

int main() {
    namespace digital = prox::digital;
    using namespace digital::unit_literals;

    std::cout << "Total size in MB: " << (1_GB + 500_MB).value() << " MB\n";
    // Output:
    // Total size in MB: 1500 MB

    return 0;
}
```

### Fractional Units
```cpp
#include <iostream>
#include <prox/digital.hpp>

int main() {
    namespace digital = prox::digital;
    using namespace digital::unit_literals;

    static constexpr auto size = 1_GiB + 512_MiB; // 1 GiB + 512 MiB
    using gibibytes_f = digital::unit<float, digital::gibi>;
    std::cout << "Total size in GiB: " << digital::unit_cast<gibibytes_f>(size).value() << " GiB\n"; 
    // Output:
    // Total size in GiB: 1.5 GiB

    return 0;
}
```

### Converting Between Units
```cpp
#include <iostream>
#include <prox/digital.hpp>

int main() {
    namespace digital = prox::digital;

    static constexpr auto gi = 1_GiB;
    static constexpr auto b = digital::unit_cast<digital::bytes>(gi); // Convert GiB to bytes

    std::cout << gi.value() << " GiB = " << b.value() << " bytes\n";
    // Output:
    // 1 GiB = 1073741824 bytes

    return 0;
}
```

### Working with Mixed Units
```cpp
#include <iostream>
#include <prox/digital.hpp>

int main() {
    namespace digital = prox::digital;

    static constexpr digital::bytes b(512);
    static constexpr digital::kibibytes ki(1); // 1 KiB = 1024 bytes

    auto total_bytes = b + digital::unit_cast<digital::bytes>(ki);
    std::cout << "Total size: " << total_bytes.value() << " bytes\n";
    // Output:
    // Total size: 1536 bytes

    return 0;
}
```

### More examples
For more examples, consult the [unit tests](./tests/unittests.cpp).

---

## Key Functions

### `prox::digital::unit::value()`
Returns the numeric value (in the underlying `TRep` type) of the unit.

### Conversion Function
- **`prox::digital::unit_cast`**: Converts a unit to a different unit.

### Utility Functions
- **`prox::digital::unit::zero()`**: Returns a unit with a value of 0.
- **`prox::digital::unit::min()`**: Returns a unit with the smallest possible value for the unit.
- **`prox::digital::unit::max()`**: Returns a unit with the largest possible value for the unit.

---
