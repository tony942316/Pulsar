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

#ifndef PULSAR_DETAILS_VERTEXARRAYDECL_HPP
#define PULSAR_DETAILS_VERTEXARRAYDECL_HPP

#include "Dependencies.hpp"

namespace pul
{
    class VertexArray
    {
    public:
        explicit constexpr VertexArray() noexcept;

        inline void init() noexcept;

        inline void clear() noexcept;

        template <typename T>
            requires requires (const T& vertices)
                {
                    std::ranges::data(vertices);
                    std::ranges::size(vertices);
                }
        inline void addVertices(const T& vertices) noexcept;

        template <typename T>
            requires eqx::ConstCollection<T>
        inline void setAttribs(const T& attribs) noexcept;

        template <typename T>
        requires requires (const T& indices)
            {
                std::ranges::data(indices);
                std::ranges::size(indices);
            }
        inline void addIndices(const T& indices) noexcept;

        inline void enable() const noexcept;
        inline void disable() const noexcept;

        [[nodiscard]] inline const std::vector<int>&
            getAttribs() const noexcept;
        [[nodiscard]] inline std::size_t getIndexCount() const noexcept;

    private:
        [[nodiscard]] static inline unsigned int genVA() noexcept;
        [[nodiscard]] static inline unsigned int genBuf() noexcept;
        static inline void delVA(unsigned int va) noexcept;
        static inline void delBuf(unsigned int vb) noexcept;

        std::size_t m_VBSize;
        std::size_t m_EBSize;
        std::size_t m_Capacity;

        eqx::UniquePointer<std::vector<int>> m_Attribs;

        using VAO = eqx::UniqueResource<unsigned int, decltype(&delVA)>;
        using Buffer = eqx::UniqueResource<unsigned int, decltype(&delBuf)>;

        VAO m_VAO;
        Buffer m_VBO;
        Buffer m_EBO;
    };
}

#endif // PULSAR_DETAILS_VERTEXARRAYDECL_HPP
