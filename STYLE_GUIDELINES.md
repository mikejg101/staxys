## Naming Conventions

Naming is a critical aspect of writing clean, readable, and maintainable code. In C++, we follow CamelCase for methods
and classes and snake_case for variables and constants, with some exceptions and rules.

### Classes and Class Attributes

#### Class Names

Class names should be nouns and follow PascalCase (first letter of each word capitalized, no underscores).

Examples:

- `PerimeterRectangle`
- `FingerprintScanner`

#### Private Member Variables

Private member variables should be prepended with `m_` (for "member") to indicate they are class attributes. The naming
follows CamelCase after the `m_`.

Example:

```cpp
class PerimeterRectangle {
public:
    int perimeter;
private:
    int m_length;
    int m_width;
};
```

#### Pointer Variables

Pointer variables should be prepended with `p`, and the asterisk (`*`) should be placed next to the variable name, not
the type.

Example:

```cpp
int *pAge;
```

#### Reference Variables

Reference variables should be prepended with `r` to differentiate them from normal variables.

Example:

```cpp
int &rCount;
```

#### Static Variables

Static variables should be prepended with `s`.

Example:

```cpp
static int sCount;
```

### Functions and Method Names

#### Function Names

Method and function names should start with a verb to clearly convey the action being performed. Use camelCase for
function names.

Examples:

- `getValue()`
- `solveEquation()`

#### Function Arguments

Function arguments should start with a lowercase letter, and subsequent words should follow CamelCase.

Example:

```cpp
int calculateArea(int lengthRectangle, int widthRectangle);
```

#### Suffixes and Prefixes

Sometimes, it’s useful to add suffixes or prefixes to clarify the meaning of a variable.

- Suffixes: `Count` (for counters), `Key` (for key values).
- Prefixes: `get` (for getters), `set` (for setters).

Example:

```cpp
int getCount();
void setValue(int newValue);
```

### Variables

#### General Variable Names

Variable names should begin with a letter and may contain digits, but digits should only appear after the first letter.
Use snake_case (lowercase with underscores) for variable names.

Example:

```cpp
int total_cost;
int length_of_rectangle;
```

#### Special Variables

- Pointer Variables: Prepend with `p`.
- Reference Variables: Prepend with `r`.
- Static Variables: Prepend with `s`.

Examples:

```cpp
int *pAge;
int &rCount;
static int sMaxCount;
```

### Constants

Global constants should be written in all uppercase letters with words separated by underscores (`_`).

Example:

```cpp
const double TWO_PI = 6.28318531;
const int MAX_RETRIES = 5;
```

### File Naming Conventions

The naming of files should also adhere to specific guidelines for clarity and consistency.

#### File Extensions

Source files should have the `.cpp` or `.cc` extension, and header files should have the `.h` extension.

Examples:

- `hello_world.cpp`
- `calculator.h`

#### File Names

Use snake_case for file names. File names should be descriptive and indicate the content of the file. Avoid special
characters other than underscores (`_`) and hyphens (`-`). Do not use reserved or existing system header names (e.g.,
`iostream`, `stdio.h`).

Examples:

- `my_class.cpp`
- `utils_functions.cpp`
- `network_manager.h`

## Formatting

Consistent formatting is essential for readability and maintainability. The following guidelines should be followed when
formatting C++ code.

### Indentation

Use 4 spaces for indentation. Do not use tabs.

Example:

```cpp
void printMessage() {
    std::cout << "Hello, World!" << std::endl;
}
```

### Braces

Braces should be on the same line as the statement they belong to.

Example:

```cpp
if (condition) {
    // code block
} else {
    // code block
}
```

### Line Length

Limit lines to a maximum of 100 characters.

### Comments

Use comments to explain the purpose of the code, not what the code is doing. Comments should be concise and to the
point.

Example:

```cpp
// Calculate the area of a rectangle
int calculateArea(int length, int width) {
    return length * width;
}
```

### Spacing

Use spaces around operators and after commas.

Example:

```cpp
int sum = 1 + 2;
int product = 3 * 4;
int max = std::max(5, 6);
```

## Code Structure and Best Practices

### Const Correctness

Use `const` whenever possible to indicate that a variable or function parameter should not be modified.

Example:

```cpp
int calculateArea(const int length, const int width) {
    return length * width;
}
```

### Avoid Magic Numbers

Avoid using magic numbers in your code. Instead, use named constants or enums to make the code more readable and
maintainable.

Example:

```cpp
const int MAX_RETRIES = 5;
for (int i = 0; i < MAX_RETRIES; ++i) {
    // code block
}
```

### Avoid Global Variables

Avoid using global variables whenever possible. Instead, use local variables or pass variables as function parameters.

### Error Handling

Always check for errors and handle them appropriately. Use exceptions or return error codes to indicate errors.

### Memory Management

Use smart pointers (e.g., `std::unique_ptr`, `std::shared_ptr`) to manage memory and avoid memory leaks.

### Avoid Using Macros

Avoid using macros in your code. Instead, use `const` variables or inline functions for constants and small functions.

### Use Standard Library

Use the C++ Standard Library whenever possible to avoid reinventing the wheel and to take advantage of the built-in
features and optimizations.

### Avoid Unnecessary Optimizations

Avoid premature optimization. Write clear, readable code first, and optimize only when necessary.

### Unit Testing

Write unit tests for your code to ensure correctness and maintainability. This project uses Google Test.

### Documentation

Document your code using comments to explain the purpose of functions, classes, and variables. Use Doxygen-style
comments for generating documentation. Comments should explain the "why" behind your code, not the "what". The code
itself should be self-explanatory as much as possible. Do not write comments that simply restate what the code does.
If the code is clear, there is no need for redundant comments.

### Pass by Reference or Pointer

Use pass by reference or pointer for large objects to avoid unnecessary copying. Use pass by value for small objects.

### Avoid Using `using namespace`

Avoid using the `using namespace` directive to prevent naming conflicts and improve code readability.

### Avoid C-Style Casts

Avoid using C-style casts (e.g., `(int)x`) in favor of C++-style casts (e.g., `static_cast<int>(x)`) for type
conversions.

### Avoid Raw Loops

Avoid using raw loops (e.g., `for`, `while`) when possible. Instead, use range-based for loops or algorithms from the
Standard Library.

## Error Handling and Exceptions

### Error Handling

Always check for errors and handle them appropriately. Use exceptions or return error codes to indicate errors.

Example:

```cpp
int divide(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("Division by zero");
    }
    return a / b;
}
```

### Exceptions

Use exceptions to handle exceptional conditions, not for normal control flow. Use the appropriate exception type for
different error conditions.

Example:

```cpp
try {
    int result = divide(10, 0);
    std::cout << "Result: " << result << std::endl;
} catch (const std::runtime_error &e) {
    std::cerr << "Error: " << e.what() << std::endl;
}
```

### Avoid Catching General Exceptions

Avoid catching general exceptions (e.g., `catch (...) {}`) as it can hide errors and make debugging more difficult.

## Memory Management and Ownership

### Prefer Smart Pointers Over Raw Pointers

Prefer using smart pointers (e.g., `std::unique_ptr`, `std::shared_ptr`) over raw pointers to manage memory and avoid
memory leaks.

Example:

```cpp
std::unique_ptr<int> p(new int(42));
```

### Avoid Manual `new`/`delete`

Avoid using manual `new`/`delete` for memory management. Use smart pointers or containers from the Standard Library
instead.

Example:

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
```