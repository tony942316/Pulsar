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

#ifndef PULSAR_DETAILS_EMBSHADERSDECL_HPP
#define PULSAR_DETAILS_EMBSHADERSDECL_HPP

#include "Dependencies.hpp"

#include "../ShaderGenerator.hpp"
#include "../Shader.hpp"

namespace pul
{
    class EmbShaders
    {
    public:
        EmbShaders() = delete;
        EmbShaders(const EmbShaders&) = delete;
        EmbShaders(EmbShaders&&) = delete;
        EmbShaders& operator= (const EmbShaders&) = delete;
        EmbShaders& operator= (EmbShaders&&) = delete;
        ~EmbShaders() = delete;

        static inline void boot(float w, float h) noexcept;

        [[nodiscard]] static inline Shader& TxQuadShader() noexcept;
        [[nodiscard]] static inline Shader& FontShader() noexcept;
        [[nodiscard]] static inline Shader& CQuadShader() noexcept;

    private:
        static inline void makeTxQuadShader(float w, float h) noexcept;
        static inline void makeFontShader(float w, float h) noexcept;
        static inline void makeCQuadShader(float w, float h) noexcept;

        constinit static inline auto s_TxQuadShader = pul::Shader();
        constinit static inline auto s_FontShader = pul::Shader();
        constinit static inline auto s_CQuadShader = pul::Shader();
    };
}

#endif // PULSAR_DETAILS_EMBSHADERSDECL_HPP
