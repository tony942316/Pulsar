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

#ifndef PULSAR_INDEXBUFFERDECL_HPP
#define PULSAR_INDEXBUFFERDECL_HPP

#include "Dependencies.hpp"

namespace pul
{
    class IndexBuffer
    {
    public:
        explicit constexpr IndexBuffer() noexcept;
        template <typename T>
            requires eqx::ConstCollection<T>
        explicit inline IndexBuffer(const T& indices) noexcept;

        template <typename T>
            requires eqx::ConstCollection<T>
        inline void init(const T& indices) noexcept;

        inline void enable() const noexcept;
        inline void disable() const noexcept;

        inline void free() noexcept;

        [[nodiscard]] inline const std::vector<unsigned int>&
            getIndices() const noexcept;
        [[nodiscard]] inline std::size_t getCount() const noexcept;

    private:
        [[nodiscard]] static inline unsigned int genEB() noexcept;
        static inline void delEB(unsigned int eb) noexcept;
        [[nodiscard]] static inline std::vector<unsigned int>*
            genIndices() noexcept;
        static inline void delIndices(
            std::vector<unsigned int>* indices) noexcept;

        using EBO = eqx::UniqueResource<unsigned int, decltype(&delEB)>;
        using Indices =
            eqx::UniqueResource<std::vector<unsigned int>*,
                decltype(&delIndices)>;

        EBO m_EBO;
        Indices m_Indices;
    };
}

#endif // PULSAR_INDEXBUFFERDECL_HPP
