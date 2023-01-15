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

void Scene::OnNewEntities()
{
	if (!m_NewEntitiesToStart)
		return;

	for (size_t i = 0; i < m_EntitiesToStart.size(); i++)
	{
		Entity* entity = m_EntitiesToStart[i];
		entity->Start();
		m_Entities.push_back(entity);
	}

	m_EntitiesToStart.clear();
	m_NewEntitiesToStart = false;
}

/*void Scene::CreateNewEntities()
{
	if (!m_NewEntitiesToAdd);
		return;

	for (auto entityConstrutor : m_EntitiesToAdd)
	{
		Entity* newEntity = entityConstrutor();
		m_Entities.push_back(newEntity);
	}

	m_NewEntitiesToAdd = false;
}*/

void Scene::AddEntity(Entity* entity)
{
	entity->m_MyScene = this;
	m_EntitiesToStart.push_back(entity);
	m_NewEntitiesToStart = true;
}
