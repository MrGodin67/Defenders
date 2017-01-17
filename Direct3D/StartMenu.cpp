#include "StartMenu.h"
#include "Graphics.h"


StartMenu::StartMenu(Vec2f screenCenter, float width, float height)
{
	border = RectF(screenCenter.x - (width * 0.5f),
		screenCenter.y - (height * 0.5f),
		screenCenter.x + (width * 0.5f),
		screenCenter.y + (height * 0.5f));
	std::vector<WCHAR*> text;
	float p2x = 0.0f;
	float p2y = 0.0f;
	float px = 440.0f;
	float py = 160.0f;
	float inc1 = 90.0f;
	text.push_back(L"Drone : fast scouting\nLimited offensive, collect tech");
	text.push_back(L"Fighter : main battle uint\nBest offensive");
	text.push_back(L"Artillary : slow moving\nIncreased range");
	text.push_back(L"Radar : slow moving\nNo offence, Enemy detection");
	for (int c = 0; c < 4; c++)
	{
		UnitRects[c].pos = { px,py,px + 64.0f,py + 64.0f };
		
		py += inc1;
		UnitRects[c].clip = { p2x,p2y,p2x + 64.0f,p2y + 64.0f };
		p2x += 64.0f;
		UnitRects[c].text = text[c];
	}
	py = 160.0f;
	inc1 = 106.0f;
	text.clear();
	text.push_back(L"Command Post : Deploy drones.");
	text.push_back(L"Factory : Build Fighters\nRadar, Artillary.");
	text.push_back(L"Technology : Build new Tech from scavanged\ntech.");
	text.push_back(L"Repair Facility : Repair units.");
	
	for (int c = 0; c < 4; c++)
	{
		BaseRects[c].pos = { px,py,px + 96.0f,py + 96.0f };

		py += inc1;
		
		BaseRects[c].text = text[c];
	}
	BaseRects[0].clip = { 0.0f,0.0f,128.0f,128.0f };
	BaseRects[1].clip = { 128.0f,0.0f,256.0f,128.0f };
	BaseRects[2].clip = { 0.0f,128.0f,128.0f,256.0f };
	BaseRects[3].clip = { 128.0f,128.0f,256.0f,256.0f };
	p2x += 64.0f;
	float w = 160.0f;
	float h = 32.0f;
	float x = border.left + 80.0f;
	float y = border.top + 80.0f;
	float inc = 34.0f;
	text.clear();
	text.push_back(L"Maps");
	text.push_back(L"Units");
	text.push_back(L"Bases");
	text.push_back(L"Exit");
	text.push_back(L"Dummy");
	text.push_back(L"Dummy");
	for (int c = 0; c < numButtons; c++)
	{
		Buttons[c].frame = RectF(x, y, x + w, y + h);
		Buttons[c].id = c;
		Buttons[c].text = text[c];
		y += inc;
		
	}

	
	m_textures.push_back(std::make_unique<D2D1Texture>(Locator::RenderTarget, L"media\\menuBack2.png"));
	assert(m_textures.back());
	m_textures.push_back(std::make_unique<D2D1Texture>(Locator::RenderTarget, L"media\\playerunits.png"));
	assert(m_textures.back());
	m_textures.push_back(std::make_unique<D2D1Texture>(Locator::RenderTarget, L"media\\bases.png"));
	assert(m_textures.back());
}


StartMenu::~StartMenu()
{
}

