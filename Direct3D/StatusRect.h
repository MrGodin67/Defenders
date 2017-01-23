#pragma once
#include "Drawable.h"
#include "includes.h"
#include "Rect.h"


class StatusRect
{
public:
	struct StatusRectDesc
	{
		
		D2D1_RECT_F drawRect;
		D2D1_COLOR_F color;
		float alphaBlend = 1.0f;
		StatusRectDesc() {}
		StatusRectDesc(D2D1_RECT_F& drawrect,  float transparency,D2D1_COLOR_F color)
			:
			drawRect(drawrect),
			alphaBlend(transparency),
			color(color)
		{}
	};
protected:
	StatusRectDesc m_Desc;
	Vec2f m_center;
	Vec2f m_scale = { 1.0f,1.0f };
	float m_drawWidth, m_drawHeight;
	float m_rotAngle = 0.0f;

public:
	StatusRect() {}
	StatusRect(StatusRectDesc& desc);
	virtual ~StatusRect() {}
	StatusRectDesc GetRenderDesc() { return m_Desc; }
	void SetScaling(Vec2f& scale);
	void SetRotation(float& angle);
	virtual void SetPosition(Vec2f& pos);

public:
	class Drawable : public ::Drawable
	{
		StatusRect& m_parent;

	public:
		Drawable(StatusRect& p);
		virtual ~Drawable() {};
		virtual void Rasterize(class Graphics& gfx)override;
		virtual void TranslateCoords(const Vec2f& pos)override;
		virtual void Transform(const D2D1::Matrix3x2F& mat)override;
	};
	Drawable GetDrawable();


};
class LifeRect : public StatusRect
{
protected:
	float m_maxValue;
	float m_width;
	float m_position = 0.0f;
	D2D1_COLOR_F m_meterColor;
	float m_lineWidth = 1.0f;
	D2D1_POINT_2F m_linePt[2];
public:
	LifeRect() {}
	LifeRect(StatusRectDesc& desc,float maxValue,float lineWidth, D2D1_COLOR_F meterColor = D2D1::ColorF(0.0f,1.0f,0.0f,1.0f))
	:
	StatusRect(desc),
	m_maxValue(maxValue),
	m_lineWidth(lineWidth),
	m_meterColor(meterColor)
	{
		m_width = desc.drawRect.right - desc.drawRect.left;
		float inc = m_width / 3.0f;
		m_width -= inc;
		inc = inc * 0.5f;
		m_linePt[0].x = desc.drawRect.left + inc;
		m_linePt[0].y = desc.drawRect.top - 1.0f;
		m_linePt[1] = m_linePt[0];
	}
	void UpdateHealth(float& health);
	void SetMaxValue(float val) { m_maxValue = val; }
	virtual void SetPosition(Vec2f& pos)override;
	class Drawable : public ::Drawable
	{
		LifeRect& m_parent;

	public:
		Drawable(LifeRect& p);
		virtual ~Drawable() {};
		virtual void Rasterize(class Graphics& gfx)override;
		virtual void TranslateCoords(const Vec2f& pos)override;
		virtual void Transform(const D2D1::Matrix3x2F& mat)override;
	};
	Drawable GetDrawable();
};