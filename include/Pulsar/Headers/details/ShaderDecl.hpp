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

#ifndef PULSAR_DETAILS_SHADERDECL_HPP
#define PULSAR_DETAILS_SHADERDECL_HPP

#include "Dependencies.hpp"

namespace pul
{
    class Shader
    {
    public:
        explicit constexpr Shader() noexcept;
        explicit inline Shader(std::string_view vertexFilePath,
            std::string_view fragmentFilePath) noexcept;

        inline void init(std::string_view vertexFilePath,
            std::string_view fragmentFilePath) noexcept;

        inline void enable() const noexcept;
        inline void disable() const noexcept;

        inline void free() noexcept;

        inline void setInt(std::string_view name, int value) const noexcept;
        template <typename T>
            requires requires(const T& values)
            {
                std::ranges::size(values);
                std::ranges::data(values);
            }
        inline void setInts(std::string_view name,
            const T& values) const noexcept;
        inline void setFloat(std::string_view name, float value) const noexcept;
        inline void setVec4(std::string_view name,
            const glm::vec4& value) const noexcept;
        inline void setMat4(std::string_view name,
            const glm::mat4& value) const noexcept;

    private:
        [[nodiscard]] static inline unsigned int genShader() noexcept;
        static inline void delShader(unsigned int shader) noexcept;

        using ShaderID =
            eqx::UniqueResource<unsigned int, decltype(&delShader)>;

        [[nodiscard]] static inline std::string parseShader(
            std::string_view filePath) noexcept;
        [[nodiscard]] static inline unsigned int compileShader(
            unsigned int type, const char* src) noexcept;
        [[nodiscard]] static inline ShaderID linkShader(
            unsigned int vertexShader, unsigned int fragmentShader) noexcept;

        ShaderID m_Shader;
    };
}

#endif // PULSAR_DETAILS_SHADERDECL_HPP
