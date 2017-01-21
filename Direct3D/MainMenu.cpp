#include "MainMenu.h"
#include "Graphics.h"


MainMenu::MainMenu(Vec2f screenCenter, float width, float height)
{
	border = RectF(screenCenter.x - (width * 0.5f),
		screenCenter.y - (height * 0.5f),
		screenCenter.x + (width * 0.5f),
		screenCenter.y + (height * 0.5f));

	float w = 160.0f;
	float h = 32.0f;
	float x = border.left + 110.0f;
	float y = border.top + 180.0f;
	float inc = 34.0f;
	std::vector<WCHAR*> text;
	text.push_back(L"New");
	text.push_back(L"Resume");
	text.push_back(L"Exit");

	for (int c = 0; c < numButtons; c++)
	{
		Buttons[c].frame = RectF(x, y, x + w, y + h);
		Buttons[c].text = text[c];
		y += inc;

	}
	Buttons[0].id = newGame;
	Buttons[1].id = resumeGame;
	Buttons[2].id = exitGame;

	
}


MainMenu::~MainMenu()
{
}

void MainMenu::Draw(Graphics & gfx)
{
	gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), border.ToD2D(), Locator::ImageManager->GetImage("menuBack1")->GetTexture());
	gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), border.ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
	gfx.DrawFilledScreenRectangle(border.ToD2D(), D2D1::ColorF(0.2f, 0.2f, 0.9f, 0.20f));
	D2D1_COLOR_F colour = D2D1::ColorF(0.0f, 1.0f, 0.0f, 1.25f);
	Buttons[1].enabled = gameStarted;
	for (int c = 0; c < numButtons; c++)
	{
		RectF textRect = RectF(Buttons[c].frame.left + 4.0f,
			Buttons[c].frame.top, Buttons[c].frame.right, Buttons[c].frame.bottom);

		if (Buttons[c].drawFrame)
		{
			gfx.DrawFilledScreenRectangle(Buttons[c].frame.ToD2D(), D2D1::ColorF(0.0f, 1.0f, 0.0f, 0.25f));
			colour = D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			colour = D2D1::ColorF(0.0f, 1.0f, 0.0f, 1.25f);
		}
		Locator::TextManager->GetFormat("Tahoma22")->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		gfx.RenderText(Buttons[c].text, Locator::TextManager->GetFormat("Tahoma22"), textRect.ToD2D(), colour);

	}
}

_MenuReturn MainMenu::OnMouseClick(Vec2i& mouse)
{
	for (int c = 0; c < numButtons; c++)
	{
		if (Buttons[c].enabled)
		{
			if (Buttons[c].frame.Contains(mouse))
			{
				Locator::SoundEngine->Play("select", 1.25f);
				return Buttons[c].id;
			}
		}
		
	}

	return Invalid;
}

_MenuReturn MainMenu::OnMouseOver(Vec2i & mouse)
{
	
	Buttons[0].drawFrame = Buttons[1].drawFrame = Buttons[2].drawFrame = false;
	for (int c = 0; c < numButtons; c++)
	{
		if (Buttons[c].enabled)
		{
			if (Buttons[c].frame.Contains(mouse))
			{
				if (lastOver != c)
					Locator::SoundEngine->Play("tick", 0.25f);
				Buttons[c].drawFrame = true;
				lastOver = c;
				return Invalid;
			}
		}
		
	}
	lastOver = -1;
	return Invalid;
}
