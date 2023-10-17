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

#ifndef PULSAR_DETAILS_VERTEXARRAYIMPL_IPP
#define PULSAR_DETAILS_VERTEXARRAYIMPL_IPP

#include "VertexArrayDecl.hpp"

namespace pul
{
    constexpr VertexArray::VertexArray() noexcept
        :
        m_VBSize(0_size),
        m_EBSize(0_size),
        m_Capacity(500'000_size),
        m_Attribs(),
        m_VAO(),
        m_VBO(),
        m_EBO()
    {
    }

    inline void VertexArray::init() noexcept
    {
        m_Attribs.init();
        m_VAO.init(delVA, genVA);
        m_VBO.init(delBuf, genBuf);
        m_EBO.init(delBuf, genBuf);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO.get());
        glBufferData(GL_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(m_Capacity * sizeof(float)),
            nullptr, GL_DYNAMIC_DRAW);

        enable();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO.get());
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(m_Capacity * sizeof(unsigned int)),
            nullptr, GL_DYNAMIC_DRAW);
        disable();
    }

    inline void VertexArray::clear() noexcept
    {
        m_VBSize = 0_size;
        m_EBSize = 0_size;
    }

    template <typename T>
        requires requires (const T& vertices)
            {
                std::ranges::data(vertices);
                std::ranges::size(vertices);
            }
    inline void VertexArray::addVertices(const T& vertices) noexcept
    {
        eqx::runtimeAssert(std::ranges::size(vertices) + m_VBSize < m_Capacity,
            "Too Many Vertices In Vertex Array! "s +
            "Count: "s + eqx::toString(std::ranges::size(vertices)));

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO.get());
        glBufferSubData(GL_ARRAY_BUFFER, m_VBSize,
            static_cast<GLsizeiptr>(std::ranges::size(vertices) *
                sizeof(float)),
            std::ranges::data(vertices));

        m_VBSize += std::ranges::size(vertices) * sizeof(float);
    }

    template <typename T>
        requires eqx::ConstCollection<T>
    inline void VertexArray::setAttribs(const T& attribs) noexcept
    {
        m_Attribs.get()->resize(std::ranges::size(attribs));
        std::ranges::copy(attribs, std::ranges::begin(*m_Attribs.get()));

        const auto vertexSize = static_cast<GLsizei>(std::accumulate(
            std::ranges::cbegin(*m_Attribs.get()),
            std::ranges::cend(*m_Attribs.get()), 0)) *
                static_cast<GLsizei>(sizeof(float));
        auto runningCount = 0U;
        auto currentIndex = static_cast<GLuint>(0);

        enable();
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO.get());

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

        disable();
    }

    template <typename T>
        requires requires (const T& indices)
            {
                std::ranges::data(indices);
                std::ranges::size(indices);
            }
    inline void VertexArray::addIndices(const T& indices) noexcept
    {
        eqx::runtimeAssert(std::ranges::size(indices) + m_EBSize < m_Capacity,
            "Too Many Indices In Vertex Array!"sv);

        enable();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO.get());
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, m_EBSize,
            static_cast<GLsizeiptr>(std::ranges::size(indices) *
                sizeof(unsigned int)),
            std::ranges::data(indices));

        disable();

        m_EBSize += std::ranges::size(indices) * sizeof(unsigned int);
    }

    inline void VertexArray::enable() const noexcept
    {
        glBindVertexArray(m_VAO.get());
    }

    inline void VertexArray::disable() const noexcept
    {
        glBindVertexArray(0U);
    }

    [[nodiscard]] inline const std::vector<int>&
        VertexArray::getAttribs() const noexcept
    {
        return *m_Attribs.get();
    }

    [[nodiscard]] inline std::size_t
        VertexArray::getIndexCount() const noexcept
    {
        return static_cast<std::size_t>(m_EBSize / sizeof(unsigned int));
    }

    [[nodiscard]] inline unsigned int VertexArray::genVA() noexcept
    {
        unsigned int va = 0;
        glGenVertexArrays(1, &va);
        return va;
    }

    [[nodiscard]] inline unsigned int VertexArray::genBuf() noexcept
    {
        unsigned int vb = 0;
        glGenBuffers(1, &vb);
        return vb;
    }

    inline void VertexArray::delVA(unsigned int va) noexcept
    {
        glDeleteVertexArrays(1, &va);
    }

    inline void VertexArray::delBuf(unsigned int vb) noexcept
    {
        glDeleteBuffers(1, &vb);
    }
}

#endif // PULSAR_DETAILS_VERTEXARRAYIMPL_IPP
