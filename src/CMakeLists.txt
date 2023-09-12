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

add_library(Pulsar STATIC Pulsar.cpp)

target_include_directories(Pulsar PUBLIC ../include)

set_target_properties(Pulsar PROPERTIES
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)

target_link_libraries(Pulsar PUBLIC Equinox stb_image glfw glad glm freetype)

target_compile_features(Pulsar PUBLIC cxx_std_20)

if (MSVC)
    target_compile_options(Pulsar PRIVATE /W4 /GR- /O2)
else ()
    target_compile_options(Pulsar PRIVATE -O3 -Wall -Wextra -Wpedantic
        -Wconversion -fno-rtti -fno-exceptions)
endif()
