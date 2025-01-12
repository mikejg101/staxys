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

# Set the policy early to suppress the warning
cmake_policy(SET CMP0148 OLD)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)  # Default to Release build type

project(staxys)

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.10.0  # Specify the version/tag you need
)
FetchContent_MakeAvailable(googletest)

# Automatically collect all .cpp files in the src/staxys subdirectories
file(GLOB_RECURSE SOURCES
        src/staxys/core/*.cpp
        src/staxys/network/*.cpp
        src/staxys/error/*.cpp
        src/staxys/config/*.cpp
        src/staxys/security/*.cpp
        src/staxys/logging/*.cpp
        src/staxys/static_content/*.cpp
        src/staxys/utils/*.cpp
        src/main.cpp
)

# Create the executable target first
add_executable(staxys ${SOURCES})

# Define the path to the include directory
target_include_directories(staxys PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Link GoogleTest to your executable
target_link_libraries(staxys PRIVATE gtest gtest_main)

# Add tests
enable_testing()

# Add the tests directory (make sure CMake knows about it)
add_subdirectory(tests)
