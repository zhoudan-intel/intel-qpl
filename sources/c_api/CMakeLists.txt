# ==========================================================================
# Copyright (C) 2022 Intel Corporation
#
# SPDX-License-Identifier: MIT
# ==========================================================================

# Intel® Query Processing Library (Intel® QPL)
# Build system

enable_language(C CXX)

file(GLOB_RECURSE QPL_C_API_SRC *.c *.cpp)

add_library(qpl STATIC ${QPL_C_API_SRC}
        $<TARGET_OBJECTS:isal>
        $<TARGET_OBJECTS:isal_asm>
        $<TARGET_OBJECTS:qplcore_px>
        $<TARGET_OBJECTS:qplcore_avx512>
        $<TARGET_OBJECTS:core_iaa>
        $<TARGET_OBJECTS:middle_layer_lib>)

target_include_directories(qpl
        PUBLIC $<BUILD_INTERFACE:${QPL_PROJECT_DIR}/include/>
        PRIVATE $<TARGET_PROPERTY:middle_layer_lib,INTERFACE_INCLUDE_DIRECTORIES>
        PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

set_target_properties(qpl PROPERTIES
        $<$<C_COMPILER_ID:MSVC>:C_STANDARD 18>
        $<$<C_COMPILER_ID:GNU>:C_STANDARD 17>
        CXX_STANDARD 17)

target_compile_options(qpl
        PRIVATE $<$<C_COMPILER_ID:GNU>:${QPL_LINUX_TOOLCHAIN_REQUIRED_FLAGS};
                                       ${QPL_LINUX_TOOLCHAIN_DYNAMIC_LIBRARY_FLAGS};
                                       $<$<CONFIG:Release>:-O3;-D_FORTIFY_SOURCE=2>>
        PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,GNU>:${QPL_LINUX_TOOLCHAIN_CPP_EMBEDDED_FLAGS}>
        PRIVATE $<$<C_COMPILER_ID:MSVC>:${QPL_WINDOWS_TOOLCHAIN_REQUIRED_FLAGS};
                                        ${QPL_WINDOWS_TOOLCHAIN_DYNAMIC_LIBRARY_FLAGS}
                                        $<$<CONFIG:Release>:-O2>>
        PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:${QPL_WINDOWS_TOOLCHAIN_CPP_EMBEDDED_FLAGS}>)

target_compile_definitions(qpl
        PUBLIC -DQPL_LIB
        PUBLIC -DQPL_BADARG_CHECK
        PUBLIC $<$<C_COMPILER_ID:MSVC>:_ENABLE_EXTENDED_ALIGNED_STORAGE>
        PUBLIC $<$<BOOL:${DWQ_SUPPORT}>:DWQ_SUPPORT>)

target_link_libraries(qpl
        PRIVATE ${CMAKE_DL_LIBS})

install(TARGETS qpl
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY ${QPL_PROJECT_DIR}/include/qpl/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qpl
        FILES_MATCHING PATTERN "*.h")
