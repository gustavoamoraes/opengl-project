#include <iostream>

#include "Scene.h"
#include "imgui/imgui.h"
#include "Renderer.h"
#include "GL/glew.h"

void Scene::OnUpdate()
{
	for (Entity* e : m_Entities)
	{
		if (e->m_Active)	
			e->Update();
	}
}

void Scene::AddEntity(Entity* entiry)
{
	m_Entities.push_back(entiry);
}
