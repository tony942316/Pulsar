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

#include "Headers/Tester.hpp"

constinit inline auto g_Font = pul::Font();
constinit inline auto g_Texture = pul::Texture();

constinit inline auto g_MouseQuads = pul::batch::Quad();

constinit inline auto g_Batch = pul::batch::Quad();
constinit inline auto g_Batch2 = pul::batch::Quad();
constinit inline auto g_Batch3 = pul::batch::Quad();
constinit inline auto g_Batch4 = pul::batch::Quad();

constinit inline auto g_View = glm::vec3(0.0f, 0.0f, 0.0f);

constinit inline auto g_VA = pul::VertexArray();
constinit inline auto g_Shader = pul::Shader();

void getThings() noexcept
{
    auto vertices = std::vector<float>();
    auto indices = std::vector<unsigned int>();

    auto file = std::ifstream();
    file.open("Resources/Meshes/sword.obj", std::ios::in);

    auto line = std::string();
    while (file.eof() == false)
    {
        std::getline(file, line, '\n');

        std::cout << line << std::endl;

        if (line.size() == 0)
            continue;

        if (line.at(0) == 'v' && line.at(1) == ' ')
        {
            auto v = line |
                std::views::split(' ') |
                std::views::drop(1);
            for (const auto word : v)
            {
                auto temp = std::string();
                std::ranges::copy(word, std::back_inserter(temp));
                vertices.emplace_back(std::atof(temp.c_str()));
            }

            vertices.emplace_back(eqx::Random::randomNumber(0.8f, 1.0f));
            vertices.emplace_back(eqx::Random::randomNumber(0.8f, 1.0f));
            vertices.emplace_back(eqx::Random::randomNumber(0.8f, 1.0f));
        }
        else if (line.at(0) == 'f')
        {

            auto v = line |
                std::views::split(' ') |
                std::views::drop(1);
            auto corners = std::vector<float>();

            for (const auto data : v)
            {
                auto index = data |
                    std::views::split('/') |
                    std::views::take(1);
                auto temp = std::string();
                for (const auto what : index)
                {
                    std::ranges::copy(what, std::back_inserter(temp));
                }
                corners.emplace_back((unsigned int)std::atoi(temp.c_str()));
            }
            if (corners.size() == 4)
            {
                indices.emplace_back(corners.at(0));
                indices.emplace_back(corners.at(1));
                indices.emplace_back(corners.at(2));

                indices.emplace_back(corners.at(0));
                indices.emplace_back(corners.at(2));
                indices.emplace_back(corners.at(3));
            }
            else if (corners.size() == 3)
            {
                indices.emplace_back(corners.at(0));
                indices.emplace_back(corners.at(1));
                indices.emplace_back(corners.at(2));
            }
        }
    }

    //eqx::println(eqx::toString(vertices));
    //eqx::println(eqx::toString(indices));

    g_VA.addVertices(vertices);
    g_VA.addIndices(indices);
}

/*
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

    static auto rotX = 10.0f;
    static auto rotY = 10.0f;
    auto model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(
        (float)pul::Mouse::getPosition().x,
        800.0f - (float)pul::Mouse::getPosition().y,
        -300.0f));
    model = glm::rotate(model, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
    rotX += 0.1f;
    model = glm::rotate(model, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
    rotY += 0.2f;
    model = glm::scale(model, glm::vec3(300.0f, 300.0f, 300.0f));
    g_Shader.setMat4("u_Model", model);
}

void render() noexcept
{
    pul::Renderer::drawText(g_Batch2);
    pul::Renderer::drawText(g_Batch3);
    pul::Renderer::drawText(g_Batch4);

    //pul::Renderer::draw(g_MouseQuads);
    pul::Renderer::draw(g_Batch);

    pul::Renderer::draw(g_Shader, g_VA);
}
*/

int main()
{
    eqx::println("Start\n");

    Tester::run();

    eqx::println("\nEnd");
    return 0;
}

/*
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

    auto vertices = std::vector<float>({
        -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f });

    auto indices = std::vector<unsigned int>({
        0U, 1U, 2U,
        0U, 2U, 3U,

        4U, 5U, 6U,
        4U, 6U, 7U,

        1U, 5U, 6U,
        1U, 6U, 2U,

        4U, 0U, 3U,
        4U, 3U, 7U,

        0U, 4U, 5U,
        0U, 5U, 1U,

        6U, 7U, 3U,
        6U, 3U, 2U });

    auto attribs = std::vector<int>({
        3, 3 });

    g_VA.init();
    //g_VA.addVertices(vertices);
    //g_VA.addIndices(indices);
    g_VA.setAttribs(attribs);

    auto model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(100.0f, 100.0f, -50.0f));
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    model = glm::scale(model, glm::vec3(25.0f, 25.0f, 25.0f));
    auto view = glm::mat4(1.0f);
    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    auto proj = glm::mat4(1.0f);
    //proj = glm::perspective(glm::radians(90.0f), 1200.0f / 800.0f, 0.1f, 1000.0f);
    proj = glm::ortho(0.0f, 1200.0f, 0.0f, 800.0f, 0.1f, 1000.0f);
    //auto color = glm::vec4(0.8f, 0.0f, 0.2f, 1.0f);
    g_Shader.init("Resources/Shaders/MVPVertex.glsl", "Resources/Shaders/MVPFragment.glsl");
    g_Shader.setMat4("u_Model", model);
    g_Shader.setMat4("u_View", view);
    g_Shader.setMat4("u_Projection", proj);
    //g_Shader.setVec4("u_Color", color);

    //g_Shader.setMat4("u_Model", glm::mat4(1.0f));
    //g_Shader.setMat4("u_View", glm::mat4(1.0f));
    //g_Shader.setMat4("u_Projection", glm::mat4(1.0f));

    getThings();

    g_Window.show();

    std::cout << "End" << std::endl;
    return 0;
}
*/
