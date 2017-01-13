#include "Game.h"
#include "Direct3DWindow.h"


void Game::EndApp()
{
	PostQuitMessage(0);
}

void Game::LoadSounds()
{
	m_soundFX = std::make_unique<SoundManager>();

	m_soundFX->AddSound("notenoughcredit", L"media\\notenoughcredits.wav");
	m_soundFX->AddSound("notenoughcredit", L"media\\notenoughcredits.wav" );
	m_soundFX->AddSound("basedestroyed",L"media\\basedestroyed.wav" );
	m_soundFX->AddSound("hostiledestroyed", L"media\\hostiledestroyed.wav" );
	m_soundFX->AddSound("hostilelocated", L"media\\hostileslocated.wav" );
	m_soundFX->AddSound("newitems", L"media\\newitems.wav" );
	m_soundFX->AddSound("baseunderattack", L"media\\baseunderattack.wav" );
	m_soundFX->AddSound("constructionstarted", L"media\\constuctionstarted.wav" );
	m_soundFX->AddSound("constructioncomplete", L"media\\constuctionCompleted.wav" );
	m_soundFX->AddSound("unitrepaired", L"media\\unitrepaired.wav" );
	m_soundFX->AddSound("newunitsavailable", L"media\\newunit.wav" );
	Locator::SetSoundManager(m_soundFX.get());
	/*
	m_soundFX["notenoughcredit"] = SoundEffect({ L"media\\notenoughcredits.wav" });
	m_soundFX["basedestroyed"] = SoundEffect({ L"media\\basedestroyed.wav" });
	m_soundFX["hostiledestroyed"] = SoundEffect({ L"media\\hostiledestroyed.wav" });
	m_soundFX["hostilelocated"] = SoundEffect({ L"media\\hostileslocated.wav" });
	m_soundFX["newitems"] = SoundEffect({ L"media\\newitems.wav" });
	m_soundFX["baseunderattack"] = SoundEffect({ L"media\\baseunderattack.wav" });
	m_soundFX["constructionstarted"] = SoundEffect({ L"media\\constuctionstarted.wav" });
	m_soundFX["constructioncomplete"] = SoundEffect({ L"media\\constuctionCompleted.wav" });
	m_soundFX["unitrepaired"] = SoundEffect({ L"media\\unitrepaired.wav" });
	m_soundFX["newunitsavailable"] = SoundEffect({ L"media\\newunit.wav" });
	*/
}

void Game::Move()
{
	std::vector<Vec2f> pts;
	Vec2f mp = Vec2f((float)input.GetMousePos().x, (float)input.GetMousePos().y);
	mp = m_cam.ConvertToWorldSpace(mp);
	Vec2i s = m_grid.GetCellIndex(m_moveableObj[0]->GetCenter());
	Vec2i e = m_grid.GetCellIndex(mp);
	
	if (m_grid.FindPath(s,e, pts))
		m_moveableObj[0]->SetWaypoints(pts);
}

Game::Game(Direct3DWindow & wnd)
	:
	window(wnd),
	input(window.m_mouse,window.m_keyboard),
	gfx(wnd.ScreenWidth(),wnd.ScreenHeight(),wnd.WindowHandle(),
		true, FULL_SCREEN,1000.0f,0.01f),
	m_cam((float)wnd.ScreenWidth(), (float)wnd.ScreenHeight() - 128),
	m_grid(m_cam)
{
	LoadSounds();
	LoadImages();
	LoadMap(0, L"media\\map_pieces.png");
	m_cam.ConfineToMap(RectF(0.0f, 0.0f, m_grid.Width(), m_grid.Height()));
	m_MainMenu = std::make_unique<MainMenu>(Vec2f((float)window.ScreenWidth() / 2, (float)window.ScreenHeight() / 2), 800.0f, 600.0f);
	m_itemSelector = std::make_unique<ItemsSelector>(Vec2f((float)window.ScreenWidth(), (float)window.ScreenHeight()), 128.0f);
	m_itemSelector->SetSprites("base", m_gameBases.get());
	float speed = 92.0f;
	m_moveableObj.push_back(std::make_unique<MoveableObject>(m_gamePieces.get(), 0, 48.0f, 48.0f, speed, Vec2f(5.0f*64.0f, 5.0f* 64.0f)));
	
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
	
	switch (m_gameState)
	{
	case _GameState::running:
	{
		

		if (input.KeyPress(VK_ESCAPE))
			m_gameState = _GameState::paused;

		Vec2f scroll(0.0f, 0.0f);
		
		

		if (input.KeyPress('A'))
		{
			scroll.x = -10.0f;
		}
		if (input.KeyPress('D'))
		{
			scroll.x = 10.0f;

		}
		if (input.KeyPress('W'))
		{
			scroll.y = -10.0f;
		}
		if (input.KeyPress('S'))
		{
			scroll.y = 10.0f;
		}
		m_cam.Scroll(scroll);
		if (input.MouseMiddleClick())
		{
			float d = 0.0f;
			
		}
		
			
		
		if (input.MouseRightClick())
		{
			Move();
		}

		if (input.MouseLeftClick())
		{
			if (m_itemSelector->BaseItemSelected() && selected_Base.selected)
			{
					Tile tile;
					if (m_grid.SetBase(Vec2i(input.GetMousePos()+m_cam.GetPos()), tile))
					{

						m_bases.emplace_back(m_gameBases.get(), selected_Base.imageIndex, 128.0f, 128.0f, tile.GetWorldPosition(),
							15.0f);
						m_itemSelector->BaseItemSelected(false);
					}
					
				
			}
			
			if (m_itemSelector->OnMouseClick(input.GetMousePos(), selected_Base))
			{
				selected_Base.selected = true;
			}
			else
			{
				selected_Base.selected = false;
			}
     	}
		if(m_itemSelector->BaseItemSelected())
			m_grid.SetBasePlacementTiles(input.GetMousePos());

		m_moveableObj[0]->Update(deltaTime);
		m_moveableObj[0]->TransformToCamera(m_cam.GetPos());
		for (auto& base : m_bases)
			base.Update(deltaTime);
	}
		break;
	case _GameState::paused:
	case _GameState::start:
		
			
		if (input.MouseLeftClick())
		{
			int result = m_MainMenu->OnMouseClick(input.GetMousePos().x, input.GetMousePos().y);
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
		m_moveableObj[0]->Draw(gfx);

		for (auto& base : m_bases)
			base.Draw(gfx,m_cam);

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
	m_grid.LoadMap("map0.txt", textureFilename);
	return false;
}

bool Game::LoadImages()
{
	m_gameMapPieces = std::make_unique<SpriteSheet>(L"media\\map_pieces.png", 64.0f, 64.0f);
	m_gameBases = std::make_unique<SpriteSheet>(L"media\\bases.png", 128.0f, 128.0f);
	m_gamePieces = std::make_unique<SpriteSheet>(L"media\\test.png", 32.0f, 32.0f);
	return false;
}
