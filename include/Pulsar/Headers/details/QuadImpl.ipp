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

#ifndef PULSAR_DETAILS_QUADIMPL_IPP
#define PULSAR_DETAILS_QUADIMPL_IPP

#include "QuadDecl.hpp"

namespace pul
{
    constexpr Quad::Quad() noexcept
        :
        m_Texture(nullptr),
        m_VertexData()
    {
        m_VertexData.at(c_X[0_size] + 2_size) = 0.0f;
        m_VertexData.at(c_X[0_size] + 3_size) = 0.0f;

        m_VertexData.at(c_X[1_size] + 2_size) = 1.0f;
        m_VertexData.at(c_X[1_size] + 3_size) = 0.0f;

        m_VertexData.at(c_X[2_size] + 2_size) = 1.0f;
        m_VertexData.at(c_X[2_size] + 3_size) = 1.0f;

        m_VertexData.at(c_X[3_size] + 2_size) = 0.0f;
        m_VertexData.at(c_X[3_size] + 3_size) = 1.0f;

        m_VertexData.at(c_X[3_size] + 9_size) = 0.0f;
    }

    inline Quad::Quad(const eqx::Rectangle<float>& drawBox) noexcept
        :
        Quad()
    {
        setDrawBox(drawBox);
    }

    inline void Quad::setMixture(float mixture) noexcept
    {
        std::ranges::for_each(c_M,
            [&](std::size_t index)
            {
                m_VertexData.at(index) = mixture;
            });
    }

    inline void Quad::setColor(const glm::vec4 color) noexcept
    {
        std::ranges::for_each(c_R,
            [&](std::size_t index)
            {
                m_VertexData.at(index) = color.r;
                m_VertexData.at(index + 1_size) = color.g;
                m_VertexData.at(index + 2_size) = color.b;
                m_VertexData.at(index + 3_size) = color.a;
            });
    }

    inline void Quad::setDrawBox(
        const eqx::Rectangle<float>& drawBox) noexcept
    {
        m_VertexData.at(c_X.at(0_size)) = drawBox.x;
        m_VertexData.at(c_X.at(0_size) + 1_size) = 800.0f - drawBox.y;

        m_VertexData.at(c_X.at(1_size)) = drawBox.getTopRightPoint().x;
        m_VertexData.at(c_X.at(1_size) + 1_size) =
            800.0f - drawBox.getTopRightPoint().y;

        m_VertexData.at(c_X.at(2_size)) = drawBox.getBottomRightPoint().x;
        m_VertexData.at(c_X.at(2_size) + 1_size) =
            800.0f - drawBox.getBottomRightPoint().y;

        m_VertexData.at(c_X.at(3_size)) = drawBox.getBottomLeftPoint().x;
        m_VertexData.at(c_X.at(3_size) + 1_size) =
            800.0f - drawBox.getBottomLeftPoint().y;
    }

    inline void Quad::setTexture(Texture* tex) noexcept
    {
        m_Texture = tex;
    }

    inline void Quad::setTextureIndex(unsigned int index) noexcept
    {
        std::ranges::for_each(c_T,
            [&](std::size_t t)
            {
                m_VertexData.at(t) = static_cast<float>(index);
            });
    }

    [[nodiscard]] constexpr const Texture& Quad::getTexture() const noexcept
    {
        return *m_Texture;
    }

    [[nodiscard]] constexpr const std::array<float, 40_size>&
        Quad::getVertexData() const noexcept
    {
        return m_VertexData;
    }

    [[nodiscard]] constexpr eqx::Rectangle<float>
        Quad::getDrawBox() const noexcept
    {
        return eqx::Rectangle<float>(m_VertexData.at(c_X[0_size]),
            800.0f - m_VertexData.at(c_X[0_size] + 1_size),
            m_VertexData.at(c_X[2_size]) - m_VertexData.at(c_X[0_size]),
            m_VertexData.at(c_X[2_size] + 1_size) -
                m_VertexData.at(c_X[2_size] + 1_size));
    }

    [[nodiscard]] constexpr glm::vec4 Quad::getColor() const noexcept
    {
        return glm::vec4(m_VertexData.at(c_R[0_size]),
            m_VertexData.at(c_R[0_size] + 1_size),
            m_VertexData.at(c_R[0_size] + 2_size),
            m_VertexData.at(c_R[0_size] + 3_size));
    }

    [[nodiscard]] constexpr float Quad::getMixture() const noexcept
    {
        return m_VertexData.at(c_M[0_size]);
    }

    [[nodiscard]] constexpr const std::array<int, 5_size>&
        Quad::getAttribs() noexcept
    {
        return c_Attribs;
    }

    [[nodiscard]] constexpr const std::array<unsigned int, 6_size>&
        Quad::getIndices() noexcept
    {
        return c_Indices;
    }
}

#endif // PULSAR_DETAILS_QUADIMPL_IPP
