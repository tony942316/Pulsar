/*
 * Copyright (C) 2024 Anthony H. Grasso
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

#ifndef PULSAR_DETAILS_EMBSHADERSIMPL_IPP
#define PULSAR_DETAILS_EMBSHADERSIMPL_IPP

#include "EmbShadersDecl.hpp"

namespace pul
{
    inline void EmbShaders::boot(float w, float h) noexcept
    {
        makeTxQuadShader(w, h);
        makeFontShader(w, h);
        makeCQuadShader(w, h);
    }

    [[nodiscard]] inline Shader& EmbShaders::TxQuadShader() noexcept
    {
        return s_TxQuadShader;
    }

    [[nodiscard]] inline Shader& EmbShaders::FontShader() noexcept
    {
        return s_FontShader;
    }

    [[nodiscard]] inline Shader& EmbShaders::CQuadShader() noexcept
    {
        return s_CQuadShader;
    }

    inline void EmbShaders::makeTxQuadShader(float w, float h) noexcept
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

        s_TxQuadShader.init(pul::ShaderGenerator(vc, fc));

        auto projection =
            glm::ortho(0.0f, w, 0.0f, h, -1.0f, 1.0f);
        s_TxQuadShader.setMat4("u_View", glm::mat4(1.0f));
        s_TxQuadShader.setMat4("u_Projection", projection);

        auto textures = std::array<int, 32>();
        std::ranges::copy(std::views::iota(0, 32), textures.begin());
        s_TxQuadShader.setInts("u_Textures", textures);
    }

    inline void EmbShaders::makeFontShader(float w, float h) noexcept
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
            "o_FragmentColor = vec4(0.8f, 0.0f, 0.2f,"sv
                "texture(u_Textures[int(p_TexIndex)], p_TexCoord).r);\n"sv;

        s_FontShader.init(pul::ShaderGenerator(vc, fc));

        auto projection =
            glm::ortho(0.0f, w, 0.0f, h, -1.0f, 1.0f);
        s_FontShader.setMat4("u_View", glm::mat4(1.0f));
        s_FontShader.setMat4("u_Projection", projection);

        auto textures = std::array<int, 32>();
        std::ranges::copy(std::views::iota(0, 32), textures.begin());
        s_FontShader.setInts("u_Textures", textures);
    }

    inline void EmbShaders::makeCQuadShader(float w, float h) noexcept
    {
        auto vc = pul::ShaderGenerator::ShaderConfig();
        auto fc = pul::ShaderGenerator::ShaderConfig();

        vc.inputs.emplace_back(
            "layout (location = 0) in vec2 i_Pos;\n"sv);
        vc.inputs.emplace_back(
            "layout (location = 1) in vec3 i_Color;\n"sv);

        vc.uniforms.emplace_back("uniform mat4 u_View;\n"sv);
        vc.uniforms.emplace_back("uniform mat4 u_Projection;\n"sv);

        vc.outputs.emplace_back("out vec3 p_Color;\n"sv);

        vc.code =
            "p_Color = i_Color;\n"sv
            "gl_Position = "sv
                "u_Projection * u_View * vec4(i_Pos, 0.0f, 1.0f);\n"sv;

        fc.inputs.emplace_back("in vec3 p_Color;\n"sv);

        fc.outputs.emplace_back("out vec4 o_FragmentColor;\n"sv);

        fc.code =
            "o_FragmentColor = vec4(p_Color, 1.0f);\n"sv;

        s_CQuadShader.init(pul::ShaderGenerator(vc, fc));

        auto projection =
            glm::ortho(0.0f, w, 0.0f, h, -1.0f, 1.0f);
        s_CQuadShader.setMat4("u_View", glm::mat4(1.0f));
        s_CQuadShader.setMat4("u_Projection", projection);
    }
}

#endif // PULSAR_DETAILS_EMBSHADERSIMPL_IPP
