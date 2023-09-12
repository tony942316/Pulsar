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

#ifndef PULSAR_DETAILS_WINDOWDECL_HPP
#define PULSAR_DETAILS_WINDOWDECL_HPP

#include "Dependencies.hpp"

#include "../Mouse.hpp"
#include "../Keyboard.hpp"

namespace pul
{
    class Window
    {
    public:
        explicit constexpr Window() noexcept;
        explicit inline Window(int width, int height,
            std::string_view name) noexcept;

        inline void init(int width, int height, std::string_view name) noexcept;
        inline void free() noexcept;

        inline void show() noexcept;
        inline void close() noexcept;

        inline void setUpdateFunc(const std::function<void()>& func) noexcept;
        inline void setRenderFunc(const std::function<void()>& func) noexcept;

        [[nodiscard]] inline float getWidth() const noexcept;
        [[nodiscard]] inline float getHeight() const noexcept;
        [[nodiscard]] inline float getDeltaTime() const noexcept;
        [[nodiscard]] inline std::string_view getName() const noexcept;

    private:
        using UniqueWindow =
            eqx::UniqueResource<GLFWwindow*, decltype(&glfwDestroyWindow)>;

        float m_Width, m_Height, m_DeltaTime;
        double m_TotalTime;

        std::size_t m_FrameCount;

        eqx::UniquePointer<std::string> m_Name;
        eqx::UniquePointer<std::function<void()>> m_UpdateFunc, m_RenderFunc;
        UniqueWindow m_Window;
    };
}

#endif // PULSAR_DETAILS_WINDOWDECL_HPP
