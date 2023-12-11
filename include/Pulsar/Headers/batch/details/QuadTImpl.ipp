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

#ifndef PULSAR_BATCH_DETAILS_QUADTIMPL_IPP
#define PULSAR_BATCH_DETAILS_QUADTIMPL_IPP

#include "QuadTDecl.hpp"

namespace pul::batch::shader
{
    [[nodiscard]] inline const Shader& getQuadT() noexcept
    {
        static auto shader = makeQuadT();
        return shader;
    }

    [[nodiscard]] inline Shader makeQuadT() noexcept
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
    constexpr QuadT::QuadT() noexcept
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

    constexpr void QuadT::setLoc(std::size_t index,
        const eqx::Point<float>& loc) noexcept
    {
        eqx::runtimeAssert(index < 32, "Batch Overflow!"sv);

        auto rect = getRect(index);
        rect.setLocation(loc);
        setRect(index, rect);
    }

    constexpr void QuadT::setRect(std::size_t index,
        const eqx::Rectangle<float>& rect) noexcept
    {
        eqx::runtimeAssert(index < 32, "Batch Overflow!"sv);

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

    constexpr void QuadT::setTexture(std::size_t index,
        const Texture& texture) noexcept
    {
        m_Textures.at(index) = &texture;
    }

    inline void QuadT::enableTextures() const noexcept
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

    [[nodiscard]] constexpr const std::array<float, 640_size>&
        QuadT::getData() const noexcept
    {
        return m_Data;
    }

    [[nodiscard]] constexpr eqx::Point<float>
        QuadT::getLoc(std::size_t index) const noexcept
    {
        auto ix = c_IndexX + (index * c_QStride);
        auto iy = c_IndexY + (index * c_QStride);

        return eqx::Point<float>(m_Data.at(ix), m_Data.at(iy));
    }

    [[nodiscard]] constexpr eqx::Rectangle<float>
        QuadT::getRect(std::size_t index) const noexcept
    {
        eqx::runtimeAssert(index < 32, "Batch Overflow!"sv);

        auto ix = c_IndexX + (index * c_QStride);
        auto iy = c_IndexY + (index * c_QStride);
        auto tl = eqx::Point<float>();
        auto br = eqx::Point<float>();
        auto off = 0_size;

        off = 0_size;
        tl = eqx::Point<float>(m_Data.at(ix + off), m_Data.at(iy + off));
        off += 2 * c_VStride;
        br = eqx::Point<float>(m_Data.at(ix + off), m_Data.at(iy + off));

        return eqx::Rectangle<float>(tl, br);
    }

    [[nodiscard]] constexpr const Texture&
        QuadT::getTexture(std::size_t index) const noexcept
    {
        return *m_Textures.at(index);
    }

    inline void QuadT::setUniforms(float w, float h) noexcept
    {
        auto projection =
            glm::ortho(0.0f, w, 0.0f, h, -1.0f, 1.0f);
        pul::batch::shader::getQuadT().setMat4("u_View", glm::mat4(1.0f));
        pul::batch::shader::getQuadT().setMat4("u_Projection", projection);

        auto textures = std::array<int, 32>();
        std::ranges::copy(std::views::iota(0, 32), textures.begin());
        pul::batch::shader::getQuadT().setInts("u_Textures", textures);
    }

    [[nodiscard]] consteval const std::array<unsigned int, 192_size>&
        QuadT::getIndices() noexcept
    {
        return c_Indices;
    }

    [[nodiscard]] consteval const std::array<int, 3_size>&
        QuadT::getAttribs() noexcept
    {
        return c_Attribs;
    }
}

#endif // PULSAR_BATCH_DETAILS_QUADTIMPL_IPP
