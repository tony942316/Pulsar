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

#ifndef PULSAR_DETAILS_QUADTDECL_HPP
#define PULSAR_DETAILS_QUADTDECL_HPP

#include "Dependencies.hpp"

#include "../batch/QuadT.hpp"

namespace pul
{
    class QuadT
    {
    public:
        explicit inline QuadT() noexcept;

        inline void setLoc(const eqx::Point<float>& loc) noexcept;
        inline void setRect(const eqx::Rectangle<float>& rect) noexcept;
        inline void setTexture(const Texture& tex) noexcept;

        [[nodiscard]] inline eqx::Point<float> getLoc() const noexcept;
        [[nodiscard]] inline eqx::Rectangle<float> getRect() const noexcept;
        [[nodiscard]] inline const Texture& getTexture() const noexcept;

        [[nodiscard]] static inline const pul::batch::QuadT&
            getBatch() noexcept;

    private:
        std::size_t m_BatchIndex;

        constinit static inline auto s_BatchSize = 0_size;
        constinit static inline auto s_Batch = pul::batch::QuadT();

    };
}

#endif // PULSAR_DETAILS_QUADTDECL_HPP
