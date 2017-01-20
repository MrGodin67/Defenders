#include "StartMenu.h"
#include "Graphics.h"
#include "Locator.h"

StartMenu::StartMenu(Vec2f screenCenter, float width, float height)
{
	border = RectF(screenCenter.x - (width * 0.5f),
		screenCenter.y - (height * 0.5f),
		screenCenter.x + (width * 0.5f),
		screenCenter.y + (height * 0.5f));
	std::vector<WCHAR*> text;
	
	float px = border.left + 328.0f;
	float py = border.top + 80.0f;
	float inc1 = 90.0f;
	text.push_back(L"Drone : fast scouting\nLimited offensive, collect tech");
	text.push_back(L"Fighter : main battle uint\nBest offensive");
	text.push_back(L"Artillary : slow moving\nIncreased range");
	text.push_back(L"Radar : slow moving\nNo offence, Enemy detection");
	text.push_back(L"Turret : static\n Enemy detection");
	
	for (int c = 0; c < 5; c++)
	{
		UnitRects[c].clip = Locator::ImageManager->GetClip("player_units", c);
		UnitRects[c].pos = { px,py,px + 64.0f,py + 64.0f };
		UnitRects[c].textPos = { px + 70.0f,py + 6.0f,px + 364.0f,py + 64.0f };
		py += inc1;
		UnitRects[c].text = text[c];
	}
	
	py = border.top + 80.0f;
	inc1 = 106.0f;
	text.clear();
	text.push_back(L"Command Post : Drone creation, sell technology ");
	text.push_back(L"Factory : Build Fighters\nRadar, Artillary.");
	text.push_back(L"Technology : Build new Tech from scavanged technology.");
	text.push_back(L"Repair Facility : Repair units.");
	
	for (int c = 0; c < 4; c++)
	{
		BaseRects[c].pos = { px,py,px + 96.0f,py + 96.0f };
		BaseRects[c].clip = Locator::ImageManager->GetClip("bases", c);
		BaseRects[c].textPos = { px + 100.0f,py + 6.0f,px + 396.0f,py + 96.0f };
		py += inc1;
		BaseRects[c].text = text[c];
	}
	
	
	float w = 160.0f;
	float h = 32.0f;
	float x = border.left + 80.0f;
	float y = border.top + 80.0f;
	float inc = 34.0f;
	text.clear();
	text.push_back(L"Map");
	text.push_back(L"Units");
	text.push_back(L"Bases");
	text.push_back(L"Technology");
	text.push_back(L"Objective");
	text.push_back(L"How To");
	text.push_back(L"Start New Game");
	text.push_back(L"Exit");
	for (int c = 0; c < numButtons -2; c++)
	{
		Buttons[c].frame = RectF(x, y, x + w, y + h);
		Buttons[c].id = 0;
		Buttons[c].text = text[c];
		y += inc;
		
	}
	y += inc ;
	Buttons[numButtons - 2].frame = RectF(x, y, x + w, y + h);
	Buttons[numButtons - 2].id = 1;
	Buttons[numButtons - 2].text = L"New Game";
	y += inc*4;
	Buttons[numButtons - 1].frame = RectF(x, y, x + w, y + h);
	Buttons[numButtons - 1].id = 1;
	Buttons[numButtons - 1].text = L"Back";
	
	TechRects[0].clip = Locator::ImageManager->GetClip("player_units", 5);
	TechRects[0].pos = UnitRects[3].pos;
	TechRects[0].textPos = UnitRects[3].textPos;
	TechRects[0].text = L"Techology hardware";

	TechRects[1].clip = Locator::ImageManager->GetClip("player_units", 6);
	TechRects[1].pos = UnitRects[4].pos;
	TechRects[1].textPos = UnitRects[4].textPos;
	TechRects[1].text = L"Data storage device";

	TechRects[2].textPos =  { border.left + 328.0f,border.top + 80.0f,border.right - 80.0f,border.bottom - 80.0f };
	TechRects[2].text = L"  Collect as much enemy technology as you can. Constuct it by combining scripts,found on data storage units, along with hardware found amongst the enemy wreckage. You can then sell it to enterprises that can further enhance it's capabilities, or you may choose to use the technology to upgrade your units. Rest assured, everything has it's price..";
	
	HowTo.textPos = { border.left + 328.0f,border.top + 80.0f,border.right - 80.0f,border.bottom - 80.0f };
	HowTo.text = L"  Press Control + left mouse button to select Units\\Bases to place in world";



}


