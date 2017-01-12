#pragma once
#include "includes.h"
class Locator
{
public:
	static ID2D1RenderTarget* RenderTarget;
	static void SetD2DRenderTarget(ID2D1RenderTarget* rt);
};