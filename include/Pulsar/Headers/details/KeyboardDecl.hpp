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
            A = GLFW_KEY_A,
            B = GLFW_KEY_B,
            C = GLFW_KEY_C,
            D = GLFW_KEY_D,
            E = GLFW_KEY_E,
            F = GLFW_KEY_F,
            G = GLFW_KEY_G,
            H = GLFW_KEY_H,
            I = GLFW_KEY_I,
            J = GLFW_KEY_J,
            K = GLFW_KEY_K,
            L = GLFW_KEY_L,
            M = GLFW_KEY_M,
            N = GLFW_KEY_N,
            O = GLFW_KEY_O,
            P = GLFW_KEY_P,
            Q = GLFW_KEY_Q,
            R = GLFW_KEY_R,
            S = GLFW_KEY_S,
            T = GLFW_KEY_T,
            U = GLFW_KEY_U,
            V = GLFW_KEY_V,
            W = GLFW_KEY_W,
            X = GLFW_KEY_X,
            Y = GLFW_KEY_Y,
            Z = GLFW_KEY_Z,
            N0 = GLFW_KEY_0,
            N1 = GLFW_KEY_1,
            N2 = GLFW_KEY_2,
            N3 = GLFW_KEY_3,
            N4 = GLFW_KEY_4,
            N5 = GLFW_KEY_5,
            N6 = GLFW_KEY_6,
            N7 = GLFW_KEY_7,
            N8 = GLFW_KEY_8,
            N9 = GLFW_KEY_9,
            Space = GLFW_KEY_SPACE,
            Escape = GLFW_KEY_ESCAPE,
            Enter = GLFW_KEY_ENTER,
            Tab = GLFW_KEY_TAB,
            Up = GLFW_KEY_UP,
            Down = GLFW_KEY_DOWN,
            Left = GLFW_KEY_LEFT,
            Right = GLFW_KEY_RIGHT
        };

        Keyboard() = delete;
        Keyboard(const Keyboard&) = delete;
        Keyboard(Keyboard&&) = delete;
        Keyboard& operator= (const Keyboard&) = delete;
        Keyboard& operator= (Keyboard&&) = delete;
        ~Keyboard() = delete;

        static inline void buttonCallback(GLFWwindow* window, int key,
            int scancode, int action, int mods) noexcept;

        [[nodiscard]] static inline Button getKey(Key key) noexcept;
        [[nodiscard]] static inline bool isPressed(Key key) noexcept;
        [[nodiscard]] static inline bool isReleased(Key key) noexcept;

    private:
        constinit static inline auto s_Keys =
            std::invoke([]() constexpr
                {
                    auto result = std::array<Button, 400_size>();
                    result.fill(Button::Up);
                    return result;
                });
    };
}

#endif // PULSAR_DETAILS_KEYBOARDDECL_HPP
