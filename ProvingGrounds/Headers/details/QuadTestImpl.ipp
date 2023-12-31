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

#ifndef PROVINGGROUNDS_DETAILS_QUADTESTIMPL_IPP
#define PROVINGGROUNDS_DETAILS_QUADTESTIMPL_IPP

#include "QuadTestDecl.hpp"

inline void QuadTest::update() noexcept
{
    [[maybe_unused]] static auto init = std::invoke(
        []()
        {
            static auto tex =
                pul::Texture("Resources/Textures/AwesomeFace.png");
            s_Batch.setTexture(0, tex);
            return true;
        });

    s_Batch.setRect(0, eqx::Rectangle<float>(
        static_cast<float>(pul::Mouse::getPosition().x),
        static_cast<float>(pul::Mouse::getPosition().y),
        100.0f,
        100.0f));
}

inline void QuadTest::render() noexcept
{
    pul::Renderer::draw(s_Batch);
}

#endif // PROVINGGROUNDS_DETAILS_QUADTESTIMPL_IPP
