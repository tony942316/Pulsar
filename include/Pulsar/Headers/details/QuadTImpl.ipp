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

#ifndef PULSAR_DETAILS_QUADTIMPL_IPP
#define PULSAR_DETAILS_QUADTIMPL_IPP

#include "QuadTDecl.hpp"

namespace pul
{
    inline QuadT::QuadT() noexcept
        :
        m_BatchIndex(0_size)
    {
        m_BatchIndex = s_BatchSize;
        s_BatchSize++;
        eqx::runtimeAssert(s_BatchSize < 32, "Batch Limit Hit!");
    }

    inline void QuadT::setLoc(const eqx::Point<float>& loc) noexcept
    {
        s_Batch.setLoc(m_BatchIndex, loc);
    }

    inline void QuadT::setRect(const eqx::Rectangle<float>& rect) noexcept
    {
        s_Batch.setRect(m_BatchIndex, rect);
    }

    inline void QuadT::setTexture(const Texture& tex) noexcept
    {
        s_Batch.setTexture(m_BatchIndex, tex);
    }

    [[nodiscard]] inline eqx::Point<float> QuadT::getLoc() const noexcept
    {
        return s_Batch.getLoc(m_BatchIndex);
    }

    [[nodiscard]] inline eqx::Rectangle<float>
        QuadT::getRect() const noexcept
    {
        return s_Batch.getRect(m_BatchIndex);
    }

    [[nodiscard]] inline const Texture& QuadT::getTexture() const noexcept
    {
        return s_Batch.getTexture(m_BatchIndex);
    }

    [[nodiscard]] inline const pul::batch::QuadT& QuadT::getBatch() noexcept
    {
        return s_Batch;
    }
}

#endif // PULSAR_DETAILS_QUADTIMPL_IPP
