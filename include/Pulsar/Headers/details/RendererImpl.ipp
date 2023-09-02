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
        const VertexBuffer& vertexBuffer,
        const IndexBuffer& indexBuffer) noexcept
    {
        shader.enable();
        vertexBuffer.enable();
        indexBuffer.enable();

        glDrawElements(GL_TRIANGLES, static_cast<int>(indexBuffer.getCount()),
            GL_UNSIGNED_INT, 0);

        shader.disable();
        vertexBuffer.disable();
        indexBuffer.disable();
    }

    inline void Renderer::draw(const Quad& quad) noexcept
    {
        quad.setUniforms();

        Texture::enableTextureSlot(0U);
        quad.getTexture().enable();

        draw(Quad::getShader(), Quad::getVertexBuffer(),
            Quad::getIndexBuffer());

        Texture::enableTextureSlot(0U);
        quad.getTexture().disable();

        Quad::cleanUniforms();
    }
}

#endif // PULSAR_DETAILS_RENDERERIMPL_IPP
