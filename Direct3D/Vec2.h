#pragma once
#include <vector>

template <typename T>
class _Vec2
{
public:
	inline			_Vec2() {}
	inline			_Vec2(T x, T y)
		:
		x(x),
		y(y)
	{}
	inline			_Vec2(const _Vec2& vect)
		:
		_Vec2(vect.x, vect.y)
	{}
	template <typename T2>
	inline			operator _Vec2< T2 >() const
	{
		return{ (T2)x,(T2)y };
	}
	inline T		LenSq() const
	{
		return *this * *this;
	}
	inline T		Len() const
	{
		return sqrt(LenSq());
	}
	inline _Vec2&	Normalize()
	{
		const T length = Len();
		x /= length;
		y /= length;
		return *this;
	}
	inline _Vec2&	CCW90()
	{
		T temp = y;
		y = -x;
		x = temp;
		return *this;
	}
	inline _Vec2&	CW90()
	{
		T temp = y;
		y = x;
		x = -temp;
		return *this;
	}
	inline _Vec2&	Swap(_Vec2& vect)
	{
		const _Vec2 temp = vect;
		vect = *this;
		*this = temp;
		return *this;
	}
	inline _Vec2	operator-() const
	{
		return _Vec2(-x, -y);
	}
	inline _Vec2&	operator=(const _Vec2 &rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
		return *this;
	}
	inline _Vec2&	operator+=(const _Vec2 &rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}
	inline _Vec2&	operator-=(const _Vec2 &rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}
	inline T		operator*(const _Vec2 &rhs) const
	{
		return this->x * rhs.x + this->y * rhs.y;
	}
	inline _Vec2	operator+(const _Vec2 &rhs) const
	{
		return _Vec2(*this) += rhs;
	}
	inline _Vec2	operator-(const _Vec2 &rhs) const
	{
		return _Vec2(*this) -= rhs;
	}
	inline _Vec2&	operator*=(const T &rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		return *this;
	}
	inline _Vec2	operator*(const T &rhs) const
	{
		return _Vec2(*this) *= rhs;
	}
	inline _Vec2&	operator/=(const T &rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		return *this;
	}
	inline _Vec2	operator/(const T &rhs) const
	{
		return _Vec2(*this) /= rhs;
	}
	inline T		CrossWith(const _Vec2 &rhs) const
	{
		return x * rhs.y - y * rhs.x;
	}
	inline _Vec2	ClosestPtOnLine(const _Vec2 &lnpt1, const _Vec2 &lnpt2) const
	{
		_Vec2 p1 = lnpt1;
		_Vec2 p2 = lnpt2;
		_Vec2 pointOnLine;
		if (abs(p1.x - p2.x) > 0.0f)
		{
			if (p1.x > p2.x)
			{
				p1.Swap(p2);
			}
			const T m = (p2.y - p1.y) / (p2.x - p1.x);
			const T b = p1.y - m * p1.x;

			if (abs(m) > 0.0f)
			{
				T n = -1.0f / m;
				T c = this->y - this->x * n;
				pointOnLine.x = (b - c) / (n - m);
				pointOnLine.y = m * pointOnLine.x + b;
			}
			else
			{
				pointOnLine.x = this->x;
				pointOnLine.y = p1.y;
			}
		}
		else
		{
			pointOnLine.x = p1.x;
			pointOnLine.y = this->y;
		}
		return pointOnLine;
	}
	inline bool		IsInsideRect(const _Vec2 &p1, const _Vec2 & p2) const
	{
		const T medianX = (p1.x + p2.x) / 2.0f;
		const T medianY = (p1.y + p2.y) / 2.0f;
		return abs(medianX - x) <= abs(medianX - p1.x) &&
			abs(medianY - y) <= abs(medianY - p1.y);
	}
	inline bool		operator==(const _Vec2 &rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
	inline bool		operator!=(const _Vec2 &rhs) const
	{
		return !(*this == rhs);
	}
	inline _Vec2	MidpointWith(const _Vec2& p2) const
	{
		return _Vec2((x + p2.x) / 2.0f, (y + p2.y) / 2.0f);
	}
	inline _Vec2	Rotation(const float angle) const
	{
		_Vec2<T> result;
		float cosine = cosf(angle);
		float sine = sinf(angle);
		result.x = x * cosine - y * sine;
		result.y = x * sine + y * cosine;
		return result;
	}

public:
	T x;
	T y;
};

typedef _Vec2< float > Vec2f;
typedef _Vec2< double > Vec2d;
typedef _Vec2< int > Vec2i;

template< typename T >
inline std::vector< _Vec2<T> > CalculateIntersectionPoints(_Vec2<T> q, _Vec2<T> p1, _Vec2<T> p2, T r)
{
	std::vector< _Vec2<T> > points;
	// calculate discriminant
	const _Vec2<T> d = p2 - p1;
	const T dr2 = d.LenSq();
	const T D = (p1 - q).CrossWith(p2 - q);
	const T disc = sq(r) * dr2 - sq(D);
	// line intersection test
	if (disc >= (T)0.0)
	{
		// calculate points of intersection
		const T sqrtDisc = sqrt(disc);
		const T lhsx = D * d.y;
		const T rhsx = sgn(d.y) * d.x * sqrtDisc;
		const T lhsy = -D * d.x;
		const T rhsy = abs(d.y) * sqrtDisc;
		points.push_back(_Vec2<T> { (lhsx + rhsx) / dr2, (lhsy + rhsy) / dr2 } +q);
		if (disc > (T)0.0)
		{
			points.push_back(_Vec2<T> { (lhsx - rhsx) / dr2, (lhsy - rhsy) / dr2 } +q);
		}
	}
	return points;
}