#
# Copyright (C) 2023 Anthony H. Grasso
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_EXTENSIONS Off)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

add_executable(ProvingGrounds Main.cpp)

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/ProvingGrounds/Resources
    ${PROJECT_BINARY_DIR}/ProvingGrounds/Resources
    COMMENT "Copying Resources!")

add_dependencies(ProvingGrounds copy_resources)

target_include_directories(ProvingGrounds PRIVATE ../include)

target_link_libraries(ProvingGrounds PRIVATE Pulsar)

target_compile_features(ProvingGrounds PRIVATE cxx_std_20)
if (MSVC)
    target_compile_options(ProvingGrounds PRIVATE /W4 /GR- /Zc:preprocessor)
else ()
    target_compile_options(ProvingGrounds PRIVATE -Wall -Wextra -Wpedantic
        -Wconversion -fno-rtti -fno-exceptions)
endif()
