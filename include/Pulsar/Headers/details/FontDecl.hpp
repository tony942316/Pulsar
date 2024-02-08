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

#ifndef PULSAR_DETAILS_FONTDECL_HPP
#define PULSAR_DETAILS_FONTDECL_HPP

#include "Dependencies.hpp"

#include "../Texture.hpp"
#include "../Shader.hpp"
#include "../TxQuad.hpp"

namespace pul
{
    class Font
    {
    public:
        explicit constexpr Font() noexcept;
        explicit inline Font(std::string_view filePath) noexcept;

        inline void init(std::string_view filePath) noexcept;

        [[nodiscard]] inline std::vector<TxQuad> getText(
            std::string_view text,
            const eqx::Point<float>& loc = eqx::Point<float>()) noexcept;

        static inline void boot() noexcept;

    private:
        struct Character
        {
            Texture tex;
            glm::ivec2 size;
            glm::ivec2 bear;
            unsigned int adv;
        };

        static inline bool initFreeType() noexcept;

        eqx::UniquePointer<std::vector<Character>> m_Chars;

        constinit static inline auto s_FT = FT_Library();
    };
}

#endif // PULSAR_DETAILS_FONTDECL_HPP
