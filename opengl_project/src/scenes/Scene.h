#pragma once

#include <string>
#include <vector>
#include <functional>
#include "Entity.h"

class Scene
{
	public:
		Scene() {};
		~Scene() {};

		virtual void OnUpdate();
		virtual void OnImGUIRender() {};

		void AddEntity(Entity* entiry);
		//Camera mainCamera;

private:
	std::vector<Entity*> m_Entities;
};
