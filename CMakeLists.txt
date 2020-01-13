# MIT License

# Copyright (c) 2020 Sathyanesh Krishnan

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.


cmake_minimum_required(VERSION 3.10)

# set the project name and version
project( ElasticCircularQ VERSION 1.0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Let us print the DIRs
message("PROJECT_NAME              ${PROJECT_NAME}")
message("PROJECT_SOURCE_DIR        ${PROJECT_SOURCE_DIR}")
message("CMAKE_SOURCE_DIR          ${CMAKE_SOURCE_DIR}")
message("CMAKE_CURRENT_SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}")
message("PROJECT_BINARY_DIR        ${PROJECT_BINARY_DIR}")
message("CMAKE_BINARY_DIR          ${CMAKE_BINARY_DIR}")
message("CMAKE_CURRENT_BINARY_DIR  ${CMAKE_CURRENT_BINARY_DIR}")
message("CMAKE_INSTALL_PREFIX      ${CMAKE_INSTALL_PREFIX}")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

set(MY_SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(MY_INCL_DIR "${PROJECT_SOURCE_DIR}/include")

file(GLOB SOURCE_FILES
    "${MY_INCL_DIR}/ElasticCircularQ.h"
    "${MY_SRC_DIR}/ElasticCircularQ.cpp"
    "${MY_SRC_DIR}/testq.cpp"
)


# add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} )

# add the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME}
PUBLIC
    "${MY_INCL_DIR}"
)

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS=1)

