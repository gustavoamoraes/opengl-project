#include "Scene.h"
#include "imgui/imgui.h"
#include "Renderer.h"
#include "GL/glew.h"

scene::SceneMenu::SceneMenu(Scene*& firstScene) : m_CurrentScene(firstScene)
{
}

void scene::SceneMenu::OnImGUIRender()
{
    if (ImGui::TreeNode("Scenes"))
    {
        for (auto& test : m_Scenes)
        {
            if (ImGui::Selectable(test.first.c_str()))
                m_CurrentScene = test.second();
        }

        ImGui::TreePop();
    }
}

void scene::SceneMenu::OnRender()
{
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
