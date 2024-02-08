/*
 * Copyright (C) 2024 Anthony H. Grasso
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

#ifndef PULSAR_DETAILS_CQUADIMPL_IPP
#define PULSAR_DETAILS_CQUADIMPL_IPP

#include "CQuadDecl.hpp"

namespace pul
{
    constexpr CQuad::CQuad() noexcept
        :
        m_Rect(),
        m_Color()
    {
    }

    constexpr CQuad::CQuad(const eqx::Rectangle<float>& rect,
        const color& c) noexcept
        :
        m_Rect(rect),
        m_Color(c)
    {
    }

    constexpr void CQuad::setLoc(const eqx::Point<float>& loc) noexcept
    {
        m_Rect.setLocation(loc);
    }

    constexpr void CQuad::setRect(const eqx::Rectangle<float>& rect) noexcept
    {
        m_Rect = rect;
    }

    constexpr void CQuad::setColor(const color& c) noexcept
    {
        m_Color = c;
    }

    [[nodiscard]] constexpr eqx::Point<float> CQuad::getLoc() const noexcept
    {
        return m_Rect.getLocation();
    }

    [[nodiscard]] constexpr const eqx::Rectangle<float>&
        CQuad::getRect() const noexcept
    {
        return m_Rect;
    }

    [[nodiscard]] constexpr const CQuad::color& CQuad::getColor() const noexcept
    {
        return m_Color;
    }

    [[nodiscard]] constexpr Batch<5_size, 4_size>
        CQuad::batch(std::span<CQuad> quads) noexcept
    {
        /*
            x, y, r, g, b
            0, 1, 2, 3, 4
            0, ...
            0, ...
            0, ...
        */
        auto result = Batch<5_size, 4_size>();

        auto temp = std::span<float>();
        for (auto i = 0_size; i < quads.size(); i++)
        {
            temp = result.getObject(i);

            temp[0] = quads[i].getRect().getTopLeftPoint().x;
            temp[1] = 800.0f - quads[i].getRect().getTopLeftPoint().y;
            temp[2] = quads[i].m_Color.r;
            temp[3] = quads[i].m_Color.g;
            temp[4] = quads[i].m_Color.b;

            temp[5] = quads[i].getRect().getTopRightPoint().x;
            temp[6] = 800.0f - quads[i].getRect().getTopRightPoint().y;
            temp[7] = quads[i].m_Color.r;
            temp[8] = quads[i].m_Color.g;
            temp[9] = quads[i].m_Color.b;

            temp[10] = quads[i].getRect().getBottomRightPoint().x;
            temp[11] = 800.0f - quads[i].getRect().getBottomRightPoint().y;
            temp[12] = quads[i].m_Color.r;
            temp[13] = quads[i].m_Color.g;
            temp[14] = quads[i].m_Color.b;

            temp[15] = quads[i].getRect().getBottomLeftPoint().x;
            temp[16] = 800.0f - quads[i].getRect().getBottomLeftPoint().y;
            temp[17] = quads[i].m_Color.r;
            temp[18] = quads[i].m_Color.g;
            temp[19] = quads[i].m_Color.b;
        }

        return result;
    }

    [[nodiscard]] constexpr std::span<const int> CQuad::getAttribs() noexcept
    {
        return std::span<const int>(c_Attribs);
    }

    [[nodiscard]] constexpr
        std::span<const unsigned int> CQuad::getIndices() noexcept
    {
        return std::span<const unsigned int>(c_Indices);
    }
}

#endif // PULSAR_DETAILS_CQUADIMPL_IPP
