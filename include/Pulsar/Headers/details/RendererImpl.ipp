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

    inline void Renderer::draw(const batch::Quad& quads) noexcept
    {
        quads.enableTextures();
        s_VA.clear();
        s_VA.addVertices(quads.getData());
        s_VA.addIndices(batch::Quad::getIndices());
        s_VA.setAttribs(batch::Quad::getAttribs());
        draw(shader::getQuad(), s_VA);
    }

    inline void Renderer::drawText(const batch::Quad& quads) noexcept
    {
        quads.enableTextures();
        s_VA.clear();
        s_VA.addVertices(quads.getData());
        s_VA.addIndices(batch::Quad::getIndices());
        s_VA.setAttribs(batch::Quad::getAttribs());

        draw(shader::getText(), s_VA);
    }

    inline void Renderer::init() noexcept
    {
        s_VA.init();
    }
}

#endif // PULSAR_DETAILS_RENDERERIMPL_IPP
