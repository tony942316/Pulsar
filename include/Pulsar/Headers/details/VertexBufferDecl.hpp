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

#ifndef PULSAR_DETAILS_VERTEXBUFFERIMPL_IPP
#define PULSAR_DETAILS_VERTEXBUFFERIMPL_IPP

#include "Dependencies.hpp"

namespace pul
{
    class VertexBuffer
    {
    public:
        explicit constexpr VertexBuffer() noexcept;
        template <typename T, typename U>
            requires eqx::ConstCollection<T> && eqx::ConstCollection<U>
        explicit inline VertexBuffer(const T& vertices,
            const U& attribs) noexcept;

        template <typename T, typename U>
            requires eqx::ConstCollection<T> && eqx::ConstCollection<U>
        void init(const T& vertices, const U& attribs) noexcept;

        inline void free() noexcept;

        inline void enable() const noexcept;
        inline void disable() const noexcept;

        [[nodiscard]] inline const std::vector<float>&
            getVertices() const noexcept;

    private:
        [[nodiscard]] static inline unsigned int genVB() noexcept;
        [[nodiscard]] static inline unsigned int genVA() noexcept;
        static inline void delVB(unsigned int vb) noexcept;
        static inline void delVA(unsigned int va) noexcept;

        [[nodiscard]] static inline std::vector<float>* genVertices() noexcept;
        [[nodiscard]] static inline std::vector<int>* genAttribs() noexcept;
        static inline void delVertices(std::vector<float>* vertices) noexcept;
        static inline void delAttribs(std::vector<int>* attribs) noexcept;

        using VBO = eqx::UniqueResource<unsigned int, decltype(&delVB)>;
        using VAO = eqx::UniqueResource<unsigned int, decltype(&delVA)>;
        using Vertices =
            eqx::UniqueResource<std::vector<float>*, decltype(&delVertices)>;
        using Attribs =
            eqx::UniqueResource<std::vector<int>*, decltype(&delAttribs)>;

        VAO m_VAO;
        VBO m_VBO;
        Vertices m_Vertices;
        Attribs m_Attribs;
    };
}

#endif // PULSAR_DETAILS_VERTEXBUFFERIMPL_IPP
