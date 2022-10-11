#pragma once

#include <string>
//#include "Scene.h"

class Entity
{
public:
	virtual void Update();
	virtual void Setup();

	bool m_Active;
	//std::string tag;
private:
	//Scene* m_MyScene;
};