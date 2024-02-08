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

#ifndef PULSAR_DETAILS_TXQUADIMPL_IPP
#define PULSAR_DETAILS_TXQUADIMPL_IPP

#include "TxQuadDecl.hpp"

namespace pul
{
    constexpr TxQuad::TxQuad() noexcept
        :
        m_Rect(),
        m_Tex(nullptr)
    {
    }

    constexpr TxQuad::TxQuad(const eqx::Rectangle<float>& rect,
        const Texture& tex) noexcept
        :
        m_Rect(rect),
        m_Tex(&tex)
    {
    }

    constexpr void TxQuad::setLoc(const eqx::Point<float>& loc) noexcept
    {
        m_Rect.setLocation(loc);
    }

    constexpr void TxQuad::setRect(const eqx::Rectangle<float>& rect) noexcept
    {
        m_Rect = rect;
    }

    constexpr void TxQuad::setTexture(const Texture& tex) noexcept
    {
        m_Tex = &tex;
    }

    [[nodiscard]] constexpr eqx::Point<float> TxQuad::getLoc() const noexcept
    {
        return m_Rect.getLocation();
    }

    [[nodiscard]] constexpr eqx::Rectangle<float>
        TxQuad::getRect() const noexcept
    {
        return m_Rect;
    }

    [[nodiscard]] constexpr const Texture& TxQuad::getTexture() const noexcept
    {
        return *m_Tex;
    }

    [[nodiscard]] constexpr Batch<5_size, 4_size>
        TxQuad::batch(std::span<TxQuad> quads) noexcept
    {
        /*
            x, y, s, t, tex
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
            temp[2] = 0.0f;
            temp[3] = 0.0f;
            temp[4] = static_cast<float>(i);

            temp[5] = quads[i].getRect().getTopRightPoint().x;
            temp[6] = 800.0f - quads[i].getRect().getTopRightPoint().y;
            temp[7] = 1.0f;
            temp[8] = 0.0f;
            temp[9] = static_cast<float>(i);

            temp[10] = quads[i].getRect().getBottomRightPoint().x;
            temp[11] = 800.0f - quads[i].getRect().getBottomRightPoint().y;
            temp[12] = 1.0f;
            temp[13] = 1.0f;
            temp[14] = static_cast<float>(i);

            temp[15] = quads[i].getRect().getBottomLeftPoint().x;
            temp[16] = 800.0f - quads[i].getRect().getBottomLeftPoint().y;
            temp[17] = 0.0f;
            temp[18] = 1.0f;
            temp[19] = static_cast<float>(i);
        }

        auto count = 0U;
        std::ranges::for_each(quads, [&count](const TxQuad& quad)
            {
                Texture::enableTextureSlot(count);
                quad.getTexture().enable();
                count++;
            });

        return result;
    }

    [[nodiscard]] constexpr std::span<const int> TxQuad::getAttribs() noexcept
    {
        return std::span<const int>(c_Attribs);
    }

    [[nodiscard]] constexpr
        std::span<const unsigned int> TxQuad::getIndices() noexcept
    {
        return std::span<const unsigned int>(c_Indices);
    }
}

#endif // PULSAR_DETAILS_TXQUADIMPL_IPP
