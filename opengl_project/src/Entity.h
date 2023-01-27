#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "Scene.h"

class Entity
{
public:
	virtual void Update();
	virtual void Start();
	virtual void SetActive(bool active);

	Scene* m_MyScene;
	bool m_Active = true;
};

#else
class Entity;
#endif
