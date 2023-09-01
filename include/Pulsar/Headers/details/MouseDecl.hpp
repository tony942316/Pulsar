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

#ifndef PULSAR_DETAILS_MOUSEDECL_HPP
#define PULSAR_DETAILS_MOUSEDECL_HPP

#include "Dependencies.hpp"

namespace pul
{
    class Mouse
    {
    public:
        enum class Button
        {
            Up,
            Down
        };

        Mouse() = delete;
        Mouse(const Mouse&) = delete;
        Mouse(Mouse&&) = delete;
        Mouse& operator= (const Mouse&) = delete;
        Mouse& operator= (Mouse&&) = delete;
        ~Mouse() = delete;

        static inline void moveCallback(GLFWwindow* window, double xpos,
            double ypos) noexcept;
        static inline void buttonCallback(GLFWwindow* window, int button,
            int action, int mods) noexcept;

        [[nodiscard]] static inline const eqx::Point<double>&
            getPosition() noexcept;
        [[nodiscard]] static inline const eqx::Point<double>&
            getLeftClickPosition() noexcept;
        [[nodiscard]] static inline const eqx::Point<double>&
            getLeftReleasePosition() noexcept;
        [[nodiscard]] static inline const eqx::Point<double>&
            getRightClickPosition() noexcept;
        [[nodiscard]] static inline const eqx::Point<double>&
            getRightReleasePosition() noexcept;
        [[nodiscard]] static inline Button getLeftButton() noexcept;
        [[nodiscard]] static inline Button getRightButton() noexcept;

    private:
        constinit static inline auto m_Position = eqx::Point<double>(),
            m_LCD = eqx::Point<double>(),
            m_LCU = eqx::Point<double>(),
            m_RCD = eqx::Point<double>(),
            m_RCU = eqx::Point<double>();

        constinit static inline auto m_LeftButton = Button::Up,
            m_RightButton = Button::Up;
    };
}

#endif // PULSAR_MOUSEDECL_HPP
