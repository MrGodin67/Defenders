#include "Game.h"
#include "Direct3DWindow.h"


void Game::EndApp()
{
	PostQuitMessage(0);
}

void Game::LoadSounds()
{
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
	LoadMap(0, L"media\\test.png");
	m_cam.ConfineToMap(RectF(0.0f, 0.0f, m_grid.Width(), m_grid.Height()));
	
	m_MainMenu = std::make_unique<MainMenu>(Vec2f((float)window.ScreenWidth() / 2, (float)window.ScreenHeight() / 2), 800.0f, 600.0f);
	
	
	m_itemSelector = std::make_unique<ItemsSelector>(m_gamePieces.get(),
		(float)window.ScreenWidth(), (float)window.ScreenHeight(), 128.0f);
	
	
	float speed = 52.0f;
	m_moveableObj.push_back(std::make_unique<MoveableObject>(m_gamePieces.get(), 1, 64.0f, 64.0f, speed, Vec2f(5.0f*64.0f, 5.0f* 64.0f)));
	
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
		if (input.MouseLeftClick())
		{
			float d = 0.0f;
			m_soundFX["newitems"].Play(d, 1.0f);
			std::vector<Vec2f> pts;
			Vec2f mp = Vec2f((float)input.GetMousePos().x, (float)input.GetMousePos().y);
			mp = m_cam.ConvertToWorldSpace(mp);
			Vec2f s = m_grid.GetCellIndex(m_moveableObj[0]->GetCenter());
			Vec2f e = m_grid.GetCellIndex(mp);
			if (m_grid.FindPath(s, e, pts))
				m_moveableObj[0]->SetWaypoints(pts);
             
		

		}
		m_moveableObj[0]->Update(deltaTime);
		m_moveableObj[0]->TransformToCamera(m_cam.GetPos());
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
		m_itemSelector->Draw(gfx);
		m_moveableObj[0]->Draw(gfx);
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
	m_gamePieces = std::make_unique<SpriteSheet>(L"media\\test.png", 64.0f, 64.0f);
	m_gameBases = std::make_unique<SpriteSheet>(L"media\\bases.png", 128.0f, 128.0f);
	return false;
}
