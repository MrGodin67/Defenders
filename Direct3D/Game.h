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
#include "SoundManager.h"
#include "Bases.h"
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
	ItemsSelector::Item selected_Base = ItemsSelector::Item();
	std::vector<Base> m_bases;
	std::unique_ptr<SoundManager> m_soundFX;
	std::unique_ptr<MainMenu> m_MainMenu;
	std::unique_ptr<SpriteSheet> m_gameMapPieces;
	std::unique_ptr<SpriteSheet> m_gamePieces;
	std::unique_ptr<SpriteSheet> m_gameBases;
	std::unique_ptr<ItemsSelector> m_itemSelector;
	std::vector<std::unique_ptr<MoveableObject>> m_moveableObj;
	//std::unordered_map<std::string, SoundEffect> m_soundFX;
	_GameState m_gameState = _GameState::start;
private:
	void LoadSounds();
	void Move();
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
