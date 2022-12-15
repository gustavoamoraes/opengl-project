#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "Scene.h"

class Entity
{
public:
	virtual void Update();
	virtual void Setup();

	bool m_Active = true;
	Scene* m_MyScene;
};

#else
class Entity;
#endif
