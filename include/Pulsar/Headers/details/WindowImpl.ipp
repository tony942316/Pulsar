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

#ifndef PULSAR_DETAILS_WINDOWIMPL_IPP
#define PULSAR_DETAILS_WINDOWIMPL_IPP

#include "WindowDecl.hpp"

namespace pul
{

    constexpr Window::Window() noexcept
        :
        m_Width(0.0f),
        m_Height(0.0f),
        m_DeltaTime(0.0f),
        m_TotalTime(0.0f),
        m_FrameCount(0_size),
        m_Name(),
        m_UpdateFunc(),
        m_RenderFunc(),
        m_Window()
    {
    }

    inline Window::Window(int width, int height,
        std::string_view name) noexcept
        :
        Window()
    {
        init(width, height, name);
    }

    inline void Window::init(int width, int height,
        std::string_view name) noexcept
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, false);

        Keyboard::init();

        m_Width = static_cast<float>(width);
        m_Height = static_cast<float>(height);

        m_Name.init();
        *m_Name.get() = name;

        m_UpdateFunc.init();
        m_RenderFunc.init();

        m_Window.init(glfwDestroyWindow, glfwCreateWindow, width, height,
            m_Name.get()->c_str(), nullptr, nullptr);

        glfwMakeContextCurrent(m_Window.get());
        glfwSwapInterval(1);

        glfwSetCursorPosCallback(m_Window.get(), Mouse::moveCallback);
        glfwSetMouseButtonCallback(m_Window.get(), Mouse::buttonCallback);
        glfwSetKeyCallback(m_Window.get(), Keyboard::buttonCallback);

        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        glViewport(0, 0, width, height);
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    inline void Window::free() noexcept
    {
        m_Name.free();
        m_UpdateFunc.free();
        m_RenderFunc.free();
        m_Window.free();
    }

    inline void Window::show() noexcept
    {
        std::cout << "Version: "sv << glGetString(GL_VERSION) << std::endl;
        std::cout << "Max Texture: "sv <<
            GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS << std::endl;

        auto frameTimer = eqx::StopWatch();
        auto printTimer = eqx::StopWatch();
        auto avgFPS = 0.0;
        auto longestFrame = 0LL;
        auto shortestFrame = std::numeric_limits<long long>::max();

        auto currentFrame = 0.0f;
        auto deltaTime = 0.0f;
        auto lastFrame = 0.0f;
        while (!glfwWindowShouldClose(m_Window.get()))
        {
            frameTimer.start();

            currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            std::invoke(*m_UpdateFunc.get());
            std::invoke(*m_RenderFunc.get());

            glfwSwapBuffers(m_Window.get());
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glfwPollEvents();

            m_DeltaTime = deltaTime;

            frameTimer.stop();

            m_TotalTime += frameTimer.getSeconds();
            m_FrameCount++;

            if (frameTimer.getTime<t_US>() > longestFrame)
            {
                longestFrame = frameTimer.getTime<t_US>();
            }

            if (frameTimer.getTime<t_US>() < shortestFrame)
            {
                shortestFrame = frameTimer.getTime<t_US>();
            }

            if (printTimer.readSeconds() > 1.0)
            {
                avgFPS = static_cast<double>(m_FrameCount) / m_TotalTime;
                std::cout << "********************"sv << std::endl;
                std::cout << "Frame Count: "sv << m_FrameCount << std::endl;
                std::cout << "Total Time: "sv << m_TotalTime << std::endl;
                std::cout << "Average FPS: "sv << avgFPS << std::endl;
                std::cout << "Longest Frame: "sv << longestFrame <<
                    "us" << std::endl;
                std::cout << "Shortest Frame: "sv << shortestFrame <<
                    "us" << std::endl;
                std::cout << "********************"sv << std::endl;
                m_FrameCount = 0_size;
                m_TotalTime = 0.0;
                longestFrame = 0.0;
                shortestFrame = std::numeric_limits<long long>::max();
                printTimer.start();
            }
        }

        free();
        glfwTerminate();
    }

    inline void Window::close() noexcept
    {
        glfwSetWindowShouldClose(m_Window.get(), true);
    }

    inline void Window::setUpdateFunc(
        const std::function<void()>& func) noexcept
    {
        *m_UpdateFunc.get() = func;
    }

    inline void Window::setRenderFunc(
        const std::function<void()>& func) noexcept
    {
        *m_RenderFunc.get() = func;
    }

    [[nodiscard]] inline float Window::getWidth() const noexcept
    {
        return m_Width;
    }

    [[nodiscard]] inline float Window::getHeight() const noexcept
    {
        return m_Height;
    }

    [[nodiscard]] inline float Window::getDeltaTime() const noexcept
    {
        return m_DeltaTime;
    }

    [[nodiscard]] inline std::string_view Window::getName() const noexcept
    {
        return *m_Name.get();
    }
}

#endif // PULSAR_DETAILS_WINDOWIMPL_IPP
