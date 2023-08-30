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

void update() noexcept
{
    if (pul::Keyboard::getKey(pul::Keyboard::Key::Escape) == pul::Keyboard::Button::Down)
    {
        g_Window.close();
    }
}

void render() noexcept
{
    auto model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(pul::Mouse::getPosition().x, pul::Mouse::getPosition().y, 0.0f));
    model = glm::scale(model, glm::vec3(100.0f, 100.0f, 1.0f));
    auto view = glm::mat4(1.0f);
    auto projection = glm::ortho(0.0f, 1200.0f, 800.0f, 0.0f, -1.0f, 1.0f);

    auto shader = pul::Shader();
    shader.init("Resources/Shaders/MVPVertex.glsl", "Resources/Shaders/MVPFragment.glsl");

    shader.setMat4("u_Model", model);
    shader.setMat4("u_View", view);
    shader.setMat4("u_Projection", projection);
    shader.setVec4("u_Color", glm::vec4(0.8f, 0.0f, 0.2f, 1.0f));

    float verts[] = {
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    int attrs[] = {
        3
    };

    unsigned int inds[] = {
        0, 1, 2,
        0, 2, 3
    };

    auto vb = pul::VertexBuffer(verts, attrs);
    auto ib = pul::IndexBuffer(inds);

    shader.enable();
    vb.enable();
    ib.enable();

    glDrawElements(GL_TRIANGLES, static_cast<GLint>(ib.getCount()), GL_UNSIGNED_INT, 0);

    ib.disable();
    vb.disable();
    shader.disable();
}

int main()
{
    std::cout << "Start" << std::endl;

    g_Window.init(1200, 800, "Pulsar Window");
    g_Window.setUpdateFunc(update);
    g_Window.setRenderFunc(render);

    g_Window.show();

    std::cout << "End" << std::endl;
    return 0;
}
