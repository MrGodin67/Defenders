#pragma once
#include "Graphics.h"
#include "InputManager.h"
#include <memory>
#include "WorldGrid.h"
#include "Camera.h"
#include "MoveableObject.h"
#include "SpriteSheet.h"
#include "MainMenu.h"
#include "SoundEffect.h"
#include "ItemSelector.h"
enum class _GameState
{
	start,
	running,
	paused
};
class Game
{
	class Direct3DWindow& window;
	Graphics gfx;
	InputManager input;
	void EndApp();
	Camera m_cam;
	WorldGrid m_grid;
	std::mt19937 rng;
	std::unique_ptr<MainMenu> m_MainMenu;
	std::unique_ptr<SpriteSheet> m_gamePieces;
	std::unique_ptr<ItemsSelector> m_itemSelector;
	std::vector<std::unique_ptr<MoveableObject>> m_moveableObj;
	std::unordered_map<std::string, SoundEffect> m_soundFX;
	_GameState m_gameState = _GameState::start;
private:
	void LoadSounds();
public:
	Game(class Direct3DWindow& wnd);
	bool Play(const float& deltaTime);
	HRESULT ConstructScene(const float& deltaTime);
	HRESULT RenderScene();
	
	////////////////////////////////////
	// LOGIC
	////////////////////////////////////

private:
	XMFLOAT2 m_ScreenSize;
	XMFLOAT2 m_ScreenCenter;
	void FindPath();
};
