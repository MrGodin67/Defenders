#include "Locator.h"

ID2D1RenderTarget* Locator::RenderTarget = nullptr;
SoundManager* Locator::SoundEngine = nullptr;
TextHandler* Locator::TextManager = nullptr;
void Locator::SetD2DRenderTarget(ID2D1RenderTarget* rt)
{
	RenderTarget = rt;
}

void Locator::SetSoundManager(SoundManager * sm)
{
	SoundEngine = sm;
}

void Locator::SetTextManager(TextHandler * tx)
{
	TextManager = tx;
}
