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
            static auto tex2 =
                pul::Texture("Resources/Textures/Test.png");
            s_Face.setTexture(tex);
            s_Face2.setTexture(tex);
            s_Cat.setTexture(tex2);
            s_Cat.setRect(eqx::Rectangle<float>(0.0f, 0.0f, 100.0f, 100.0f));
            return true;
        });

    s_Face.setRect(eqx::Rectangle<float>(
        static_cast<float>(pul::Mouse::getPosition().x),
        static_cast<float>(pul::Mouse::getPosition().y),
        100.0f,
        100.0f));
    s_Face2.setRect(eqx::Rectangle<float>(
        static_cast<float>(pul::Mouse::getPosition().x - 100.0),
        static_cast<float>(pul::Mouse::getPosition().y),
        100.0f,
        100.0f));
}

inline void QuadTest::render() noexcept
{
    pul::Renderer::draw(s_Face);
    pul::Renderer::draw(s_Face2);
    pul::Renderer::draw(s_Cat);
}

#endif // PROVINGGROUNDS_DETAILS_QUADTESTIMPL_IPP
