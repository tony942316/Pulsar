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

#ifndef PULSAR_DETAILS_BATCHDECL_HPP
#define PULSAR_DETAILS_BATCHDECL_HPP

#include "Dependencies.hpp"

namespace pul
{
    template <std::size_t vsize, std::size_t vcount>
    class Batch
    {
    private:
        static constexpr auto c_ObjStride = vsize * vcount;
        static constexpr auto c_ObjCount = 32_size;

    public:
        explicit constexpr Batch() noexcept;

        [[nodiscard]] constexpr std::span<float>
            getObject(std::size_t index) noexcept;
        [[nodiscard]] constexpr std::span<const float>
            getObject(std::size_t index) const noexcept;
        constexpr void swapObjects(std::size_t l, std::size_t r) noexcept;

        [[nodiscard]] constexpr std::span<const float> getData() const noexcept;

    private:
        [[nodiscard]] constexpr auto
            getIter(std::size_t index) noexcept;
        [[nodiscard]] constexpr auto
            getIter(std::size_t index) const noexcept;
        [[nodiscard]] constexpr std::size_t
            getOffset(std::size_t index) const noexcept;

        std::array<float, c_ObjStride * c_ObjCount> m_Data;
    };
}

#endif // PULSAR_DETAILS_BATCHDECL_HPP
