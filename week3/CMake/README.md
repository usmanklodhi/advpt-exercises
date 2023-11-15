# CMake Test Project

This CMake project offers multiple versions and configurations based on CMake options. Below, we break down the script version by version:

## Version 1:

- If the `USE_V1` option is enabled, it includes project headers.
- It adds an executable named "app," which consists of source files `main.cpp`, `foo.cpp`, and `bar.cpp`.

## Version 2:

- If the `USE_V2` option is enabled, it includes project headers.
- It uses the `file` command with the `GLOB` option to gather a list of all source files in the project directory and its subdirectories, storing them in the `all_SRC` variable.
- It adds an executable named "app" using the `all_SRC` variable, including all source files found.

## Version 3:

- If the `USE_V3` option is enabled, it includes project headers.
- It adds a subdirectory located at `${PROJECT_SOURCE_DIR}/src` to the project. Inside this subdirectory, it presumably contains its own CMakeLists.txt file and source code.
- It adds an executable named "app" with source file `main.cpp`.
- It links the "app" target to libraries named "foolib" and "barlib."

## Debug Configuration:

- If the `DEBUGABLE` option is enabled, it checks if either `USE_V2` or `USE_V3` is also enabled.
- If `USE_DEBUG` is enabled, it sets C++ compiler flags to enable debugging information and define the "DEBUG" preprocessor macro.
- If `USE_DEBUG` is disabled, it sets C++ compiler flags without debugging information or the "DEBUG" macro.

In summary, this CMake script allows you to build your project with different configurations based on the options you choose:

- Version 1 builds "app" with specific source files.
- Version 2 builds "app" by automatically collecting source files.
- Version 3 builds "app" with source files located in a subdirectory and links to specific libraries.

You can select the version and configuration you want to use by enabling or disabling the corresponding CMake options when configuring your project.
