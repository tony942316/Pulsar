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

#ifndef PROVINGGROUNDS_DETAILS_CUBETESTIMPL_IPP
#define PROVINGGROUNDS_DETAILS_CUBETESTIMPL_IPP

#include "CubeTestDecl.hpp"

inline void CubeTest::update(float dt) noexcept
{
    [[maybe_unused]] static auto init = std::invoke(
        []()
        {
            auto vertices = std::vector<float>({
                -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,

                -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f });

            auto indices = std::vector<unsigned int>({
                0U, 1U, 2U,
                0U, 2U, 3U,

                4U, 5U, 6U,
                4U, 6U, 7U,

                1U, 5U, 6U,
                1U, 6U, 2U,

                4U, 0U, 3U,
                4U, 3U, 7U,

                0U, 4U, 5U,
                0U, 5U, 1U,

                6U, 7U, 3U,
                6U, 3U, 2U });

            auto attribs = std::vector<int>({
                3, 3 });

            s_Shader.init("Resources/Shaders/MVPVertex.glsl",
                "Resources/Shaders/MVPFragment.glsl");
            auto view = glm::mat4(1.0f);
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
            auto proj = glm::mat4(1.0f);
            proj = glm::perspective(glm::radians(90.0f), 1200.0f / 800.0f, 0.1f, 1000.0f);
            //proj = glm::ortho(0.0f, 1200.0f, 0.0f, 800.0f, 0.1f, 1000.0f);

            s_Shader.setMat4("u_Model", s_Model);
            s_Shader.setMat4("u_View", view);
            s_Shader.setMat4("u_Projection", proj);

            s_VA.init();
            s_VA.addVertices(vertices);
            s_VA.addIndices(indices);
            s_VA.setAttribs(attribs);

            return true;
        });

    static constexpr auto c_RotX = 20.0f;
    static constexpr auto c_RotY = 10.0f;
    s_Model = glm::rotate(s_Model, glm::radians(c_RotX * dt),
        glm::vec3(1.0f, 0.0f, 0.0f));
    s_Model = glm::rotate(s_Model, glm::radians(c_RotY * dt),
        glm::vec3(0.0f, 1.0f, 0.0f));
    s_Shader.setMat4("u_Model", s_Model);
}

inline void CubeTest::render() noexcept
{
    pul::Renderer::draw(s_Shader, s_VA);
}

#endif // PROVINGGROUNDS_DETAILS_CUBETESTIMPL_IPP
