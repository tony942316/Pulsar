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

#ifndef PULSAR_SHADERDECL_HPP
#define PULSAR_SHADERDECL_HPP

#include "Dependencies.hpp"

namespace pul
{
    class Shader
    {
    public:
        explicit constexpr Shader() noexcept;

        inline void init(std::string_view vertexFilePath,
            std::string_view fragmentFilePath) noexcept;

        inline void enable() const noexcept;
        inline void disable() const noexcept;

    private:
        static inline unsigned int genShader() noexcept;
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

#endif // PULSAR_SHADERDECL_HPP
