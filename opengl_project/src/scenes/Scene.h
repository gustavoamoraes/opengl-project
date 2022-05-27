#pragma once

#include <string>
#include <vector>
#include <functional>
namespace scene
{
	class Scene
	{
		public:
			Scene() {};
			virtual ~Scene() {};

			virtual void OnUpdate() {};
			virtual void OnRender() {};
			virtual void OnImGUIRender() {};
	};

	class SceneMenu : public Scene
	{
		public:
			SceneMenu(Scene*& firstScene);
			~SceneMenu() {};

			void OnImGUIRender();
			void OnRender();

			template<typename T>
			void AddScene(const std::string& name)
			{
				m_Scenes.push_back(std::make_pair(name, []() { return new T(); }));
			}

			Scene*& m_CurrentScene;

		private:
			std::vector<std::pair<std::string, std::function<Scene*()>>> m_Scenes;
	};
}