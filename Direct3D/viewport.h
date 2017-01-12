#pragma once
#include "RenderTarget.h"
#include "includes.h"
#include "Drawable.h"

class Viewport : public RenderTarget
{
public:// next = grafix
	Viewport(RenderTarget& next, float4& rect)
		:
		next(next),
		clip(rect)
	{

	}
	float4 GetClip() { return clip; }

	virtual void Rasterize(Drawable& obj)
	{
		//float2 pos = float2((float)clip.left, (float)clip.top);
		//obj.Transform(D2D1::Matrix3x2F::Translation({ pos.x,pos.y }));
	
		//obj.Clip(clip);
		next.Rasterize(obj);
	}
	int GetWidth() { return (int)(clip.right - clip.left); }
	int GetHeight() { return (int)(clip.bottom - clip.top); }
	float2 GetPos() { return float2((float)clip.left, (float)clip.top); }
private:
	RenderTarget& next;

	float4 clip;
};