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

#ifndef PULSAR_DETAILS_FONTIMPL_IPP
#define PULSAR_DETAILS_FONTIMPL_IPP

#include "FontDecl.hpp"

namespace pul
{
    constexpr Font::Font() noexcept
        :
        m_Chars()
    {
    }

    inline Font::Font(std::string_view filePath) noexcept
        :
        Font()
    {
        init(filePath);
    }

    inline void Font::init(std::string_view filePath) noexcept
    {
        [[maybe_unused]] static auto initFT = initFreeType();

        m_Chars.init();
        m_Chars.get()->resize(128_size);

        auto face = FT_Face();
        eqx::runtimeAssert(FT_New_Face(s_FT, filePath.data(), 0, &face) == 0,
            "Freetype Face Load Failure!"sv);
        eqx::runtimeAssert(FT_Set_Pixel_Sizes(face, 0, 48) == 0,
            "Freetype Set Pixel Size Failure!"sv);

        std::ranges::for_each(std::views::iota(0, 128),
            [&](int i)
            {
                eqx::runtimeAssert(FT_Load_Char(face,
                    static_cast<unsigned char>(i), FT_LOAD_RENDER) == 0,
                    "Failed To Load Char: "s + std::to_string(i));
                auto& ch = m_Chars.get()->at(static_cast<std::size_t>(i));
                auto& gly = face->glyph;
                ch.tex.init(gly);
                ch.size = glm::ivec2(gly->bitmap.width, gly->bitmap.rows);
                ch.bear = glm::ivec2(gly->bitmap_left, gly->bitmap_top);
                ch.adv = static_cast<unsigned int>(gly->advance.x);
            });

        eqx::runtimeAssert(FT_Done_Face(face) == 0,
            "Freetype Face Delete Error!"sv);
    }

    [[nodiscard]] inline std::vector<TxQuad> Font::getText(
        std::string_view text, const eqx::Point<float>& loc) noexcept
    {
        auto result = std::vector<TxQuad>();
        auto x = loc.x;

        auto index = 0_size;
        std::ranges::for_each(text,
            [&](char c)
            {
                auto& ch = m_Chars.get()->at(static_cast<std::size_t>(c));

                result.emplace_back(eqx::Rectangle<float>(
                    x + static_cast<float>(ch.bear.x),
                    loc.y - static_cast<float>(ch.bear.y),
                    static_cast<float>(ch.size.x),
                    static_cast<float>(ch.size.y)), ch.tex);

                x += static_cast<float>(ch.adv >> 6);
                index++;
            });

        return result;
    }

    inline void Font::boot() noexcept
    {
        initFreeType();
    }

    inline bool Font::initFreeType() noexcept
    {
        eqx::runtimeAssert(FT_Init_FreeType(&s_FT) == 0,
            "Freetype Init Failure!"sv);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        return true;
    }
}

#endif // PULSAR_DETAILS_FONTIMPL_IPP
