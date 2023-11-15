# Resolving Compilation Directives Error in C++ Program

If you encounter an error message indicating that you need to define exactly one of the following preprocessor directives: `WARMUP`, `EXACTMATCH`, `ARGNUMBERS`, `DEFAULTARGS`, `STATICMEMBER`, `CONSTMEMBER`, `VIRTUALMEMBER`, `TEMPLATEFUNCS`, `TEMPLATEMEMBER`, you can use the following instructions to resolve it.

## How to Define Compilation Directives

You can define these directives at compile time using the `-D` option with the `g++` compiler. Here's an example using the `WARMUP` directive:

```bash
g++ -DWARMUP overloading.cpp -o overloading
