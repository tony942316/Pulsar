#include <iostream>

#include "Pulsar/Pulsar.hpp"

int main()
{
    std::cout << "Start" << std::endl;

    GLFWwindow* window;

    if (!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);

    window = glfwCreateWindow(640, 480, "Hello Window", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, 640, 480);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

    while (!glfwWindowShouldClose(window))
    {
        shader.enable();
        vb.enable();
        ib.enable();

        glDrawElements(GL_TRIANGLES, static_cast<GLint>(ib.getCount()), GL_UNSIGNED_INT, 0);

        ib.disable();
        vb.disable();
        shader.disable();

        glfwSwapBuffers(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();
    }

    vb.free();
    shader.free();
    ib.free();

    glfwTerminate();

    std::cout << "End" << std::endl;
    return 0;
}
