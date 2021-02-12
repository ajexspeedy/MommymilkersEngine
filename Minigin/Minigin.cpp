#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "Component.h"
#include "RenderComponent.h"
#include "TextComponent.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	RenderComponent render_component{"background.jpg"};

	auto game_object1 = new GameObject(new RenderComponent("background.jpg"),"Background");
	scene.Add(game_object1);

	auto game_object2 = new GameObject(new RenderComponent("logo.png", 216.f, 180.f),"Logo");
	scene.Add(game_object2);

	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto text_object = new GameObject(new TextComponent("Programming 4 Assignment", font),"Text");
	text_object->SetPosition(80, 50);
	scene.Add(text_object);

	const auto fps_font = ResourceManager::GetInstance().LoadFont("Comic_Sans.otf", 18);
	auto fps_counter = new GameObject(new TextComponent("FPS: 0", fps_font),"FPS_Counter");
	scene.Add(fps_counter);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& timer = TimeManager::GetInstance();
		
		bool doContinue = true;
		float lag = 0.0f;
		while (doContinue)
		{
			timer.CalculateDeltaTime();
			lag += timer.GetDeltaTime();
			doContinue = input.ProcessInput();
			while(lag >= MsPerFrame)
			{
				sceneManager.Update();
				lag -= MsPerFrame;
			}
			renderer.Render();
			
		
		}
	}

	Cleanup();
}
