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

#ifndef PROVINGGROUNDS_DETAILS_TESTERIMPL_IPP
#define PROVINGGROUNDS_DETAILS_TESTERIMPL_IPP

#include "TesterDecl.hpp"

inline void Tester::run() noexcept
{
    s_Window.init(1200, 800, "Pulsar Test Window");
    s_Window.setUpdateFunc(update);
    s_Window.setRenderFunc(render);
    pul::Renderer::init();
    pul::batch::QuadT::setUniforms(1200.0f, 800.0f);
    pul::Font::setUniforms(1200.0f, 800.0f);

    s_Window.show();
}

inline void Tester::update() noexcept
{
    if (pul::Keyboard::getKey(pul::Keyboard::Key::Escape) ==
        pul::Keyboard::Button::Down)
    {
        s_Window.close();
    }

    if (pul::Keyboard::getKey(pul::Keyboard::Key::D) ==
        pul::Keyboard::Button::Down)
    {
        s_State = State::Quad;
    }

    if (pul::Keyboard::getKey(pul::Keyboard::Key::W) ==
        pul::Keyboard::Button::Down)
    {
        s_State = State::Text;
    }

    if (pul::Keyboard::getKey(pul::Keyboard::Key::R) ==
        pul::Keyboard::Button::Down)
    {
        s_State = State::Cube;
    }

    if (pul::Keyboard::getKey(pul::Keyboard::Key::S) ==
        pul::Keyboard::Button::Down)
    {
        s_State = State::Blender;
    }

    if (pul::Keyboard::getKey(pul::Keyboard::Key::A) ==
        pul::Keyboard::Button::Down)
    {
        s_State = State::None;
    }

    switch (s_State)
    {
    case State::None:
        break;
    case State::Quad:
        QuadTest::update();
        break;
    case State::Text:
        TextTest::update();
        break;
    case State::Cube:
        CubeTest::update(s_Window.getDeltaTime());
        break;
    case State::Blender:
        BlenderTest::update(s_Window.getDeltaTime());
        break;
    }
}

inline void Tester::render() noexcept
{
    switch (s_State)
    {
    case State::None:
        break;
    case State::Quad:
        QuadTest::render();
        break;
    case State::Text:
        TextTest::render();
        break;
    case State::Cube:
        CubeTest::render();
        break;
    case State::Blender:
        BlenderTest::render();
        break;
    }
}

#endif // PROVINGGROUNDS_DETAILS_TESTERIMPL_IPP
