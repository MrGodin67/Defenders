#include "Game.h"
#include "Direct3DWindow.h"




Game::Game(Direct3DWindow & wnd)
	:
	window(wnd),
	m_input(window.m_mouse,window.m_keyboard),
	gfx(wnd.ScreenWidth(),wnd.ScreenHeight(),wnd.WindowHandle(),
		true, FULL_SCREEN,1000.0f,0.01f),
	m_cam((float)wnd.ScreenWidth(), (float)wnd.ScreenHeight() - 128),
	m_grid(m_cam)
{
	LoadSounds();
	LoadImages();
	LoadMap(0, L"media\\map_pieces.png");
	LoadUnits();
	m_cam.ConfineToMap(RectF(0.0f, 0.0f, m_grid.Width(), m_grid.Height()));
	m_MainMenu = std::make_unique<MainMenu>(Vec2f((float)window.ScreenWidth() / 2, (float)window.ScreenHeight() / 2), 800.0f, 600.0f);
	
	

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
	Vec2i mousePt = m_input.GetMousePos();
	switch (m_gameState)
	{
	case _GameState::running:
	{
		

		if (m_input.KeyPress(VK_ESCAPE))
			m_gameState = _GameState::paused;

		Vec2f scroll(0.0f, 0.0f);
		
		

		if (m_input.KeyPress('A'))
		{
			scroll.x = -10.0f;
		}
		if (m_input.KeyPress('D'))
		{
			scroll.x = 10.0f;

		}
		if (m_input.KeyPress('W'))
		{
			scroll.y = -10.0f;
		}
		if (m_input.KeyPress('S'))
		{
			scroll.y = 10.0f;
		}
		m_cam.Scroll(scroll);
		if (m_input.MouseMiddleClick())
		{
			float d = 0.0f;
			
		}
		
		m_unitManager->Update(deltaTime);
			
		
	

		if (m_input.MouseLeftClick())
		{
			if (m_input.KeyPress(VK_SHIFT))
			{
				m_baseManager->OnMouseClick(mousePt);
			}
			if (m_itemSelector->BaseItemSelected() && selected_Base.selected)
			{
					Tile tile;
					if (m_grid.SetBase(Vec2i(m_input.GetMousePos()+m_cam.GetPos()), tile))
					{
						m_baseManager->AddBase(tile.GetWorldPosition(), selected_Base.imageIndex);
				    	m_itemSelector->BaseItemSelected(false);
					}
					
				
			}
			
			if (m_itemSelector->OnMouseClick(m_input.GetMousePos(), selected_Base))
			{
				selected_Base.selected = true;
			}
			else
			{
				selected_Base.selected = false;
			}
     	}
		if(m_itemSelector->BaseItemSelected())
			m_grid.SetBasePlacementTiles(m_input.GetMousePos());

		
		m_baseManager->Update(deltaTime);
	}
		break;
	case _GameState::paused:
	case _GameState::start:
		
			
		if (m_input.MouseLeftClick())
		{
			
			int result = m_MainMenu->OnMouseClick(m_input.GetMousePos().x, m_input.GetMousePos().y);
			if (result != -1)
			{
				switch (result)
				{
				case 0:
				case 1:
					m_gameState = _GameState::running;
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
		m_grid.Draw(gfx, m_cam.GetViewFrame());
		m_baseManager->Draw(gfx,m_cam);
		m_unitManager->Draw(gfx);
		// draw last
		m_itemSelector->Draw(gfx);
		
		
		break;
	case _GameState::paused:
	case _GameState::start:
		m_MainMenu->Draw(gfx);
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
	m_baseManager = std::make_unique<BaseManager>(L"media\\bases.png",128.0f,128.0f);
	m_gameMapPieces = std::make_unique<SpriteSheet>(L"media\\map_pieces.png", 64.0f, 64.0f);
	m_gamePieces = std::make_unique<SpriteSheet>(L"media\\test.png", 32.0f, 32.0f);
	m_itemSelector = std::make_unique<ItemsSelector>(Vec2f((float)window.ScreenWidth(), (float)window.ScreenHeight()), 128.0f);
	m_itemSelector->SetSprites("base", m_baseManager->Images());
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
