#include "StatusRect.h"

#include "Graphics.h"


StatusRect::StatusRect(StatusRectDesc& desc)
	:
	m_Desc(desc)
{
	m_drawWidth = desc.drawRect.right - desc.drawRect.left;
	m_drawHeight = desc.drawRect.bottom - desc.drawRect.top;
	m_center.x = desc.drawRect.left + (m_drawWidth * 0.5f);
	m_center.y = desc.drawRect.top + (m_drawHeight * 0.5f);

}


void StatusRect::SetScaling(Vec2f & scale)
{
	m_scale = scale;
}

void StatusRect::SetRotation(float & angle)
{
	m_rotAngle = angle;
}

void StatusRect::SetPosition(Vec2f & pos)
{
	m_Desc.drawRect = RectF(pos.x, pos.y, pos.x + m_drawWidth, pos.y + m_drawHeight).ToD2D();
	m_center.x = pos.x + (m_drawWidth * 0.5f);
	m_center.y = pos.y + (m_drawHeight * 0.5f);
}

void StatusRect::SetColor(D2D1_COLOR_F color)
{
	m_Desc.color = color;
}

StatusRect::Drawable::Drawable(StatusRect& p)
	:
	m_parent(p)

{
	matTrans = D2D1::Matrix3x2F::Identity();
	matRot = D2D1::Matrix3x2F::Identity();
	matScale = D2D1::Matrix3x2F::Identity();


}

StatusRect::Drawable StatusRect::GetDrawable()
{
	return Drawable(*this);
}

void StatusRect::Drawable::Rasterize(Graphics& gfx)
{
	Transform(D2D1::Matrix3x2F::Rotation(m_parent.m_rotAngle, { m_parent.m_center.x,m_parent.m_center.y }));
	Transform(D2D1::Matrix3x2F::Scale(
	{ m_parent.m_scale.x, m_parent.m_scale.y },
	{ m_parent.m_center.x,m_parent.m_center.y }));
	if(m_parent.m_Desc.drawFilled)
		gfx.DrawFilledScreenRectangle( m_parent.m_Desc.drawRect, m_parent.m_Desc.color,&matTrans);
	else
		gfx.DrawRectangle(matTrans, m_parent.m_Desc.drawRect, m_parent.m_Desc.color);


}
void StatusRect::Drawable::Transform(const D2D1::Matrix3x2F& mat)
{
	matTrans = mat * matTrans;
}
void StatusRect::Drawable::TranslateCoords(const Vec2f &pos)
{
	matTrans = D2D1::Matrix3x2F::Translation({ pos.x, pos.y });

}




LifeRect::Drawable::Drawable(LifeRect& p)
	:
	m_parent(p)

{
	matTrans = D2D1::Matrix3x2F::Identity();
	matRot = D2D1::Matrix3x2F::Identity();
	matScale = D2D1::Matrix3x2F::Identity();


}

void LifeRect::UpdateHealth(float & health)
{
	// get percentile of completion (health / m_maxValue)
	// set position to be the percentile of width
	
	m_position = m_width * (health / m_maxValue);
	if (m_position > m_width)
		m_position = m_width;
	// move line to show amount of health
	m_linePt[1].x = m_linePt[0].x + m_position;
}

void LifeRect::SetPosition(Vec2f & pos)
{
	m_Desc.drawRect = RectF(pos.x, pos.y, pos.x + m_drawWidth, pos.y + m_drawHeight).ToD2D();
	m_center.x = pos.x + (m_drawWidth * 0.5f);
	m_center.y = pos.y + (m_drawHeight * 0.5f);
	
	float inc = m_width / 3.0f;
	inc = inc * 0.5f;
	m_linePt[0].x = m_Desc.drawRect.left + inc;
	m_linePt[0].y = m_Desc.drawRect.top - 1.0f;
	m_linePt[1].y = m_linePt[0].y;
	m_linePt[1].x = m_linePt[0].x + m_position;
}

LifeRect::Drawable LifeRect::GetDrawable()
{
	return Drawable(*this);
}

void LifeRect::Drawable::Rasterize(Graphics& gfx)
{
	Transform(D2D1::Matrix3x2F::Rotation(m_parent.m_rotAngle, { m_parent.m_center.x,m_parent.m_center.y }));
	Transform(D2D1::Matrix3x2F::Scale(
	{ m_parent.m_scale.x, m_parent.m_scale.y },
	{ m_parent.m_center.x,m_parent.m_center.y }));
	gfx.DrawRectangle(matTrans, m_parent.m_Desc.drawRect, m_parent.m_Desc.color);
	gfx.DrawLine(matTrans,m_parent.m_linePt[0],m_parent.m_linePt[1], m_parent.m_meterColor, m_parent.m_lineWidth);

}
void LifeRect::Drawable::Transform(const D2D1::Matrix3x2F& mat)
{
	matTrans = mat * matTrans;
}
void LifeRect::Drawable::TranslateCoords(const Vec2f &pos)
{
	matTrans = D2D1::Matrix3x2F::Translation({ pos.x, pos.y });

}