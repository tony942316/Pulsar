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

#ifndef PULSAR_DETAILS_QUADIMPL_IPP
#define PULSAR_DETAILS_QUADIMPL_IPP

#include "QuadDecl.hpp"

namespace pul
{
    constexpr Quad::Quad() noexcept
        :
        m_Mixture(0.0f),
        m_Color(1.0f),
        m_DrawBox(),
        m_Model(1.0f),
        m_Texture()
    {
    }

    inline Quad::Quad(const eqx::Rectangle<float>& drawBox) noexcept
        :
        Quad()
    {
        setDrawBox(drawBox);
    }

    inline void Quad::setUniforms() const noexcept
    {
        setUniforms(m_Model, 0U, m_Mixture, m_Color);
    }

    inline void Quad::setMixture(float mixture) noexcept
    {
        m_Mixture = mixture;
    }

    inline void Quad::setColor(const glm::vec4 color) noexcept
    {
        m_Color = color;
    }

    inline void Quad::setDrawBox(
        const eqx::Rectangle<float>& drawBox) noexcept
    {
        m_DrawBox = drawBox;
        m_Model = glm::translate(
            glm::mat4(1.0f),
            glm::vec3(
                m_DrawBox.x + m_DrawBox.w / 2.0f,
                m_DrawBox.y + m_DrawBox.h / 2.0f,
                0.0f));
        m_Model = glm::scale(m_Model, glm::vec3(m_DrawBox.w,
            m_DrawBox.h, 1.0f));
    }

    inline void Quad::setTexture(std::string_view filePath) noexcept
    {
        m_Texture.init(filePath);
    }

    [[nodiscard]] constexpr float Quad::getMixture() const noexcept
    {
        return m_Mixture;
    }

    [[nodiscard]] constexpr const glm::vec4& Quad::getColor() const noexcept
    {
        return m_Color;
    }

    [[nodiscard]] constexpr const eqx::Rectangle<float>&
        Quad::getDrawBox() const noexcept
    {
        return m_DrawBox;
    }

    [[nodiscard]] constexpr const Texture& Quad::getTexture() const noexcept
    {
        return m_Texture;
    }

    [[nodiscard]] constexpr const glm::mat4&
        Quad::getModel() const noexcept
    {
        return m_Model;
    }

    inline void Quad::init(float width, float height) noexcept
    {
        stbi_set_flip_vertically_on_load(true);
        s_Shader = Shader("Resources/Shaders/QuadVertex.glsl"sv,
            "Resources/Shaders/QuadFragment.glsl"sv);
        glm::mat4 projection = glm::ortho(0.0f, width, 0.0f, height,
            -1.0f, 1.0f);
        s_Shader.setMat4("u_Projection", projection);
        s_Shader.setMat4("u_View", glm::mat4(1.0f));

        s_Shader.setMat4("u_Model", glm::mat4(1.0f));
        s_Shader.setFloat("u_Mixture", 0.0f);
        s_Shader.setVec4("u_Color", glm::vec4());
        s_Shader.setInt("u_Texture0", 0);

        s_VertexBuffer = VertexBuffer(c_SquareVertices, c_SquareAttribs);
        s_IndexBuffer = IndexBuffer(c_SquareIndices);
    }

    inline void Quad::free() noexcept
    {
        s_Shader = Shader();
        s_VertexBuffer = VertexBuffer();
        s_IndexBuffer = IndexBuffer();
    }

    inline void Quad::setUniforms(const glm::mat4& model,
        unsigned int texture,
        float mixture,
        const glm::vec4& color) noexcept
    {
        s_Shader.setMat4("u_Model", model);
        s_Shader.setInt("u_Texture0", static_cast<int>(texture));
        s_Shader.setFloat("u_Mixture", mixture);
        s_Shader.setVec4("u_Color", color);
    }

    inline void Quad::cleanUniforms() noexcept
    {
        setUniforms(glm::mat4(1.0f), 0U, 0.0f, glm::vec4());
    }

    [[nodiscard]] inline const Shader& Quad::getShader() noexcept
    {
        return s_Shader;
    }

    [[nodiscard]] inline const VertexBuffer& Quad::getVertexBuffer() noexcept
    {
        return s_VertexBuffer;
    }

    [[nodiscard]] inline const IndexBuffer& Quad::getIndexBuffer() noexcept
    {
        return s_IndexBuffer;
    }
}

#endif // PULSAR_DETAILS_QUADIMPL_IPP
