#
# Copyright 2025 Michael Goodwin
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

enable_testing()

file(GLOB_RECURSE SOURCES
        ${PROJECT_SOURCE_DIR}/src/staxys/core/*.cpp
        ${PROJECT_SOURCE_DIR}/src/staxys/network/*.cpp
        ${PROJECT_SOURCE_DIR}/src/staxys/error/*.cpp
        ${PROJECT_SOURCE_DIR}/src/staxys/config/*.cpp
        ${PROJECT_SOURCE_DIR}/src/staxys/security/*.cpp
        ${PROJECT_SOURCE_DIR}/src/staxys/logging/*.cpp
        ${PROJECT_SOURCE_DIR}/src/staxys/static_content/*.cpp
        ${PROJECT_SOURCE_DIR}/src/staxys/utils/*.cpp
        ${PROJECT_SOURCE_DIR}/tests/test_utils_string_utils.cpp
)

# Define the test executable
add_executable(test_staxys ${SOURCES})

# Link the GoogleTest library to your test executable
target_link_libraries(test_staxys PRIVATE gtest gtest_main)

# Include the project's main headers directory
target_include_directories(test_staxys PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Run the tests
include(GoogleTest)
gtest_discover_tests(test_staxys)