StartMenu::~StartMenu()
{
}

void StartMenu::Draw(Graphics & gfx)
{
	gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), border.ToD2D(), Locator::ImageManager->GetImage("menuBack2")->GetTexture());
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
				break;
			case 3:
				DrawTechnology(gfx);
				break;	
			case 4:
				DrawObjectives(gfx);
				break;
			case 5:
				DrawHowTo(gfx);
				break;
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
			Locator::SoundEngine->Play("select", 0.75f);
			
			return Buttons[c].id;
		}

	}

	return -1;
}

int StartMenu::OnMouseOver(Vec2i & mouse)
{
	
	Buttons[0].drawFrame = Buttons[1].drawFrame = Buttons[2].drawFrame = 
		Buttons[3].drawFrame = Buttons[4].drawFrame = Buttons[5].drawFrame= Buttons[6].drawFrame = Buttons[7].drawFrame = false;
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
	
	RectF frm = { border.left + 328.0f,border.top + 80.0f,border.right - 80.0f,border.bottom  -  80.0f };

	D2D1_COLOR_F colour = D2D1::ColorF(0.0f, 1.0f, 0.0f, 1.25f);
	gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), frm.ToD2D(), Locator::ImageManager->GetImage("worldmap")->GetTexture());

	
}

void StartMenu::DrawUnits(Graphics & gfx)
{
	
	D2D1_COLOR_F colour = D2D1::ColorF(0.0f, 1.0f, 0.0f, 1.25f);
	Locator::TextManager->GetFormat("Tahoma22")->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	for (int c = 0; c < 5; c++)
	{
		gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), UnitRects[c].pos.ToD2D(), UnitRects[c].clip.bitmap, &UnitRects[c].clip.rect.ToD2D());
		gfx.RenderText(UnitRects[c].text, Locator::TextManager->GetFormat("Tahoma22"), UnitRects[c].textPos.ToD2D(), colour);

		int y = 0;
	}
}

void StartMenu::DrawBases(Graphics & gfx)
{
	
	D2D1_COLOR_F colour = D2D1::ColorF(0.0f, 1.0f, 0.0f, 1.25f);
	Locator::TextManager->GetFormat("Tahoma22")->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	for (int c = 0; c < 4; c++)
	{
		gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), BaseRects[c].pos.ToD2D(), BaseRects[c].clip.bitmap, &BaseRects[c].clip.rect.ToD2D());
		gfx.RenderText(BaseRects[c].text, Locator::TextManager->GetFormat("Tahoma22"), BaseRects[c].textPos.ToD2D(), colour);

	
	}
}

void StartMenu::DrawObjectives(Graphics & gfx)
{
	RectF frm = { border.left + 328.0f,border.top + 80.0f,border.right - 80.0f,border.bottom - 80.0f };
	WCHAR* txt = L"  An unidentified entity has landed on Outpost H-16 in the Delta Quadrant. In order for us to defeat the incursion we must eraticate the intruders.\n You will be provided the resposability to defend the location";
	D2D1_COLOR_F color = D2D1::ColorF(0.0f, 1.0f, 0.0f, 1.0f);
	Locator::TextManager->GetFormat("Tahoma20")->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	gfx.RenderText(txt, Locator::TextManager->GetFormat("Tahoma20"), frm.ToD2D(), color);

}

void StartMenu::DrawTechnology(Graphics & gfx)
{
	D2D1_COLOR_F color = D2D1::ColorF(0.0f, 1.0f, 0.0f, 1.0f);
	Locator::TextManager->GetFormat("Tahoma20")->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	gfx.RenderText(TechRects[2].text, Locator::TextManager->GetFormat("Tahoma20"), TechRects[2].textPos.ToD2D(), color);
	
	for (int c = 0; c < 2; c++)
	{
		gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), TechRects[c].pos.ToD2D(), TechRects[c].clip.bitmap, &TechRects[c].clip.rect.ToD2D());
		gfx.RenderText(TechRects[c].text, Locator::TextManager->GetFormat("Tahoma22"), TechRects[c].textPos.ToD2D(), color);

	}
	

}

void StartMenu::DrawHowTo(Graphics & gfx)
{
	D2D1_COLOR_F color = D2D1::ColorF(0.0f, 1.0f, 0.0f, 1.0f);
	Locator::TextManager->GetFormat("Tahoma20")->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	gfx.RenderText(HowTo.text, Locator::TextManager->GetFormat("Tahoma20"), HowTo.textPos.ToD2D(), color);

}
