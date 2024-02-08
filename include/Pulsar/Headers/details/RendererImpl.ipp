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

    inline void Renderer::draw(const TxQuad& quad) noexcept
    {
        auto x = std::array<TxQuad, 1_size>({ quad });
        draw(x);
    }

    inline void Renderer::draw(const CQuad& quad) noexcept
    {
        auto x = std::array<CQuad, 1_size>({ quad });
        draw(x);
    }

    inline void Renderer::draw(std::span<TxQuad> quads) noexcept
    {
        drawQuads(EmbShaders::TxQuadShader(), quads);
    }

    inline void Renderer::draw(std::span<CQuad> quads) noexcept
    {
        drawQuads(EmbShaders::CQuadShader(), quads);
    }

    inline void Renderer::drawText(std::span<TxQuad> quads) noexcept
    {
        drawQuads(EmbShaders::FontShader(), quads);
    }

    inline void Renderer::drawQuads(const Shader& shader,
        std::span<TxQuad> quads) noexcept
    {
        glDisable(GL_DEPTH_TEST);

        auto remaining = quads;
        auto chunk = std::span<TxQuad>();

        while (remaining.size() > 32_size)
        {
            chunk = remaining.first(32_size);
            s_VA.clear();
            s_VA.addVertices(TxQuad::batch(chunk).getData());
            s_VA.addIndices(TxQuad::getIndices());
            s_VA.setAttribs(TxQuad::getAttribs());
            draw(shader, s_VA);
            remaining = remaining.subspan(32_size);
        }

        s_VA.clear();
        s_VA.addVertices(TxQuad::batch(remaining).getData());
        s_VA.addIndices(TxQuad::getIndices());
        s_VA.setAttribs(TxQuad::getAttribs());
        draw(shader, s_VA);

        glEnable(GL_DEPTH_TEST);
    }

    inline void Renderer::drawQuads(const Shader& shader,
        std::span<CQuad> quads) noexcept
    {
        glDisable(GL_DEPTH_TEST);

        auto remaining = quads;
        auto chunk = std::span<CQuad>();

        while (remaining.size() > 32_size)
        {
            chunk = remaining.first(32_size);
            s_VA.clear();
            s_VA.addVertices(CQuad::batch(chunk).getData());
            s_VA.addIndices(CQuad::getIndices());
            s_VA.setAttribs(CQuad::getAttribs());
            draw(shader, s_VA);
            remaining = remaining.subspan(32_size);
        }

        s_VA.clear();
        s_VA.addVertices(CQuad::batch(remaining).getData());
        s_VA.addIndices(CQuad::getIndices());
        s_VA.setAttribs(CQuad::getAttribs());
        draw(shader, s_VA);

        glEnable(GL_DEPTH_TEST);
    }

    inline void Renderer::boot() noexcept
    {
        s_VA.init();
    }
}

#endif // PULSAR_DETAILS_RENDERERIMPL_IPP
