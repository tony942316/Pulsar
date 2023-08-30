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

#ifndef PULSAR_KEYBOARDIMPL_IPP
#define PULSAR_KEYBOARDIMPL_IPP

#include "KeyboardDecl.hpp"

namespace pul
{
    inline void Keyboard::init() noexcept
    {
        static auto keyStore = std::vector<Button>(400, Button::Up);
        s_Keys = &keyStore;
    }

    inline void Keyboard::buttonCallback([[maybe_unused]] GLFWwindow* window,
        int key, [[maybe_unused]] int scancode, int action,
        [[maybe_unused]] int mods) noexcept
    {
        if (action == GLFW_REPEAT)
        {
            return;
        }
        s_Keys->at(static_cast<std::size_t>(key)) = static_cast<Button>(action);
    }

    [[nodiscard]] inline Keyboard::Button Keyboard::getKey(Key key) noexcept
    {
        return s_Keys->at(static_cast<std::size_t>(key));
    }
}

#endif // PULSAR_KEYBOARDIMPL_IPP
