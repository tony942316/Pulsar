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

#ifndef PULSAR_DETAILS_KEYBOARDDECL_HPP
#define PULSAR_DETAILS_KEYBOARDDECL_HPP

#include "Dependencies.hpp"

namespace pul
{
    class Keyboard
    {
    public:
        enum class Button
        {
            Up = GLFW_RELEASE,
            Down = GLFW_PRESS
        };

        enum class Key
        {
            W = GLFW_KEY_W,
            A = GLFW_KEY_A,
            S = GLFW_KEY_S,
            D = GLFW_KEY_D,
            R = GLFW_KEY_R,
            Space = GLFW_KEY_SPACE,
            Escape = GLFW_KEY_ESCAPE
        };

        Keyboard() = delete;
        Keyboard(const Keyboard&) = delete;
        Keyboard(Keyboard&&) = delete;
        Keyboard& operator= (const Keyboard&) = delete;
        Keyboard& operator= (Keyboard&&) = delete;
        ~Keyboard() = delete;

        static inline void init() noexcept;

        static inline void buttonCallback(GLFWwindow* window, int key,
            int scancode, int action, int mods) noexcept;

        [[nodiscard]] static inline Button getKey(Key key) noexcept;

    private:
        constinit static inline auto s_Keys = eqx::nullp<std::vector<Button>>;
    };
}

#endif // PULSAR_DETAILS_KEYBOARDDECL_HPP
