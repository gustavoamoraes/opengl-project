#pragma once

#include "Scene.h"

//Game Objects
#include "Chunck.h"
#include "CameraController.h"

class MainScene : public Scene
{
public:

	MainScene()
	{	
		Chunck* chunck = new Chunck();
		CameraController* camera = new CameraController();

		AddEntity(chunck);
		AddEntity(camera);
	};
};