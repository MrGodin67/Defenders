#pragma once
#include "Graphics.h"
#include "InputManager.h"
#include <memory>
#include "WorldGrid.h"
#include "Camera.h"
#include "MoveableObject.h"

#include "MainMenu.h"
#include "StartMenu.h"
#include "SoundEffect.h"

#include "SoundManager.h"

#include "GameState.h"
#include "EntityManager.h"
#include "FileWriter.h"
#include "TextureManager.h"
#include "VecRect.h"

#include "BaseController.h"

class Game
{
	Vec2i m_mousePt = Vec2i(0, 0);
	class Direct3DWindow& window;
	Graphics gfx;
	
	void EndApp();
	Camera m_cam;
	WorldGrid m_grid;
	InputManager& m_input;
	
	std::unique_ptr<SoundManager> m_soundFX;
	std::unique_ptr<MainMenu> m_MainMenu;
	std::unique_ptr<UnitManager> m_unitManager;
	std::unique_ptr<TextureManager> m_textureManager;
	std::unique_ptr<BaseController> m_controller;
	FileHandler testFile;
	Extents<float> pos;
	std::unordered_map<std::string, std::unique_ptr<MenuInterface>> m_menus;
	_GameState m_gameState = _GameState::paused;
private:
	void LoadSounds();
	void Move();
	void LoadUnits();
	void HandleUserEvents(Mouse::Event mouse);
public:
	Game(class Direct3DWindow& wnd);
	bool Play(const float& deltaTime);
	HRESULT ConstructScene(const float& deltaTime);
	HRESULT RenderScene();
	
	////////////////////////////////////
	// LOGIC
	////////////////////////////////////

private:
	
	void FindPath();
	bool LoadMap(const int& index, const std::wstring textureFilename);
	bool LoadImages();
};
