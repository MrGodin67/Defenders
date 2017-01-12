#pragma once
/******************************************************************************************
*	Chili DirectX Framework Version 14.03.22											  *
*	Rect.h																				  *
*	Copyright 2014 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#include "Vec2.h"
#include "D2D1.h"
template < typename T >
class Rect
{
public:
	inline	Rect() {}
	inline	Rect(T left, T top, T right, T bottom)
		:
		left(left),
		top(top),
		right(right),
		bottom(bottom)
	{}
	inline	Rect(const Rect& rect)
		:
		top(rect.top),
		bottom(rect.bottom),
		left(rect.left),
		right(rect.right)
	{}
	inline	Rect(_Vec2<T> p0, _Vec2<T> p1)
		:
		Rect(min(p0.y, p1.y),
			max(p0.y, p1.y),
			min(p0.x, p1.x),
			max(p0.x, p1.x))
	{}
	inline	void Translate(_Vec2< T > d)
	{
		Translate(d.x, d.y);
	}
	inline	void Translate(T dx, T dy)
	{
		top += dy;
		bottom += dy;
		left += dx;
		right += dx;
	}
	template < typename T2 >
	inline	operator Rect< T2 >() const
	{
		return{ (T2)top,(T2)bottom,(T2)left,(T2)right };
	}
	inline	void ClipTo(const Rect& rect)
	{
		top = max(top, rect.top);
		bottom = min(bottom, rect.bottom);
		left = max(left, rect.left);
		right = min(right, rect.right);
	}
	inline	T GetWidth() const
	{
		return right - left;
	}
	inline	T GetHeight() const
	{
		return bottom - top;
	}
	inline	bool Overlaps(const Rect& rect) const
	{
		return top < rect.bottom && bottom > rect.top &&
			left < rect.right && right > rect.left;
	}
	template < typename T2 >
	inline	bool Contains(_Vec2<T2> p) const
	{
		return p.y >= top && p.y <= bottom && p.x >= left && p.x <= right;
	}
	inline D2D1_RECT_F ToD2D()
	{
		return D2D1::RectF((float)left, (float)top, (float)right, (float)bottom);
	}
public:
	T top;
	T bottom;
	T left;
	T right;
};

typedef Rect< int > RectI;
typedef Rect< float > RectF;