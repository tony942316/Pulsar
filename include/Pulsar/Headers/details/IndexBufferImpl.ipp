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

#ifndef PULSAR_INDEXBUFFERIMPL_IPP
#define PULSAR_INDEXBUFFERIMPL_IPP

#include "IndexBufferDecl.hpp"

namespace pul
{

    constexpr IndexBuffer::IndexBuffer() noexcept
        :
        m_EBO(),
        m_Indices()
    {
    }

    template <typename T>
        requires eqx::ConstCollection<T>
    inline IndexBuffer::IndexBuffer(const T& indices) noexcept
        :
        IndexBuffer()
    {
        init(indices);
    }

    template <typename T>
        requires eqx::ConstCollection<T>
    inline void IndexBuffer::init(const T& indices) noexcept
    {
        if (m_EBO.get() != 0U)
        {
            free();
        }

        m_EBO.init(delEB, genEB);
        m_Indices.init(delIndices, genIndices);

        m_Indices.get()->reserve(std::ranges::size(indices));
        std::ranges::copy(indices, std::back_inserter(*m_Indices.get()));

        enable();

        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(sizeof(unsigned int) * std::ranges::size(*m_Indices.get())),
            m_Indices.get()->data(),
            GL_STATIC_DRAW);

        disable();
    }

    inline void IndexBuffer::enable() const noexcept
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO.get());
    }

    inline void IndexBuffer::disable() const noexcept
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    inline void IndexBuffer::free() noexcept
    {
        m_EBO.free();
        m_Indices.free();
    }

    [[nodiscard]] inline const std::vector<unsigned int>&
        IndexBuffer::getIndices() const noexcept
    {
        return *m_Indices.get();
    }

    [[nodiscard]] inline std::size_t IndexBuffer::getCount() const noexcept
    {
        return std::ranges::size(*m_Indices.get());
    }

    [[nodiscard]] inline unsigned int IndexBuffer::genEB() noexcept
    {
        unsigned int eb;
        glGenBuffers(1, &eb);
        return eb;
    }

    inline void IndexBuffer::delEB(unsigned int eb) noexcept
    {
        glDeleteBuffers(1, &eb);
    }

    [[nodiscard]] inline std::vector<unsigned int>*
        IndexBuffer::genIndices() noexcept
    {
        return new std::vector<unsigned int>();
    }

    inline void IndexBuffer::delIndices(
        std::vector<unsigned int>* indices) noexcept
    {
        delete indices;
    }
}

#endif // PULSAR_INDEXBUFFERIMPL_IPP
