#pragma once

#include "includes.h"
#include "Rect.h"
#include "Vec2.h"
#include "EntityInterface.h"
#include "SpriteSheet.h"

class TextSprite
{
protected:
	D2D1_COLOR_F color;
	D2D1_COLOR_F backcolor;
	RectF pos;
	WCHAR text[256];
	bool drawBackground;
	IDWriteTextFormat* pFormat;
public:
	TextSprite() {}
	TextSprite(IDWriteTextFormat* format,RectF pos,std::wstring text, D2D1_COLOR_F color, D2D1_COLOR_F backColor = D2D1::ColorF(0.0f,0.0f,0.0f,1.0f),bool drawBack = false)
		:pFormat(format),pos(pos), color(color),backcolor(backColor),drawBackground(drawBack)
	{
		wsprintf(this->text, L"%s", text.c_str());
		//this->text[] = const_cast<WCHAR*>(text.c_str());
	}
	virtual ~TextSprite() {}
	virtual void UpdateText(std::wstring str);
	virtual void Draw(class Graphics& gfx);

};

class Sprite : public Entity
{
protected:
	SpriteSheet* m_image;
	RectF m_drawRect;
	Vec2f m_pos;
	float m_width;
	float m_height;
	int m_imageIndex;
	float m_angle = 0.0f;
public:
	Sprite(SpriteSheet* image,int imageIndex, float width, float height, Vec2f pos,_EntityType type);

	// Inherited via Entity
	virtual void Update(const float & dt) override;
	virtual void Draw(Graphics & gfx) override;
	virtual RectF GetAABB() override;
	virtual void TransformToCamera(Vec2f& pos);
	virtual Vec2f GetCenter() override;
	virtual Vec2f GetPosition();
	void SetTexture(SpriteSheet* image, int imageIndex,float width,float height);
	void SetDrawRect(RectF rect) 
	{ 
		m_width = rect.right - rect.left;
		m_height = rect.bottom - rect.top;
		m_pos.x = rect.left;
		m_pos.y = rect.top;
		m_drawRect = rect; 
	}
};