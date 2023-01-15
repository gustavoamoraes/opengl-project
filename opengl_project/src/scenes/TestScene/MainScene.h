#pragma once

#include "BlockAtlas.h"

//Game Objects
#include "ChunckManager.h"
#include "CameraController.h"

class MainScene : public Scene
{
public:

	MainScene()
	{	
		Setup(); 
	};

	void Setup()
	{
		BlockAtlas::instance()->GenerateBlockAtlas();

		ChunckManager* chunckManager = ChunckManager::instance();
		CameraController* camera = new CameraController();

		AddEntity(chunckManager);
		AddEntity(camera);
	}
};