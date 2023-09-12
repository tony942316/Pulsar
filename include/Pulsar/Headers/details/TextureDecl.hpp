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

#ifndef PULSAR_DETAILS_TEXTUREDECL_HPP
#define PULSAR_DETAILS_TEXTUREDECL_HPP

#include "Dependencies.hpp"

namespace pul
{
    class Texture
    {
    public:
        explicit constexpr Texture() noexcept;
        explicit inline Texture(std::string_view filePath) noexcept;
        explicit inline Texture(FT_GlyphSlot glyph) noexcept;

        inline void init(std::string_view filePath) noexcept;
        inline void init(FT_GlyphSlot glyph) noexcept;
        inline void free() noexcept;

        inline void enable() const noexcept;
        inline void disable() const noexcept;

        static inline void enableTextureSlot(unsigned int i) noexcept;

    private:
        [[nodiscard]] static inline unsigned int genTex() noexcept;
        static inline void delTex(unsigned int tex) noexcept;

        using Tex = eqx::UniqueResource<unsigned int, decltype(&delTex)>;

        Tex m_Texture;
        eqx::UniquePointer<std::string> m_FilePath;
    };
}

#endif // PULSAR_DETAILS_TEXTUREDECL_HPP
