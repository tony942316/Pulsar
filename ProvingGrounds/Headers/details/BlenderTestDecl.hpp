/*
 * Copyright (C) 2023 Anthony H. Grasso
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef PROVINGGROUNDS_DETAILS_BLENDERTESTDECL_HPP
#define PROVINGGROUNDS_DETAILS_BLENDERTESTDECL_HPP

#include "Dependencies.hpp"

class BlenderTest
{
public:
    BlenderTest() = delete;
    BlenderTest(const BlenderTest&) = delete;
    BlenderTest(BlenderTest&&) = delete;
    BlenderTest& operator= (const BlenderTest&) = delete;
    BlenderTest& operator= (BlenderTest&&) = delete;
    ~BlenderTest() = delete;

    static inline void update(float dt) noexcept;
    static inline void render() noexcept;

private:
    static inline bool loadFile() noexcept;

    constinit static inline auto s_Model = glm::mat4(1.0f);

    constinit static inline auto s_Shader = pul::Shader();
    constinit static inline auto s_VA = pul::VertexArray();
};

#endif // PROVINGGROUNDS_DETAILS_BLENDERTESTDECL_HPP
