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

#ifndef PULSAR_SHADERIMPL_IPP
#define PULSAR_SHADERIMPL_IPP

#include "ShaderDecl.hpp"

namespace pul
{
    constexpr Shader::Shader() noexcept
        :
        m_Shader()
    {
    }

    inline Shader::Shader(std::string_view vertexFilePath,
        std::string_view fragmentFilePath) noexcept
    {
        init(vertexFilePath, fragmentFilePath);
    }

    inline void Shader::init(std::string_view vertexFilePath,
        std::string_view fragmentFilePath) noexcept
    {
        if (m_Shader.get() != 0U)
        {
            m_Shader.free();
        }

        auto vertexStr = parseShader(vertexFilePath);
        auto vertexSrc = vertexStr.c_str();
        auto vertexShader = compileShader(GL_VERTEX_SHADER, vertexSrc);

        auto fragmentStr = parseShader(fragmentFilePath);
        auto fragmentSrc = fragmentStr.c_str();
        auto fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);

        m_Shader = linkShader(vertexShader, fragmentShader);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    inline void Shader::enable() const noexcept
    {
        glUseProgram(m_Shader.get());
    }

    inline void Shader::disable() const noexcept
    {
        glUseProgram(0U);
    }

    inline void Shader::free() noexcept
    {
        m_Shader.free();
    }

    inline void Shader::setInt(std::string_view name, int value) const noexcept
    {
        enable();
        glUniform1i(glGetUniformLocation(m_Shader.get(), name.data()), value);
        disable();
    }

    inline void Shader::setFloat(std::string_view name,
        float value) const noexcept
    {
        enable();
        glUniform1f(glGetUniformLocation(m_Shader.get(), name.data()), value);
        disable();
    }

    inline void Shader::setVec4(std::string_view name,
        const glm::vec4& value) const noexcept
    {
        enable();
        glUniform4fv(glGetUniformLocation(m_Shader.get(), name.data()),
            1, glm::value_ptr(value));
        disable();
    }

    inline void Shader::setMat4(std::string_view name,
        const glm::mat4& value) const noexcept
    {
        enable();
        glUniformMatrix4fv(glGetUniformLocation(m_Shader.get(), name.data()),
            1, false, glm::value_ptr(value));
        disable();
    }

    [[nodiscard]] inline unsigned int Shader::genShader() noexcept
    {
        return glCreateProgram();
    }

    inline void Shader::delShader(unsigned int shader) noexcept
    {
        glDeleteProgram(shader);
    }

    [[nodiscard]] inline std::string Shader::parseShader(
        std::string_view filePath) noexcept
    {
        auto file = std::ifstream(filePath.data(), std::ios::in);
        return (std::stringstream() << file.rdbuf()).str();
    }

    [[nodiscard]] inline unsigned int Shader::compileShader(
        unsigned int type, const char* src) noexcept
    {
        auto success = 0;
        char infoLog[512];
        auto shader = glCreateShader(type);
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        eqx::runtimeAssert(success, "Shader Compilation Error: "s + infoLog);
        return shader;
    }

    [[nodiscard]] inline Shader::ShaderID Shader::linkShader(
        unsigned int vertexShader, unsigned int fragmentShader) noexcept
    {
        auto success = 0;
        char infoLog[512];
        auto shaderProgram = ShaderID();
        shaderProgram.init(delShader, genShader);
        glAttachShader(shaderProgram.get(), vertexShader);
        glAttachShader(shaderProgram.get(), fragmentShader);
        glLinkProgram(shaderProgram.get());
        glGetProgramiv(shaderProgram.get(), GL_LINK_STATUS, &success);
        glGetProgramInfoLog(shaderProgram.get(), 512, nullptr, infoLog);
        eqx::runtimeAssert(success, "Shader Link Error: "s + infoLog);
        return shaderProgram;
    }
}

#endif // PULSAR_SHADERIMPL_IPP
