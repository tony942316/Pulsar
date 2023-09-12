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
constinit inline auto g_Quad2 = pul::Quad();

constinit inline auto g_Font = pul::Font();

constinit inline auto g_Quads = eqx::UniquePointer<std::vector<pul::Quad>>();
constinit inline auto g_Quads2 = eqx::UniquePointer<std::vector<pul::Quad>>();
constinit inline auto g_Quads3 = eqx::UniquePointer<std::vector<pul::Quad>>();

constinit inline auto g_Texture = pul::Texture();

void update() noexcept
{
    if (pul::Keyboard::getKey(pul::Keyboard::Key::Escape) ==
        pul::Keyboard::Button::Down)
    {
        g_Window.close();
    }

    g_Quad.setDrawBox(eqx::Rectangle<float>(
        static_cast<float>(pul::Mouse::getPosition().x - 100.0f),
        static_cast<float>(pul::Mouse::getPosition().y),
        100.0f, 100.0f));
    g_Quad2.setDrawBox(eqx::Rectangle<float>(
        static_cast<float>(pul::Mouse::getPosition().x),
        static_cast<float>(pul::Mouse::getPosition().y),
        100.0f, 100.0f));
}

void render() noexcept
{
    pul::Renderer::draw(g_Quad);
    pul::Renderer::draw(g_Quad2);

    pul::Renderer::draw(*g_Quads.get());
    pul::Renderer::draw(*g_Quads2.get());
    pul::Renderer::draw(*g_Quads3.get());
}

int main()
{
    std::cout << "Start" << std::endl;

    g_Window.init(1200, 800, "Pulsar Window");
    g_Window.setUpdateFunc(update);
    g_Window.setRenderFunc(render);
    pul::Renderer::init(1200.0f, 800.0f);

    g_Quad.setColor(glm::vec4(0.8f, 0.0f, 0.2f, 1.0f));
    g_Quad.setMixture(0.5f);
    g_Texture.init("Resources/Textures/AwesomeFace.png");
    g_Quad.setTexture(&g_Texture);

    g_Quad2.setColor(glm::vec4(0.8f, 0.0f, 0.2f, 1.0f));
    g_Quad2.setMixture(0.5f);
    g_Quad2.setTexture(&g_Texture);

    //FT_Done_FreeType(ft);

    g_Font.init("Resources/Fonts/Poppins/Poppins-Regular.ttf");

    g_Quads.init(g_Font.getText("abcdefghijklmnopqrstuvwxyz",
        eqx::Point<float>(100.0f, 100.0f)));
    g_Quads2.init(g_Font.getText("ABCDEFGHIJKLMNOPQRSTUVWXYZ",
        eqx::Point<float>(100.0f, 150.0f)));
    g_Quads3.init(g_Font.getText("Like",
        eqx::Point<float>(100.0f, 200.0f)));

    g_Window.show();

    std::cout << "End" << std::endl;
    return 0;
}
