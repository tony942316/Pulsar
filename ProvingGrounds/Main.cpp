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

constinit inline auto g_Font = pul::Font();
constinit inline auto g_Texture = pul::Texture();

constinit inline auto g_MouseQuads = pul::batch::Quad();

constinit inline auto g_Batch = pul::batch::Quad();
constinit inline auto g_Batch2 = pul::batch::Quad();
constinit inline auto g_Batch3 = pul::batch::Quad();
constinit inline auto g_Batch4 = pul::batch::Quad();

constinit inline auto g_View = glm::vec3(0.0f, 0.0f, 0.0f);

void update() noexcept
{
    if (pul::Keyboard::getKey(pul::Keyboard::Key::Escape) ==
        pul::Keyboard::Button::Down)
    {
        g_Window.close();
    }

    if (pul::Keyboard::getKey(pul::Keyboard::Key::A) ==
        pul::Keyboard::Button::Down)
    {
        g_View.x -= 400.0f * g_Window.getDeltaTime();
    }
    else if (pul::Keyboard::getKey(pul::Keyboard::Key::D) ==
        pul::Keyboard::Button::Down)
    {
        g_View.x += 400.0f * g_Window.getDeltaTime();
    }

    if (pul::Keyboard::getKey(pul::Keyboard::Key::W) ==
        pul::Keyboard::Button::Down)
    {
        g_View.y += 400.0f * g_Window.getDeltaTime();
    }
    else if (pul::Keyboard::getKey(pul::Keyboard::Key::S) ==
        pul::Keyboard::Button::Down)
    {
        g_View.y -= 400.0f * g_Window.getDeltaTime();
    }

    auto view = glm::translate(glm::mat4(1.0f), g_View);
    pul::shader::getQuad().setMat4("u_View", view);

    g_MouseQuads.setRect(0, eqx::Rectangle<float>(
        static_cast<float>(pul::Mouse::getPosition().x - 100.0f),
        static_cast<float>(pul::Mouse::getPosition().y),
        100.0f, 100.0f));
    g_MouseQuads.setRect(1, eqx::Rectangle<float>(
        static_cast<float>(pul::Mouse::getPosition().x),
        static_cast<float>(pul::Mouse::getPosition().y),
        100.0f, 100.0f));
}

void render() noexcept
{
    pul::Renderer::drawText(g_Batch2);
    pul::Renderer::drawText(g_Batch3);
    pul::Renderer::drawText(g_Batch4);

    pul::Renderer::draw(g_MouseQuads);
    pul::Renderer::draw(g_Batch);
}

int main()
{
    std::cout << "Start" << std::endl;

    g_Window.init(1200, 800, "Pulsar Window");
    g_Window.setUpdateFunc(update);
    g_Window.setRenderFunc(render);
    pul::Renderer::init();

    g_Texture.init("Resources/Textures/AwesomeFace.png");

    g_MouseQuads.setTexture(0, g_Texture);
    g_MouseQuads.setTexture(1, g_Texture);

    //FT_Done_FreeType(ft);

    g_Font.init("Resources/Fonts/Poppins/Poppins-Regular.ttf");

    //g_Batch2 = g_Font.getText("abcdefghijklmnopqrstuvwxyz'/\\;:,.!?",
    g_Batch2 = g_Font.getText("abcdefghijklmnopqrstuvwxyz",
        eqx::Point<float>(100.0f, 100.0f));
    //g_Batch3 = g_Font.getText("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",
    g_Batch3 = g_Font.getText("ABCDEFGHIJKLMNOPQRSTUVWXYZ",
        eqx::Point<float>(100.0f, 150.0f));
    g_Batch4 = g_Font.getText("Like Wow Ok!",
        eqx::Point<float>(100.0f, 200.0f));

    g_Batch.setRect(0, eqx::Rectangle<float>(500.0f, 500.0f, 100.0f, 100.0f));
    g_Batch.setTexture(0, g_Texture);

    pul::batch::Quad::setUniforms(1200.0f, 800.0f);
    pul::Font::setUniforms(1200.0f, 800.0f);

    g_Window.show();

    std::cout << "End" << std::endl;
    return 0;
}
