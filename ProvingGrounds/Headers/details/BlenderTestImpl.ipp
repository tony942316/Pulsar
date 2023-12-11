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

#ifndef PROVINGGROUNDS_DETAILS_BLENDERTESTIMPL_IPP
#define PROVINGGROUNDS_DETAILS_BLENDERTESTIMPL_IPP

#include "BlenderTestDecl.hpp"

inline void BlenderTest::update(float dt) noexcept
{
    [[maybe_unused]] static auto init = loadFile();

    static constexpr auto c_RotX = 20.0f;
    static constexpr auto c_RotY = 10.0f;
    s_Model = glm::rotate(s_Model, glm::radians(c_RotX * dt),
        glm::vec3(1.0f, 0.0f, 0.0f));
    s_Model = glm::rotate(s_Model, glm::radians(c_RotY * dt),
        glm::vec3(0.0f, 1.0f, 0.0f));
    s_Shader.setMat4("u_Model", s_Model);
}

inline void BlenderTest::render() noexcept
{
    pul::Renderer::draw(s_Shader, s_VA);
}

inline bool BlenderTest::loadFile() noexcept
{
    s_VA.init();

    auto vertices = std::vector<float>();
    auto indices = std::vector<unsigned int>();

    auto file = std::ifstream();
    file.open("Resources/Meshes/sword.obj", std::ios::in);

    auto line = std::string();
    while (file.eof() == false)
    {
        std::getline(file, line, '\n');

        if (line.size() == 0)
            continue;

        if (line.at(0) == 'v' && line.at(1) == ' ')
        {
            auto v = line |
                std::views::split(' ') |
                std::views::drop(1);
            for (const auto word : v)
            {
                auto temp = std::string();
                std::ranges::copy(word, std::back_inserter(temp));
                vertices.emplace_back(std::atof(temp.c_str()));
            }

            auto rng = eqx::Random::rollDice(4U);

            switch (rng)
            {
            case 1U:
                vertices.emplace_back(1.0f);
                vertices.emplace_back(0.0f);
                vertices.emplace_back(0.0f);
                break;
            case 2U:
                vertices.emplace_back(0.0f);
                vertices.emplace_back(1.0f);
                vertices.emplace_back(0.0f);
                break;
            case 3U:
                vertices.emplace_back(0.0f);
                vertices.emplace_back(0.0f);
                vertices.emplace_back(1.0f);
                break;
            case 4U:
                vertices.emplace_back(1.0f);
                vertices.emplace_back(1.0f);
                vertices.emplace_back(1.0f);
                break;
            default:
                eqx::runtimeAssert(false, "Invalid Switch Case!");
                break;
            }
        }
        else if (line.at(0) == 'f')
        {

            auto v = line |
                std::views::split(' ') |
                std::views::drop(1);
            auto corners = std::vector<float>();

            for (const auto data : v)
            {
                auto index = data |
                    std::views::split('/') |
                    std::views::take(1);
                auto temp = std::string();
                for (const auto what : index)
                {
                    std::ranges::copy(what, std::back_inserter(temp));
                }
                corners.emplace_back((unsigned int)std::atoi(temp.c_str()) - 1U);
            }
            if (corners.size() == 4)
            {
                indices.emplace_back(corners.at(0));
                indices.emplace_back(corners.at(1));
                indices.emplace_back(corners.at(2));

                indices.emplace_back(corners.at(0));
                indices.emplace_back(corners.at(2));
                indices.emplace_back(corners.at(3));
            }
            else if (corners.size() == 3)
            {
                indices.emplace_back(corners.at(0));
                indices.emplace_back(corners.at(1));
                indices.emplace_back(corners.at(2));
            }
        }
    }

    s_VA.addVertices(vertices);
    s_VA.addIndices(indices);
    s_VA.setAttribs(std::array<int, 2ULL>({ 3, 3 }));

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

    return true;
}

#endif // PROVINGGROUNDS_DETAILS_BLENDERTESTIMPL_IPP
