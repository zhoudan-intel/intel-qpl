# ==========================================================================
# Copyright (C) 2022 Intel Corporation
#
# SPDX-License-Identifier: MIT
# ==========================================================================

# Intel® Query Processing Library (Intel® QPL)
# Build system

enable_language(CXX)

file(GLOB SOURCES *.cpp )

add_library(tool_common STATIC ${SOURCES})

target_include_directories(tool_common
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        PRIVATE $<TARGET_PROPERTY:tool_generator,INTERFACE_INCLUDE_DIRECTORIES>     #todo remove dependency
        PRIVATE $<TARGET_PROPERTY:qpl,INTERFACE_INCLUDE_DIRECTORIES>                #todo remove dependency
        PRIVATE $<TARGET_PROPERTY:qplhl,INTERFACE_INCLUDE_DIRECTORIES>              #todo remove dependency
        PRIVATE $<TARGET_PROPERTY:middle_layer_lib,INTERFACE_INCLUDE_DIRECTORIES>   #todo remove dependency
        PRIVATE $<TARGET_PROPERTY:core_iaa,INTERFACE_INCLUDE_DIRECTORIES>)           #todo remove dependency

set_target_properties(tool_common PROPERTIES CXX_STANDARD 17)

target_link_libraries(tool_common
        "$<$<PLATFORM_ID:Linux>:stdc++fs>")

target_compile_options(tool_common
        PRIVATE $<$<CONFIG:Debug>:>
        PRIVATE $<$<CONFIG:Release>:>
        PRIVATE $<$<C_COMPILER_ID:GNU>:-m64;-Werror>
        PRIVATE $<$<C_COMPILER_ID:MSVC>:/WX; /wd4244 /wd4996>)

if (WIN32)
    target_compile_definitions(tool_common PUBLIC
            QPL_LIB
            DEBUG
            _MBCS
            _LIB
            _LIB_BUILD
            _ARCH_EM64T
            _HAS_STD_BYTE=0
            _SILENCE_CXX17_STRSTREAM_DEPRECATION_WARNING=1
            _ENABLE_EXTENDED_ALIGNED_STORAGE)

    modify_standard_language_flag(LANGUAGE_NAME "CXX"
            FLAG_NAME "/EH"
            NEW_FLAG_VALUE "a")
else ()
    target_compile_definitions(tool_common PUBLIC
            QPL_LIB
            _MBCS
            _LIB
            _LIB_BUILD
            _ARCH_EM64T
            unix
            Linux
            LINUX32E
            _linux32e
            _LINUX32E)
endif ()
