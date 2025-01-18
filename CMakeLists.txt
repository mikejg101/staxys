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

cmake_minimum_required(VERSION 3.5)
project(staxys)

set(CMAKE_CXX_STANDARD 20)
set(CLANG_TIDY_PATH "${CMAKE_SOURCE_DIR}/.clang-tidy")
set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-config-file=${CLANG_TIDY_PATH}")

cmake_policy(SET CMP0148 OLD)

set(BUILD_GTEST OFF CACHE BOOL "Disable GoogleTest installation")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG) 
endif()


find_package(Boost REQUIRED COMPONENTS program_options)

include_directories(${Boost_INCLUDE_DIRS})

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

# Link Boost libraries
target_link_libraries(staxys PRIVATE ${Boost_LIBRARIES})

# Conditionally add tests
if (BUILD_GTEST)
        # Fetch GoogleTest
        include(FetchContent)
        FetchContent_Declare(
                googletest
                GIT_REPOSITORY https://github.com/google/googletest.git
                GIT_TAG release-1.12.1
        )
        FetchContent_MakeAvailable(googletest)

        # Link GoogleTest to your executable
        target_link_libraries(staxys PRIVATE gtest gtest_main)

        # Add tests
        enable_testing()

        # Add the tests directory (make sure CMake knows about it)
        add_subdirectory(tests)
endif ()

install(TARGETS staxys DESTINATION bin) 

install(FILES ${CMAKE_SOURCE_DIR}/config/staxys.cfg DESTINATION /etc/staxys/)

install(CODE "execute_process(COMMAND ${CMAKE_SOURCE_DIR}/post_install)")