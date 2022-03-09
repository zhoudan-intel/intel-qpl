<!--
Copyright (C) 2022 Intel Corporation 
SPDX-License-Identifier: MIT
-->

Software Implementation of the Intel® Query Processing Library (Intel® QPL) Beta
================================================================================

The Intel® Query Processing Library (Intel® QPL) provides a common interface for 
a number of commonly used algorithms. Using this library enables you to
automatically tune your application to many generations of processors without
changes in your application. The Intel® QPL provides high performance
implementations of data processing functions for existing hardware accelerator,
and/or software path in case if hardware accelerator is not available. Code written
within the library automatically takes advantage of available modern CPU
capabilities. This behavior can provide tremendous development and maintenance savings.
Use the Intel® QPL to improve performance of database, enterprise data, 
communications, and scientific/technical applications.

Documentation
--------------

General information about the library can be found here:

 - [Reference manual](doc/QPL_REFERENCE_MANUAL.md)
 - [C API (Job API)](doc/QPL_C_API_MANUAL.md)
 - [C++ API (High-Level API) manual](doc/QPL_HIGH_LEVEL_API_MANUAL.md)

>**Note:** The library is in beta state and its APIs may change as the library is actively developed.

To report a security issue, refer to the [security documentation](SECURITY.md).

To work with HW-path, read the [Reference manual](doc/QPL_REFERENCE_MANUAL.md). 

To generate full HTML Reference documentation from sources with Doxygen:

1. Download and install the Doxygen processor at the [Doxygen official site](http://www.doxygen.nl/).
2. Build the documentation:

```
    cmd> cd <qpl_library catalog path>
    cmd> doxygen ./Doxyfile
```

3. View the HTML Reference generated by opening the `<qpl_library>/doc/html/index.html` file.

Prerequisites
--------------

* Assembler: `nasm 2.15.0` or higher (can be installed from https://www.nasm.us/, for example build 2.15.05: https://www.nasm.us/pub/nasm/releasebuilds/2.15.05/,
win64/nasm-2.15.05-installer-x64.exe for use on 64-bit Windows*, or nasm-2.15.05.tar.gz for Linux*)
* Compiler: GCC 8.2 or higher (Linux* OS); VC 14.1 or higher (Windows*)
* Compiler for building fuzzy tests: Clang 12.0.1 or higher (Linux* OS)
* Cross-platform build tool: CMake* version 3.15.0 or higher
* Make: GNU `make` (Linux* OS) or `nmake` (Windows*)
* Universally Unique ID library: `uuid-dev` version 2.35.2 or higher.
* Accelerator configuration library: `[accel-config](https://github.com/intel/idxd-config)` version 3.2 or higher.

Build
--------------
To build the library, complete the following steps:
1. Make sure that all prerequisites are available from your environment
2. Extract git sources using the following command: 
```shell
# Using HTTPS
git clone --recursive <qpl_git_repository> <qpl_library>
```
3. Build the library and tests executing the following list of commands from `<qpl_library>`:

### Windows*
   
```shell
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=<install_dir> -G "NMake Makefiles" ..
cmake --build . --target install
```
		
### Linux* OS
   
```shell
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=<install_dir> ..
cmake --build . --target install
```

***Build type:*** CMake generates the script for release build as default. 
If you want to build a particular type of the library and tests (`DEBUG`|`RELEASE`), use the flag `CMAKE_BUILD_TYPE` like:

```shell
# Debug
cmake -DCMAKE_BUILD_TYPE=Debug <path_to_cmake_folder>

# Release
cmake -DCMAKE_BUILD_TYPE=Release <path_to_cmake_folder>

# Release with debug information
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo <path_to_cmake_folder>
```

***Install rules:*** 
- The resulting library will be available in the folder `<install_dir>/lib`
- In Linux* OS default `<install_dir>` is `/usr/local/`

***Extra Note:*** 
More information about specific build options can be found in the [Reference manual](doc/QPL_REFERENCE_MANUAL.md):
`Specific build options` section.

Testing
-------------
See [Testing document](doc/QPL_TESTING.md) for details about testing process.

## How to Contribute

See [Contributing document](CONTRIBUTING.md) for details about contribution process.

## How to Report Issues

See [Issue Reporting](doc/QPL_ISSUE_REPORTING.md) for details about issue reporting process.

## License

The library is licensed under the EULA license. Refer to the
"[LICENSE](LICENSE)" file for the full license text.

This distribution includes third party software governed by separate license
terms (see "[THIRD-PARTY-PROGRAMS](third-party-programs.txt)").