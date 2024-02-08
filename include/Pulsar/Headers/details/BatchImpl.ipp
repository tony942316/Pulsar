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

#ifndef PULSAR_DETAILS_BATCHIMPL_IPP
#define PULSAR_DETAILS_BATCHIMPL_IPP

#include "BatchDecl.hpp"

namespace pul
{
    template <std::size_t vsize, std::size_t vcount>
    constexpr Batch<vsize, vcount>::Batch() noexcept
        :
        m_Data()
    {
    }

    template <std::size_t vsize, std::size_t vcount>
    [[nodiscard]] constexpr std::span<float>
        Batch<vsize, vcount>::getObject(std::size_t index) noexcept
    {
        return std::span<float>(getIter(index), c_ObjStride);
    }

    template <std::size_t vsize, std::size_t vcount>
    [[nodiscard]] constexpr std::span<const float>
        Batch<vsize, vcount>::getObject(std::size_t index) const noexcept
    {
        return std::span<const float>(getIter(index), c_ObjStride);
    }

    template <std::size_t vsize, std::size_t vcount>
    constexpr void Batch<vsize, vcount>::swapObjects(std::size_t l,
        std::size_t r) noexcept
    {
        eqx::runtimeAssert(l != r, "Can't Swap The Same Object!"sv);
        std::ranges::swap_ranges(
            getIter(l), getIter(l) + c_ObjStride, getIter(r));
    }

    template <std::size_t vsize, std::size_t vcount>
    [[nodiscard]] constexpr std::span<const float>
        Batch<vsize, vcount>::getData() const noexcept
    {
        return std::span<const float>(m_Data);
    }

    template <std::size_t vsize, std::size_t vcount>
    [[nodiscard]] constexpr auto
        Batch<vsize, vcount>::getIter(std::size_t index) noexcept
    {
        return std::ranges::begin(m_Data) + getOffset(index);
    }

    template <std::size_t vsize, std::size_t vcount>
    [[nodiscard]] constexpr auto
        Batch<vsize, vcount>::getIter(std::size_t index) const noexcept
    {
        return std::ranges::cbegin(m_Data) + getOffset(index);
    }

    template <std::size_t vsize, std::size_t vcount>
    [[nodiscard]] constexpr std::size_t
        Batch<vsize, vcount>::getOffset(std::size_t index) const noexcept
    {
        eqx::runtimeAssert(index < c_ObjCount,
            "Index Out Of Bounds!"sv);
        return index * c_ObjStride;
    }
}

#endif // PULSAR_DETAILS_BATCHIMPL_IPP
