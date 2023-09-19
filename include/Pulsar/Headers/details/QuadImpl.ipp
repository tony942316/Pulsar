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

namespace pul::shader
{
    [[nodiscard]] inline const Shader& getQuad() noexcept
    {
        static auto shader = makeQuad();
        return shader;
    }

    [[nodiscard]] inline Shader makeQuad() noexcept
    {
        auto vc = pul::ShaderGenerator::ShaderConfig();
        auto fc = pul::ShaderGenerator::ShaderConfig();

        vc.inputs.emplace_back(
            "layout (location = 0) in vec2 i_Pos;\n"sv);
        vc.inputs.emplace_back(
            "layout (location = 1) in vec2 i_TexCoord;\n"sv);
        vc.inputs.emplace_back(
            "layout (location = 2) in float i_TexIndex;\n"sv);

        vc.uniforms.emplace_back("uniform mat4 u_View;\n"sv);
        vc.uniforms.emplace_back("uniform mat4 u_Projection;\n"sv);

        vc.outputs.emplace_back("out vec2 p_TexCoord;\n"sv);
        vc.outputs.emplace_back("out float p_TexIndex;\n"sv);

        vc.code =
            "p_TexCoord = i_TexCoord;\n"sv
            "p_TexIndex = i_TexIndex;\n"sv
            "gl_Position = "sv
                "u_Projection * u_View * vec4(i_Pos, 0.0f, 1.0f);\n"sv;

        fc.inputs.emplace_back("in vec2 p_TexCoord;\n"sv);
        fc.inputs.emplace_back("in float p_TexIndex;\n"sv);

        fc.uniforms.emplace_back("uniform sampler2D u_Textures[32];\n"sv);

        fc.outputs.emplace_back("out vec4 o_FragmentColor;\n"sv);

        fc.code =
            "o_FragmentColor = "sv
                "texture(u_Textures[int(p_TexIndex)], p_TexCoord);\n"sv;

        return Shader(pul::ShaderGenerator(vc, fc));
    }
}

namespace pul::batch
{
    constexpr Quad::Quad() noexcept
        :
        m_Data(),
        m_Textures()
    {
        auto is = 0_size;
        auto it = 0_size;
        auto iTex = 0_size;
        auto off = 0_size;
        for (auto index = 0_size; index < 32; index++)
        {
            is = c_IndexS + (index * c_QStride);
            it = c_IndexT + (index * c_QStride);
            iTex = c_IndexTex + (index * c_QStride);

            off = 0_size;
            m_Data.at(is + off) = 0.0f;
            m_Data.at(it + off) = 0.0f;
            m_Data.at(iTex + off) = static_cast<float>(index);

            off += c_VStride;
            m_Data.at(is + off) = 1.0f;
            m_Data.at(it + off) = 0.0f;
            m_Data.at(iTex + off) = static_cast<float>(index);

            off += c_VStride;
            m_Data.at(is + off) = 1.0f;
            m_Data.at(it + off) = 1.0f;
            m_Data.at(iTex + off) = static_cast<float>(index);

            off += c_VStride;
            m_Data.at(is + off) = 0.0f;
            m_Data.at(it + off) = 1.0f;
            m_Data.at(iTex + off) = static_cast<float>(index);
        }
    }

    constexpr void Quad::setRect(std::size_t index,
        eqx::Rectangle<float> rect) noexcept
    {
        eqx::runtimeAssert(index < 32, "Batch Overflow"sv);

        auto ix = c_IndexX + (index * c_QStride);
        auto iy = c_IndexY + (index * c_QStride);
        auto off = 0_size;

        off = 0_size;
        m_Data.at(ix + off) = rect.getTopLeftPoint().x;
        m_Data.at(iy + off) = 800.0f - rect.getTopLeftPoint().y;

        off += c_VStride;
        m_Data.at(ix + off) = rect.getTopRightPoint().x;
        m_Data.at(iy + off) = 800.0f - rect.getTopRightPoint().y;

        off += c_VStride;
        m_Data.at(ix + off) = rect.getBottomRightPoint().x;
        m_Data.at(iy + off) = 800.0f - rect.getBottomRightPoint().y;

        off += c_VStride;
        m_Data.at(ix + off) = rect.getBottomLeftPoint().x;
        m_Data.at(iy + off) = 800.0f - rect.getBottomLeftPoint().y;
    }

    constexpr void Quad::setTexture(std::size_t index,
        const Texture& texture) noexcept
    {
        m_Textures.at(index) = &texture;
    }

    inline void Quad::enableTextures() const noexcept
    {
        for (auto index = 0_size; index < 32_size; index++)
        {
            Texture::enableTextureSlot(static_cast<unsigned int>(index));
            if (m_Textures.at(index) != nullptr)
            {
                m_Textures.at(index)->enable();
            }
        }
    }

    constexpr const std::array<float, 640_size>& Quad::getData() const noexcept
    {
        return m_Data;
    }

    inline void Quad::setUniforms(float w, float h) noexcept
    {
        auto projection =
            glm::ortho(0.0f, w, 0.0f, h, -1.0f, 1.0f);
        pul::shader::getQuad().setMat4("u_View", glm::mat4(1.0f));
        pul::shader::getQuad().setMat4("u_Projection", projection);

        auto textures = std::array<int, 32>();
        std::ranges::copy(std::views::iota(0, 32), textures.begin());
        pul::shader::getQuad().setInts("u_Textures", textures);
    }

    consteval const std::array<unsigned int, 192_size>&
        Quad::getIndices() noexcept
    {
        return c_Indices;
    }

    consteval const std::array<int, 3_size>& Quad::getAttribs() noexcept
    {
        return c_Attribs;
    }
}

#endif // PULSAR_DETAILS_QUADIMPL_IPP
