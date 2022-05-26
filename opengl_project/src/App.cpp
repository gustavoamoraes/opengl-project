#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    //ImGui
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init("#version 330 core");
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    glewInit();

    float vertices[]
    {
        -50.0f, -50.0f,   0.0f,  0.0f,
         50.0f, -50.0f,   1.0f,  0.0f,
         50.0f,  50.0f,   1.0f,  1.0f,
        -50.0f,  50.0f,   0.0f,  1.0f    
    };

    unsigned int traingles[]
    {
        0,1,2,
        3,0,2
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    Renderer renderer;

    VertexArray vao;
    VertexBuffer vb(vertices, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;

    layout.Push<float>(2);
    layout.Push<float>(2);
    vao.AddBuffer(layout, vb);

    IndexBuffer ib(traingles, 6);

    Shader shader = Shader("res/shaders/basic_shader.shader");
    shader.Bind();
    shader.SetUniforms4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

    glm::mat4 proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(250.0f, 250.0f, 0.0f));

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.0f));

    glm::mat4 mvp = proj * view * model;
    shader.SetUniformsMat4f("u_MVP", mvp);

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            std::cout << mvp[j][i] << "   ";
            //std::cout << "\n" << std::endl;
        }

        std::cout << std::endl;
    }

    shader.SetUniforms1i("u_Texture", 0);
    Texture texture("res/textures/tex.png");
    texture.Bind(0);
    glm::vec4 clear_color(0.45f, 0.55f, 0.60f, 1.00f);
    bool b(false);

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();

        renderer.Draw(ib, vao, shader);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &b);      // Edit bools storing our window open/close state

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}