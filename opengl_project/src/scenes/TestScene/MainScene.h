#pragma once

#include "Scene.h"

//Game Objects
#include "Player.h"

class MainScene : public Scene
{
public:

	MainScene()
	{	
		Player* player = new Player();
		player->m_Active = true;
		AddEntity(player);
	};
};