# ==========================================================================
# Copyright (C) 2022 Intel Corporation
#
# SPDX-License-Identifier: MIT
# ==========================================================================

project(hl_fuzzing VERSION 1.0 LANGUAGES CXX)

file(GLOB CPP_FILES "*.cpp")
add_custom_target(hl_fuzzy_tests)
foreach (FILE ${CPP_FILES})
	file(RELATIVE_PATH FILE_REL_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${FILE})
	string(REPLACE ".cpp" "" TARGET_NAME "${FILE_REL_PATH}")
	add_executable(${TARGET_NAME} ${FILE_REL_PATH})
	target_link_libraries(${TARGET_NAME} PRIVATE qplhl)
	add_dependencies(hl_fuzzy_tests ${TARGET_NAME})
endforeach()
