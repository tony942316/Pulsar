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

#ifndef PROVINGGROUNDS_DETAILS_TEXTTESTIMPL_IPP
#define PROVINGGROUNDS_DETAILS_TEXTTESTIMPL_IPP

#include "TextTestDecl.hpp"

inline void TextTest::update() noexcept
{
    [[maybe_unused]] static auto init = std::invoke(
        []()
        {
            s_Font.init("Resources/Fonts/Poppins/Poppins-Regular.ttf");
            s_LowerCase = s_Font.getText("abcdefghijklmnopqrstuvwxyz",
                eqx::Point<float>(100.0f, 100.0f));
            s_UpperCase = s_Font.getText("ABCDEFGHIJKLMNOPQRSTUVWXYZ",
                eqx::Point<float>(100.0f, 150.0f));
            s_Phrase = s_Font.getText("Like Wow Ok!",
                eqx::Point<float>(100.0f, 200.0f));
            return true;
        });
}

inline void TextTest::render() noexcept
{
    pul::Renderer::draw(s_LowerCase);
    pul::Renderer::draw(s_UpperCase);
    pul::Renderer::drawText(s_Phrase);
}

#endif // PROVINGGROUNDS_DETAILS_TEXTTESTIMPL_IPP
