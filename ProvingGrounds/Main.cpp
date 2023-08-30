#include <iostream>

#include "Pulsar/Pulsar.hpp"

void update() noexcept
{

}

void render() noexcept
{
    auto shader = pul::Shader();
    shader.init("Resources/Shaders/BasicVertex.glsl", "Resources/Shaders/BasicFragment.glsl");

    float verts[] = {
        -0.5f, 0.5f,
        0.5f, 0.5f,
        0.5f, -0.5f,
        -0.5f, -0.5f
    };

    int attrs[] = {
        2
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

    auto window = pul::Window(1200, 800, "Pulsar Window");
    window.setUpdateFunc(update);
    window.setRenderFunc(render);

    window.show();

    std::cout << "End" << std::endl;
    return 0;
}
