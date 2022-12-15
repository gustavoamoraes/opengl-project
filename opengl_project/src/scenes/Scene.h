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

		void AddEntity(Entity* entiry);

		Camera m_MainCamera;

private:
	std::vector<Entity*> m_Entities;
};

#else
class Scene;
#endif
