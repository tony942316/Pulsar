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

inline void Ui::update() noexcept
{
    [[maybe_unused]] static auto init = std::invoke(
        []()
        {
            s_Buttons.setUniforms(1200.0f, 800.0f);
            s_Buttons.setRect(0ULL,
                eqx::Rectangle<float>(0.0f, 0.0f, 100.0f, 75.0f));

            return true;
        });
}

inline void Ui::render() noexcept
{
    pul::Renderer::draw(s_Buttons);
}

#endif // PROVINGGROUNDS_DETAILS_UIIMPL_IPP
