#pragma once

#include "Scene.h"

//Game Objects
#include "ChunckManager.h"
#include "CameraController.h"

class MainScene : public Scene
{
public:

	MainScene()
	{	
		ChunckManager* chunckManager = ChunckManager::instance();
		CameraController* camera = new CameraController();

		AddEntity(camera);
		AddEntity(chunckManager);
	};
};