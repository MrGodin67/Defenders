#pragma once
#include "includes.h"
#include "SoundManager.h"
class Locator
{
public:
	static SoundManager* SoundEngine;
	static ID2D1RenderTarget* RenderTarget;
	static void SetD2DRenderTarget(ID2D1RenderTarget* rt);
	static void SetSoundManager(SoundManager* sm);
};