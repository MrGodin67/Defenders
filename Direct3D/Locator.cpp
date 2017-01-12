#include "Locator.h"

ID2D1RenderTarget* Locator::RenderTarget = nullptr;

void Locator::SetD2DRenderTarget(ID2D1RenderTarget* rt)
{
	RenderTarget = rt;
}