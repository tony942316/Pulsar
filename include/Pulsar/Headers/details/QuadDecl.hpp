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

#ifndef PULSAR_DETAILS_QUADDECL_HPP
#define PULSAR_DETAILS_QUADDECL_HPP

#include "Dependencies.hpp"

#include "../Shader.hpp"
#include "../VertexBuffer.hpp"
#include "../IndexBuffer.hpp"
#include "../Texture.hpp"

namespace pul
{
    class Quad
    {
    public:
        explicit constexpr Quad() noexcept;
        explicit inline Quad(const eqx::Rectangle<float>& drawBox) noexcept;

        inline void setUniforms() const noexcept;

        inline void setMixture(float mixture) noexcept;
        inline void setColor(const glm::vec4 color) noexcept;
        inline void setDrawBox(const eqx::Rectangle<float>& drawBox) noexcept;
        inline void setTexture(std::string_view filePath) noexcept;

        [[nodiscard]] constexpr float getMixture() const noexcept;
        [[nodiscard]] constexpr const glm::vec4& getColor() const noexcept;
        [[nodiscard]] constexpr const eqx::Rectangle<float>&
            getDrawBox() const noexcept;
        [[nodiscard]] constexpr const Texture& getTexture() const noexcept;
        [[nodiscard]] constexpr const glm::mat4& getModel() const noexcept;

        static inline void init(float width, float height) noexcept;
        static inline void free() noexcept;

        static inline void setUniforms(const glm::mat4& model,
            unsigned int texture,
            float mixture,
            const glm::vec4& color) noexcept;
        static inline void cleanUniforms() noexcept;

        [[nodiscard]] static inline const Shader& getShader() noexcept;
        [[nodiscard]] static inline const VertexBuffer&
            getVertexBuffer() noexcept;
        [[nodiscard]] static inline const IndexBuffer&
            getIndexBuffer() noexcept;

    private:
        float m_Mixture;
        glm::vec4 m_Color;

        eqx::Rectangle<float> m_DrawBox;
        glm::mat4 m_Model;

        Texture m_Texture;

        constinit static inline auto s_Shader = Shader();
        constinit static inline auto s_VertexBuffer = VertexBuffer();
        constinit static inline auto s_IndexBuffer = IndexBuffer();

        static constexpr auto c_SquareVertices = std::array<float, 16_size>({
            -0.5f,  0.5f, 0.0f, 1.0f,
             0.5f,  0.5f, 1.0f, 1.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f});

        static constexpr auto c_SquareIndices =
            std::array<unsigned int, 6_size>({
                0, 1, 3,
                1, 2, 3});

        static constexpr auto c_SquareAttribs = std::array<int, 2_size>({
            2, 2 });
    };
}

#endif // PULSAR_DETAILS_QUADDECL_HPP
