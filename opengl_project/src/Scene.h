#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include <functional>

#include "Entity.h"
#include "Camera.h"

class Scene
{
	public:
		Scene() {};
		~Scene() {};

		virtual void OnUpdate();

		virtual void OnImGUIRender() {};

		//template<class EntityClass>
		//void CreateNewEntities();
		//std::vector <std::function<Entity* ()>> m_EntitiesToAdd;

		void AddEntity(Entity* entity);
		void OnNewEntities();

		Camera m_MainCamera;

private:
	std::vector<Entity*> m_Entities;
	std::vector<Entity*> m_EntitiesToStart;
	bool m_NewEntitiesToStart;
};

#else
class Scene;
#endif
