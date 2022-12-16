#pragma once

#include "Scene.h"

//Game Objects
#include "Player.h"
#include "CameraController.h"

class MainScene : public Scene
{
public:

	MainScene()
	{	
		Player* player = new Player();
		CameraController* camera = new CameraController();

		AddEntity(player);
		AddEntity(camera);
	};
};