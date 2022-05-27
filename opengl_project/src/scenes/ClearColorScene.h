#pragma once

#include "Scene.h"

namespace scene
{
	class ClearColorScene : public Scene
	{
		public:
			ClearColorScene();
			~ClearColorScene();

			void OnUpdate() override;
			void OnRender() override;
			void OnImGUIRender() override;

		private:
			float color[4];
	};
	
}