## Rule of Three and Rule of Five in C++

### Rule of Three:

The "Rule of Three" states that if a class needs to provide a custom implementation for any one of the following three functions, it should provide custom implementations for all three:

- **Destructor (`~ClassName()`):** Responsible for releasing resources held by an object.
- **Copy Constructor (`ClassName(const ClassName&)`):** Creates a new object as a copy of an existing object.
- **Copy Assignment Operator (`ClassName& operator=(const ClassName&)`):** Assigns the contents of an existing object to another object.

The rationale is to prevent issues related to resource management, particularly when dealing with dynamically allocated memory. If a class manages resources in a custom way, it needs to provide proper copying and destruction behavior.

### Rule of Five:

With the introduction of move semantics in C++11, the "Rule of Five" expands the "Rule of Three" to include two additional functions:

- **Move Constructor (`ClassName(ClassName&&)`):** Efficiently transfers ownership of resources from one object to another.
- **Move Assignment Operator (`ClassName& operator=(ClassName&&)`):** Efficiently transfers ownership of resources during assignment.

These additional functions take advantage of move semantics to optimize resource management, especially when dealing with temporary objects or in situations where ownership transfer is more efficient than copying.

In object-oriented programming, these rules are relevant when designing classes that manage resources, such as memory, file handles, or other external entities. Adhering to these rules helps ensure proper behavior and avoids common pitfalls related to resource leaks and inefficient copying.
