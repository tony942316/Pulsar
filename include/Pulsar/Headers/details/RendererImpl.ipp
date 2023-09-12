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

#ifndef PULSAR_DETAILS_RENDERERIMPL_IPP
#define PULSAR_DETAILS_RENDERERIMPL_IPP

#include "RendererDecl.hpp"

namespace pul
{
    inline void Renderer::draw(const Shader& shader,
        const VertexArray& vertexArray) noexcept
    {
        shader.enable();
        vertexArray.enable();

        glDrawElements(GL_TRIANGLES,
            static_cast<int>(vertexArray.getIndexCount()),
            GL_UNSIGNED_INT, 0);

        vertexArray.disable();
        shader.disable();
    }

    inline void Renderer::draw(Quad& quad) noexcept
    {
        s_VA.clear();
        s_VA.addVertices(quad.getVertexData());
        s_VA.addIndices(Quad::getIndices());

        Texture::enableTextureSlot(0U);
        quad.setTextureIndex(0U);
        quad.getTexture().enable();

        draw(s_QuadShader, s_VA);

        quad.getTexture().disable();
    }

    inline void Renderer::draw(std::vector<Quad>& quads) noexcept
    {
        s_VA.clear();
        std::ranges::for_each(std::views::iota(0,
                static_cast<int>(std::ranges::size(quads))),
            [&quads](int val)
            {
                auto& quad = quads[static_cast<std::size_t>(val)];
                s_VA.addVertices(quad.getVertexData());

                auto v = Quad::getIndices() |
                    std::views::transform([val](unsigned int x)
                        { return x + (4U * static_cast<unsigned int>(val)); });
                auto indices = std::array<unsigned int, 6_size>();
                std::ranges::copy(v, std::ranges::begin(indices));
                s_VA.addIndices(indices);

                Texture::enableTextureSlot(static_cast<unsigned int>(val));
                quad.setTextureIndex(static_cast<unsigned int>(val));
                quad.getTexture().enable();
            });

        draw(s_QuadShader, s_VA);
    }

    inline void Renderer::init(float width, float height) noexcept
    {
        s_VA.init();
        s_VA.setAttribs(Quad::getAttribs());

        s_QuadShader.init("Resources/Shaders/QuadVertex.glsl"sv,
            "Resources/Shaders/QuadFragment.glsl"sv);
        auto projection = glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
        s_QuadShader.setMat4("u_Projection", projection);
        s_QuadShader.setMat4("u_View", glm::mat4(1.0f));
        auto textures = std::array<int, 32_size>();
        std::ranges::copy(std::views::iota(0, 32), textures.begin());
        s_QuadShader.setInts("u_Textures", textures);
    }
}

#endif // PULSAR_DETAILS_RENDERERIMPL_IPP