void StartMenu::Draw(Graphics & gfx)
{
	gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), border.ToD2D(), m_textures[0]->GetBitmap());
	gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), border.ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
	gfx.DrawFilledScreenRectangle(border.ToD2D(), D2D1::ColorF(0.2f, 0.2f, 0.9f, 0.20f));
	D2D1_COLOR_F colour = D2D1::ColorF(0.0f, 1.0f, 0.0f, 1.25f);

	for (int c = 0; c < numButtons; c++)
	{
		RectF textRect = RectF(Buttons[c].frame.left + 4.0f,
			Buttons[c].frame.top, Buttons[c].frame.right, Buttons[c].frame.bottom);
		
		if (Buttons[c].drawFrame)
		{
			gfx.DrawFilledScreenRectangle(Buttons[c].frame.ToD2D(), D2D1::ColorF(0.0f, 1.0f, 0.0f, 0.25f));
			colour = D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f);
			switch (c)
			{
			case 0:
				DrawMap(gfx);
				break;
			case 1:
				DrawUnits(gfx);
				break;
			case 2:
				DrawBases(gfx);
			}
		}
		else
		{
			colour = D2D1::ColorF(0.0f, 1.0f, 0.0f, 1.25f);
		}
		Locator::TextManager->GetFormat("Tahoma22")->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		gfx.RenderText(Buttons[c].text, Locator::TextManager->GetFormat("Tahoma22"), textRect.ToD2D(),colour);

	}


	
}

int StartMenu::OnMouseClick(Vec2i& mouse)
{
	for (int c = 0; c < numButtons; c++)
	{

		if (Buttons[c].frame.Contains(mouse))
		{
			Locator::SoundEngine->Play("select", 1.25f);
			return Buttons[c].id;
		}

	}

	return -1;
}

int StartMenu::OnMouseOver(Vec2i & mouse)
{
	
	Buttons[0].drawFrame = Buttons[1].drawFrame = Buttons[2].drawFrame = 
		Buttons[3].drawFrame = Buttons[4].drawFrame = Buttons[5].drawFrame=false;
	for (int c = 0; c < numButtons; c++)
	{

		if (Buttons[c].frame.Contains(mouse))
		{
			if (lastOver != c)
				Locator::SoundEngine->Play("tick", 0.25f);
			Buttons[c].drawFrame = true;
			lastOver = c;
			return 0;
		}

	}
	lastOver = -1;
	return 0;
}

void StartMenu::DrawMap(Graphics & gfx)
{
	RectF frm = { 440.0f,160.0f,860.0f,500.0f };
	D2D1_COLOR_F colour = D2D1::ColorF(0.0f, 1.0f, 0.0f, 1.25f);

	Locator::TextManager->GetFormat("Tahoma22")->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	gfx.RenderText(L"(1) Outpost D-11, Initial invasion\n(2) Outpost D-32, beat them back\n(3) Outpost E-37, take the offensive", Locator::TextManager->GetFormat("Tahoma22"), frm.ToD2D(), colour);
	
}

void StartMenu::DrawUnits(Graphics & gfx)
{
	RectF frm = { 440.0f,160.0f,860.0f,500.0f };
	D2D1_COLOR_F colour = D2D1::ColorF(0.0f, 1.0f, 0.0f, 1.25f);
	Locator::TextManager->GetFormat("Tahoma22")->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	for (int c = 0; c < 4; c++)
	{
		frm = UnitRects[c].pos; frm.left += 70.0f; frm.right += 290.0f;
		gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), UnitRects[c].pos.ToD2D(), m_textures[1]->GetBitmap(), &UnitRects[c].clip.ToD2D());
		gfx.RenderText(UnitRects[c].text, Locator::TextManager->GetFormat("Tahoma22"), frm.ToD2D(), colour);

		int y = 0;
	}
}

void StartMenu::DrawBases(Graphics & gfx)
{
	RectF frm = { 440.0f,160.0f,860.0f,500.0f };
	D2D1_COLOR_F colour = D2D1::ColorF(0.0f, 1.0f, 0.0f, 1.25f);
	Locator::TextManager->GetFormat("Tahoma22")->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	for (int c = 0; c < 4; c++)
	{
		frm = BaseRects[c].pos; frm.left += 110.0f; frm.right += 330.0f; frm.top += 32.0f; frm.bottom += 32.0f;
		gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), BaseRects[c].pos.ToD2D(), m_textures[2]->GetBitmap(), &BaseRects[c].clip.ToD2D());
		gfx.RenderText(BaseRects[c].text, Locator::TextManager->GetFormat("Tahoma22"), frm.ToD2D(), colour);

	
	}
}
