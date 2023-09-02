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

#include "Pulsar/Pulsar.hpp"


constinit inline auto g_Window = pul::Window();
constinit inline auto g_Quad = pul::Quad();

void update() noexcept
{
    if (pul::Keyboard::getKey(pul::Keyboard::Key::Escape) ==
            pul::Keyboard::Button::Down)
    {
        g_Window.close();
    }

    g_Quad.setDrawBox(eqx::Rectangle<float>(
        static_cast<float>(pul::Mouse::getPosition().x) - 50.0f,
        800.0f - static_cast<float>(pul::Mouse::getPosition().y) - 50.0f,
        100.0f,
        100.0f));
}

void render() noexcept
{
    pul::Renderer::draw(g_Quad);
}

int main()
{
    std::cout << "Start" << std::endl;

    g_Window.init(1200, 800, "Pulsar Window");
    pul::Quad::init(1200.0f, 800.0f);
    g_Window.setUpdateFunc(update);
    g_Window.setRenderFunc(render);

    g_Quad.setColor(glm::vec4(0.8f, 0.0f, 0.2f, 1.0f));
    g_Quad.setMixture(1.0f);
    g_Quad.setTexture("Resources/Textures/AwesomeFace.png");

    g_Window.show();

    std::cout << "End" << std::endl;
    return 0;
}
