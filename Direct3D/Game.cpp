#include "Game.h"
#include "Direct3DWindow.h"




Game::Game(Direct3DWindow & wnd)
	:
	window(wnd),
	gfx(wnd.ScreenWidth(),wnd.ScreenHeight(),wnd.WindowHandle(),
		true, FULL_SCREEN,1000.0f,0.01f),
	m_cam((float)wnd.ScreenWidth(), (float)wnd.ScreenHeight()),
	m_grid(m_cam),
	m_input(wnd.m_input)
{
	LoadSounds();
	LoadImages();
	LoadMap(0, L"media\\map_pieces.png");
	LoadUnits();
	m_cam.ConfineToMap(RectF(0.0f, 0.0f, m_grid.Width(), m_grid.Height()));
	m_MainMenu = std::make_unique<MainMenu>(Vec2f((float)window.ScreenWidth() / 2, (float)window.ScreenHeight() / 2), 800.0f, 600.0f);
	
	m_menus["main"] = std::make_unique<MainMenu>(Vec2f((float)window.ScreenWidth() / 2, (float)window.ScreenHeight() / 2), 800.0f, 600.0f);
	m_menus["start"] = std::make_unique<StartMenu>(Vec2f((float)window.ScreenWidth() / 2, (float)window.ScreenHeight() / 2), 800.0f, 600.0f);

	testFile.WriteFile();
	testFile.ReadFile();

}

bool Game::Play(const float& deltaTime)
{
	HRESULT hr;
	if (FAILED(hr = ConstructScene(deltaTime))) 
	{ return false; }
	if (FAILED(hr = RenderScene())) { return false; }
	return true;
}

HRESULT Game::ConstructScene(const float& deltaTime)
{
	
	Mouse::Event e_mouse = m_input.GetMouseEvent();
	Keyboard::Event e_kbd = m_input.GetKeyboardEvent();
	if(e_mouse.IsValid())
	   m_mousePt = Vec2i(e_mouse.GetPosX(), e_mouse.GetPosY());
	
	switch (m_gameState)
	{
	case _GameState::running:
	{		
		HandleUserEvents(e_mouse, e_kbd);
		if(m_itemSelector->BaseItemSelected())
			m_grid.SetBasePlacementTiles(m_mousePt);

		m_unitManager->Update(deltaTime, e_mouse,e_kbd);
		m_baseManager->Update(deltaTime);
	}
		break;
	case _GameState::paused:
		m_menus["main"]->OnMouseOver(m_mousePt);
		if (e_mouse.GetType() == Mouse::Event::LPress)
		{

			int result = m_menus["main"]->OnMouseClick(Vec2i(m_mousePt));
			if (result != -1)
			{
				switch (result)
				{
				case 0:
					m_gameState = _GameState::start;
				break;
				case 1:
					m_gameState = _GameState::running;
					m_menus["main"]->GameStarted(true);
					break;
				case 2:
					EndApp();
					break;

				}
			}

		}
		break;
	case _GameState::start:
		
		m_menus["start"]->OnMouseOver(m_mousePt);
		if (e_mouse.GetType() == Mouse::Event::LPress)
		{
			
			int result = m_menus["start"]->OnMouseClick(Vec2i(m_mousePt));
			if (result != -1)
			{
				switch (result)
				{
				case 0:
					m_gameState = _GameState::running;
					m_menus["main"]->GameStarted(true);
					break;
				case 1:
					m_gameState = _GameState::paused;
					break;
				case 2:
					EndApp();
					break;

				}
			}
			
		}
		break;
	}
	return S_OK;
}

HRESULT Game::RenderScene()
{
	HRESULT hr;
	hr = gfx.BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	if (FAILED(hr)) { return hr; }
	switch (m_gameState)
	{
	case _GameState::running:
		m_grid.Draw(gfx, m_cam.GetViewFrame(),m_itemSelector->CurrentSelectedBase());
		m_baseManager->Draw(gfx,m_cam);
		m_unitManager->Draw(gfx);
		// draw last
		m_itemSelector->Draw(gfx);
		
		
		break;
	case _GameState::paused:
		m_menus["main"]->Draw(gfx);
		break;
	case _GameState::start:
		m_menus["start"]->Draw(gfx);
		break;
	}
	hr = gfx.EndScene();
	if (FAILED(hr)) { return hr; }
	return hr;
}

void Game::FindPath()
{
	
}

bool Game::LoadMap(const int & index,const std::wstring textureFilename)
{
	std::string filename = "map" + std::to_string(index) + ".txt";
	m_grid.LoadMap(filename, textureFilename);
	return false;
}

