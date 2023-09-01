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

#ifndef PULSAR_DETAILS_VERTEXBUFFERDECL_HPP
#define PULSAR_DETAILS_VERTEXBUFFERDECL_HPP

#include "VertexBufferDecl.hpp"

namespace pul
{
    constexpr VertexBuffer::VertexBuffer() noexcept
        :
        m_VAO(),
        m_VBO(),
        m_Vertices(),
        m_Attribs()
    {
    }

    template <typename T, typename U>
        requires eqx::ConstCollection<T> && eqx::ConstCollection<U>
    inline VertexBuffer::VertexBuffer(const T& vertices,
        const U& attribs) noexcept
    {
        init(vertices, attribs);
    }

    template <typename T, typename U>
        requires eqx::ConstCollection<T> && eqx::ConstCollection<U>
    void VertexBuffer::init(const T& vertices, const U& attribs) noexcept
    {
        if (m_VAO.get() != 0U)
        {
            free();
        }

        m_VAO.init(delVA, genVA);
        m_VBO.init(delVB, genVB);
        m_Vertices.init(delVertices, genVertices);
        m_Attribs.init(delAttribs, genAttribs);

        m_Vertices.get()->reserve(std::ranges::size(vertices));
        std::ranges::copy(vertices, std::back_inserter(*m_Vertices.get()));

        m_Attribs.get()->reserve(std::ranges::size(attribs));
        std::ranges::copy(attribs, std::back_inserter(*m_Attribs.get()));

        enable();
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO.get());

        const auto val = sizeof(float) * std::ranges::size(*m_Vertices.get());
        glBufferData(GL_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(val),
            m_Vertices.get()->data(),
            GL_STATIC_DRAW);

        const auto vertexSize = static_cast<GLsizei>(std::accumulate(
            std::ranges::cbegin(*m_Attribs.get()),
            std::ranges::cend(*m_Attribs.get()), 0)) * static_cast<GLsizei>(sizeof(float));
        auto runningCount = 0U;
        auto currentIndex = static_cast<GLuint>(0);

        std::ranges::for_each(*m_Attribs.get(),
            [&](int val)
            {
                glVertexAttribPointer(currentIndex, val, GL_FLOAT, GL_FALSE,
                    vertexSize,
                    (void*)(runningCount * sizeof(float)));
                glEnableVertexAttribArray(currentIndex);
                currentIndex++;
                runningCount += static_cast<unsigned int>(val);
            });

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        disable();
    }

    inline void VertexBuffer::free() noexcept
    {
        eqx::runtimeAssert(m_VAO.get() != 0U,
            "No Buffer To Free!"sv);

        m_VAO.free();
        m_VBO.free();
        m_Vertices.free();
        m_Attribs.free();
    }

    inline void VertexBuffer::enable() const noexcept
    {
        eqx::runtimeAssert(m_VAO.get() != 0U,
            "No VertexBuffer To Enable!"sv);

        glBindVertexArray(m_VAO.get());
    }

    inline void VertexBuffer::disable() const noexcept
    {
        glBindVertexArray(0U);
    }

    [[nodiscard]] inline const std::vector<float>&
        VertexBuffer::getVertices() const noexcept
    {
        return *m_Vertices.get();
    }

    [[nodiscard]] inline unsigned int VertexBuffer::genVB() noexcept
    {
        unsigned int vb = 0;
        glGenBuffers(1, &vb);
        return vb;
    }

    [[nodiscard]] inline unsigned int VertexBuffer::genVA() noexcept
    {
        unsigned int va = 0;
        glGenVertexArrays(1, &va);
        return va;
    }

    inline void VertexBuffer::delVB(unsigned int vb) noexcept
    {
        glDeleteBuffers(1, &vb);
    }

    inline void VertexBuffer::delVA(unsigned int va) noexcept
    {
        glDeleteVertexArrays(1, &va);
    }

    [[nodiscard]] inline std::vector<float>*
        VertexBuffer::genVertices() noexcept
    {
        return new std::vector<float>();
    }

    [[nodiscard]] inline std::vector<int>* VertexBuffer::genAttribs() noexcept
    {
        return new std::vector<int>();
    }

    inline void VertexBuffer::delVertices(
        std::vector<float>* vertices) noexcept
    {
        delete vertices;
    }

    inline void VertexBuffer::delAttribs(std::vector<int>* attribs) noexcept
    {
        delete attribs;
    }
}

#endif // PULSAR_DETAILS_VERTEXBUFFERDECL_HPP
