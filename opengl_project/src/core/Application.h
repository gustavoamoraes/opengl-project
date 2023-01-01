#pragma once

#include <memory>
#include <functional>

#include "Window.h"
#include "Gui.h"
#include "scenes/Scene.h"

//#include "Event.h"

class Application
{
	public:
		Application(const std::string& name);
		~Application();
			
		static inline Application* GetInstance() { return s_Instance; };

		void Run();
		void OnWindowClosed();

		Window& GetWindow();
		Scene* m_CurrentScene = nullptr;
	private:
		static Application* s_Instance;
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Gui> m_Gui;

		bool m_Running = true;
};