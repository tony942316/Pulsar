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

    s_Window.show();
}

inline void Tester::update() noexcept
{
    if (pul::Keyboard::isPressed(pul::Keyboard::Key::Escape))
    {
        s_Window.close();
    }

    if (pul::Keyboard::isPressed(pul::Keyboard::Key::N1))
    {
        s_State = State::Quad;
    }

    if (pul::Keyboard::isPressed(pul::Keyboard::Key::N2))
    {
        s_State = State::Text;
    }

    if (pul::Keyboard::isPressed(pul::Keyboard::Key::N3))
    {
        s_State = State::Cube;
    }

    if (pul::Keyboard::isPressed(pul::Keyboard::Key::N4))
    {
        s_State = State::Blender;
    }

    if (pul::Keyboard::isPressed(pul::Keyboard::Key::N5))
    {
        s_State = State::Batch;
    }

    if (pul::Keyboard::isPressed(pul::Keyboard::Key::N0))
    {
        s_State = State::None;
    }

    if (Ui::update())
    {
        s_Window.close();
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
    case State::Batch:
        BatchTest::update(s_Window.getDeltaTime());
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
    case State::Batch:
        BatchTest::render();
        break;
    }

    Ui::render();
}

#endif // PROVINGGROUNDS_DETAILS_TESTERIMPL_IPP
