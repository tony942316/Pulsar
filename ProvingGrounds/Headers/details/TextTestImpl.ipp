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
            static auto lc = s_Font.getText("abcdefghijklmnopqrstuvwxyz",
                eqx::Point<float>(100.0f, 100.0f));
            s_LowerCase = lc;
            static auto uc = s_Font.getText("ABCDEFGHIJKLMNOPQRSTUVWXYZ",
                eqx::Point<float>(100.0f, 150.0f));
            s_UpperCase = uc;
            static auto ph = s_Font.getText("Like Wow Ok!",
                eqx::Point<float>(100.0f, 200.0f));
            s_Phrase = ph;
            static auto trvl = s_Font.getText("Follows The Mouse!",
                eqx::Point<float>(0.0f, 0.0f));
            s_Traveler = trvl;
            static auto trvl2 = s_Font.getText("Follows The Mouse!",
                eqx::Point<float>(450.0f, 0.0f));
            s_Traveler2 = trvl2;
            return true;
        });

    std::ranges::for_each(s_Traveler, [](pul::TxQuad& quad)
        {
            quad.setLoc(eqx::Point<float>(
                quad.getLoc().x,
                static_cast<float>(pul::Mouse::getPosition().y)));
        });

    std::ranges::for_each(s_Traveler2, [](pul::TxQuad& quad)
        {
            quad.setLoc(eqx::Point<float>(
                quad.getLoc().x,
                static_cast<float>(pul::Mouse::getPosition().y)));
        });
}

inline void TextTest::render() noexcept
{
    pul::Renderer::drawText(s_Traveler);
    pul::Renderer::draw(s_LowerCase);
    pul::Renderer::draw(s_UpperCase);
    pul::Renderer::drawText(s_Phrase);
    pul::Renderer::drawText(s_Traveler2);
}

#endif // PROVINGGROUNDS_DETAILS_TEXTTESTIMPL_IPP
