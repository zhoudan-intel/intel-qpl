# ==========================================================================
# Copyright (C) 2022 Intel Corporation
#
# SPDX-License-Identifier: MIT
# ==========================================================================

# Intel® Query Processing Library (Intel® QPL)
# Build system

enable_language(CXX)

file(GLOB SOURCES algorithmic/*.cpp
                  bad_argument/*.cpp)

add_library(unit_tests OBJECT ${SOURCES} )

get_target_property(QPL_SOURCE_DIR qpl SOURCE_DIR)
get_target_property(QPL_HL_SOURCE_DIR qplhl SOURCE_DIR)
set_target_properties(unit_tests PROPERTIES CXX_STANDARD 17)

target_include_directories(unit_tests
        PRIVATE ${QPL_PROJECT_DIR}/sources/c_api
        PRIVATE ${QPL_PROJECT_DIR}/high-level-api/util
        PRIVATE $<TARGET_PROPERTY:tests_common,INTERFACE_INCLUDE_DIRECTORIES>
        PRIVATE $<TARGET_PROPERTY:tool_generator,INTERFACE_INCLUDE_DIRECTORIES>
        PRIVATE $<TARGET_PROPERTY:qplhl,INTERFACE_INCLUDE_DIRECTORIES>   #todo remove dependency
        PRIVATE $<TARGET_PROPERTY:core_iaa,INTERFACE_INCLUDE_DIRECTORIES> #todo remove dependency
        PRIVATE $<TARGET_PROPERTY:middle_layer_lib,INTERFACE_INCLUDE_DIRECTORIES>)

target_compile_definitions(unit_tests
        PRIVATE $<TARGET_PROPERTY:tests_common,COMPILE_DEFINITIONS>)

target_compile_options(unit_tests
        PRIVATE $<TARGET_PROPERTY:tests_common,COMPILE_OPTIONS>)
