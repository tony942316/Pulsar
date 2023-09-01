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

#ifndef PULSAR_DETAILS_MOUSEIMPL_IPP
#define PULSAR_DETAILS_MOUSEIMPL_IPP

#include "MouseDecl.hpp"

namespace pul
{
    inline void Mouse::moveCallback([[maybe_unused]] GLFWwindow* window,
        double xpos, double ypos) noexcept
    {
        m_Position = eqx::Point<double>(xpos, ypos);
    }

    inline void Mouse::buttonCallback([[maybe_unused]] GLFWwindow* window,
        int button, int action, [[maybe_unused]] int mods) noexcept
    {
        if (action == GLFW_PRESS)
        {
            switch (button)
            {
            case GLFW_MOUSE_BUTTON_LEFT:
                m_LCD = getPosition();
                m_LeftButton = Button::Down;
                break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                m_RCD = getPosition();
                m_RightButton = Button::Down;
                break;
            }
        }
        else if (action == GLFW_RELEASE)
        {
            switch (button)
            {
            case GLFW_MOUSE_BUTTON_LEFT:
                m_LCU = getPosition();
                m_LeftButton = Button::Up;
                break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                m_RCU = getPosition();
                m_RightButton = Button::Up;
                break;
            }
        }
    }

    [[nodiscard]] inline const eqx::Point<double>&
        Mouse::getPosition() noexcept
    {
        return m_Position;
    }

    [[nodiscard]] inline const eqx::Point<double>&
        Mouse::getLeftClickPosition() noexcept
    {
        return m_LCD;
    }

    [[nodiscard]] inline const eqx::Point<double>&
        Mouse::getLeftReleasePosition() noexcept
    {
        return m_LCU;
    }

    [[nodiscard]] inline const eqx::Point<double>&
        Mouse::getRightClickPosition() noexcept
    {
        return m_RCD;
    }

    [[nodiscard]] inline const eqx::Point<double>&
        Mouse::getRightReleasePosition() noexcept
    {
        return m_RCU;
    }

    [[nodiscard]] inline Mouse::Button Mouse::getLeftButton() noexcept
    {
        return m_LeftButton;
    }

    [[nodiscard]] inline Mouse::Button Mouse::getRightButton() noexcept
    {
        return m_RightButton;
    }
}

#endif // PULSAR_DETAILS_MOUSEIMPL_IPP
