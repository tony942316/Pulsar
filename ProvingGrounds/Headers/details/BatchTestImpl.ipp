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

#ifndef PROVINGGROUNDS_DETAILS_BATCHTESTIMPL_IPP
#define PROVINGGROUNDS_DETAILS_BATCHTESTIMPL_IPP

#include "BatchTestDecl.hpp"

inline void BatchTest::update([[maybe_unused]] float dt) noexcept
{
    [[maybe_unused]] static auto init = std::invoke(
        []()
        {
            static auto tex =
                pul::Texture("Resources/Textures/AwesomeFace.png");
            std::ranges::for_each(s_Batch1, [](pul::TxQuad& quad)
                {
                    quad.setTexture(tex);
                    quad.setRect(eqx::Rectangle<float>(
                        eqx::Random::randomNumber(0.0f, 1100.0f),
                        eqx::Random::randomNumber(0.0f, 700.0f),
                        100.0f, 100.0f));
                });
            std::ranges::for_each(s_Batch2, [](pul::TxQuad& quad)
                {
                    quad.setTexture(tex);
                    quad.setRect(eqx::Rectangle<float>(
                        eqx::Random::randomNumber(0.0f, 1150.0f),
                        eqx::Random::randomNumber(0.0f, 750.0f),
                        50.0f, 50.0f));
                });
            return true;
        });

    static auto timer = eqx::StopWatch();

    if (pul::Keyboard::isPressed(pul::Keyboard::Key::S))
    {
        if (timer.readSeconds() > 0.35)
        {
            shuffle();
            timer.start();
        }
    }
}

inline void BatchTest::render() noexcept
{
    pul::Renderer::draw(s_Batch1);
    pul::Renderer::draw(s_Batch2);
}

inline void BatchTest::shuffle() noexcept
{
    std::ranges::for_each(s_Batch1, [](pul::TxQuad& quad)
        {
            quad.setLoc(eqx::Point<float>(
                eqx::Random::randomNumber(0.0f, 1100.0f),
                eqx::Random::randomNumber(0.0f, 700.0f)));
        });
    std::ranges::for_each(s_Batch2, [](pul::TxQuad& quad)
        {
            quad.setLoc(eqx::Point<float>(
                eqx::Random::randomNumber(0.0f, 1150.0f),
                eqx::Random::randomNumber(0.0f, 750.0f)));
        });
}

#endif // PROVINGGROUNDS_DETAILS_BATCHTESTIMPL_IPP