bool Game::LoadImages()
{
	m_textureManager = std::make_unique<TextureManager>();
	std::vector<TextureManager::ImageData> data;
	data.emplace_back("bases", L"media\\bases.png", 128.0f, 128.0f);
	data.emplace_back("map", L"media\\map_pieces.png", 64.0f, 64.0f);
	data.emplace_back("player_units", L"media\\playerunits.png", 64.0f, 64.0f);
	data.emplace_back("menuBack1", L"media\\menuback.png", 800.0f, 600.0f);
	data.emplace_back("menuBack2", L"media\\menuback2.png", 800.0f, 600.0f);
	data.emplace_back("hud", L"media\\hud.png", 256.0f, 128.0f);
	data.emplace_back("worldmap", L"media\\worldMap.png", 512.0f, 512.0f);
	m_textureManager->LoadImages(data);

	Locator::SetImageManager(m_textureManager.get());
	m_baseManager = std::make_unique<BaseManager>();
	m_gameMapPieces = std::make_unique<SpriteSheet>(L"media\\map_pieces.png", 64.0f, 64.0f);
	m_gamePieces = std::make_unique<SpriteSheet>(L"media\\test.png", 32.0f, 32.0f);
	m_itemSelector = std::make_unique<ItemsSelector>(Vec2f((float)window.ScreenWidth(), (float)window.ScreenHeight()), 128.0f);
	
	
	return true;
}
void Game::EndApp()
{
	PostQuitMessage(0);
}

void Game::LoadSounds()
{
	m_soundFX = std::make_unique<SoundManager>();
	m_soundFX->AddSound("notenoughcredit", L"media\\notenoughcredits.wav");
	m_soundFX->AddSound("notenoughcredit", L"media\\notenoughcredits.wav");
	m_soundFX->AddSound("basedestroyed", L"media\\basedestroyed.wav");
	m_soundFX->AddSound("hostiledestroyed", L"media\\hostiledestroyed.wav");
	m_soundFX->AddSound("hostilelocated", L"media\\hostileslocated.wav");
	m_soundFX->AddSound("newitems", L"media\\newitems.wav");
	m_soundFX->AddSound("baseunderattack", L"media\\baseunderattack.wav");
	m_soundFX->AddSound("constructionstarted", L"media\\constuctionstarted.wav");
	m_soundFX->AddSound("constructioncomplete", L"media\\constuctionCompleted.wav");
	m_soundFX->AddSound("unitrepaired", L"media\\unitrepaired.wav");
	m_soundFX->AddSound("newunitsavailable", L"media\\newunit.wav");
	m_soundFX->AddSound("tick", L"media\\tick.wav");
	m_soundFX->AddSound("select", L"media\\select.wav");
	Locator::SetSoundManager(m_soundFX.get());

}

void Game::Move()
{
	
}

void Game::LoadUnits()
{
	m_unitManager = std::make_unique<UnitManager>(m_input,m_grid,m_cam,L"media\\playerUnits.png");
	for (int r = 4; r < 8; r++)
	{
		for (int c = 4; c < 8; c++)
		{
			if( c == 4)
			  m_unitManager->AddPlayerUnit(drone, Vec2i(r, c));
			if(c == 5)
				m_unitManager->AddPlayerUnit(fighter, Vec2i(r, c));
			if ( c == 6)
				m_unitManager->AddPlayerUnit(radar, Vec2i(r, c));
			if (c == 7)
				m_unitManager->AddPlayerUnit(artillary, Vec2i(r, c));

		}
	}
	
	
}

void Game::HandleUserEvents(Mouse::Event mouse, Keyboard::Event kbd)
{
	if (m_input.AnyKeyPressed())
	{
		Vec2f scroll(0.0f, 0.0f);
		if(m_input.KeyPress('A'))
			scroll.x = -10.0f;
		if(m_input.KeyPress('D'))
			scroll.x = 10.0f;
		if(m_input.KeyPress('W'))
			scroll.y = -10.0f;
		if(m_input.KeyPress('S'))
			scroll.y = 10.0f ;

		if (m_input.KeyPress(VK_ESCAPE))
		{
			Locator::SoundEngine->Play("select", 0.5f);
			m_gameState = _GameState::paused;
		}

		
		m_cam.Scroll(scroll);
	}
	
	if (mouse.GetType() == Mouse::Event::RPress)
	{
		m_itemSelector->BaseItemSelected(false);
		m_grid.FlushPlacementTiles();
	}
	if (mouse.GetType() == Mouse::Event::LPress)
	{
		if (m_input.KeyPress(VK_SHIFT))
		{
			m_baseManager->OnMouseClick(m_mousePt);
		}
		if (m_itemSelector->BaseItemSelected())
		{
			Tile tile;
			if (m_grid.SetBase(Vec2i(m_cam.ConvertToWorldSpace(m_mousePt)), tile))
			{
				m_baseManager->AddBase(Vec2i(m_cam.ConvertToWorldSpace(tile.GetWorldPosition())), m_itemSelector->CurrentSelectedBase()->ImageIndex());
				m_itemSelector->BaseItemSelected(false);
				m_soundFX->Play("constructionstarted");
			}


		}

		m_itemSelector->OnMouseClick(m_mousePt, m_input.KeyPress(VK_CONTROL));
		
	}
	
}
