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

#ifndef PROVINGGROUNDS_DETAILS_UIIMPL_IPP
#define PROVINGGROUNDS_DETAILS_UIIMPL_IPP

#include "UiDecl.hpp"

inline bool Ui::update() noexcept
{
    [[maybe_unused]] static auto init = std::invoke(
        []()
        {
            s_Button.setRect(eqx::Rectangle<float>(
                10.0f, 10.0f, 150.0f, 50.0f ));
            s_Button.setColor(pul::CQuad::color(0.8f, 0.0f, 0.2f));
            return true;
        });

    auto mloc = eqx::Point<float>(
        static_cast<float>(pul::Mouse::getPosition().x),
        static_cast<float>(pul::Mouse::getPosition().y));

    auto md = eqx::Point<float>(
        static_cast<float>(pul::Mouse::getLeftClickPosition().x),
        static_cast<float>(pul::Mouse::getLeftClickPosition().y));

    auto mu = eqx::Point<float>(
        static_cast<float>(pul::Mouse::getLeftReleasePosition().x),
        static_cast<float>(pul::Mouse::getLeftReleasePosition().y));

    if (eqx::intersect(s_Button.getRect(), mloc))
    {
        if (pul::Mouse::getLeftButton() == pul::Mouse::Button::Down)
        {
            s_Button.setColor(pul::CQuad::color(0.0f, 0.6f, 0.1f));
        }
        else
        {
            s_Button.setColor(pul::CQuad::color(0.0f, 0.8f, 0.2f));
        }
    }
    else
    {
        s_Button.setColor(pul::CQuad::color(0.8f, 0.0f, 0.2f));
    }


    if (eqx::intersect(s_Button.getRect(), md) &&
        eqx::intersect(s_Button.getRect(), mu))
    {
        return true;
    }
    else
    {
        return false;
    }
}

inline void Ui::render() noexcept
{
    pul::Renderer::draw(s_Button);
}

#endif // PROVINGGROUNDS_DETAILS_UIIMPL_IPP
