/******************************************************************************************
*	Chili DirectX Framework Version 16.10.01											  *
*	Vec2.h																				  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
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
#pragma once

#include "ChilliMath.h"
#include <SFML/System/Vector2.hpp>

template <typename T>
class _Vec2
{
public:
	_Vec2()
		:
		x(T(0)),
		y(T(0))
	{}
	_Vec2( T x,T y )
		:
		x( x ),
		y( y )
	{}
	_Vec2( const _Vec2& vect )
		:
		_Vec2( vect.x,vect.y )
	{}
	operator sf::Vector2<T>() const
	{
		return sf::Vector2<T>{x, y};
	}
	template <typename V>
	explicit operator sf::Vector2<V>() const
	{
		return sf::Vector2<T>{V(x), V(y)};
	}
	template <typename T2>
	explicit operator _Vec2<T2>() const
	{
		return{ (T2)x,(T2)y };
	}
	T		getLenSq() const
	{
		return sq( *this );
	}
	T		getLen() const
	{
		return sqrt( getLenSq() );
	}
	_Vec2&	normalize()
	{
		const T length = getLen();
		x /= length;
		y /= length;
		return *this;
	}
	_Vec2	getNormalized() const
	{
		_Vec2 norm = *this;
		norm.normalize();
		return norm;
	}
	_Vec2	getPerpendicular() const
	{
		return { -y, x };
	}
	_Vec2&	rotate(double theta)
	{
		double sinT = sin(theta);
		double cosT = cos(theta);
		x = T(double(x) * (-sinT + cosT));
		y = T(double(y) * (sinT + cosT));
		return *this;
	}
	_Vec2&	setLen(T size)
	{
		normalize();
		x *= size;
		y *= size;
		return *this;
	}
	_Vec2&	limit(T limitedLen)
	{
		if (getLenSq() > pow(limitedLen, 2))
		{
			setLen(limitedLen);
		}
		return *this;
	}


	_Vec2	operator-() const
	{
		return _Vec2( -x,-y );
	}
	_Vec2&	operator=( const _Vec2 &rhs )
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}
	_Vec2&	operator+=( const _Vec2 &rhs )
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	_Vec2&	operator-=( const _Vec2 &rhs )
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	T		operator*( const _Vec2 &rhs ) const
	{
		return x * rhs.x + y * rhs.y;
	}
	_Vec2	operator+( const _Vec2 &rhs ) const
	{
		return _Vec2( *this ) += rhs;
	}
	_Vec2	operator-( const _Vec2 &rhs ) const
	{
		return _Vec2( *this ) -= rhs;
	}
	_Vec2&	operator*=( const T &rhs )
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}
	_Vec2	operator*( const T &rhs ) const
	{
		return _Vec2( *this ) *= rhs;
	}
	_Vec2&	operator/=( const T &rhs )
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}
	_Vec2	operator/( const T &rhs ) const
	{
		return _Vec2( *this ) /= rhs;
	}
	bool	operator==( const _Vec2 &rhs ) const
	{
		return x == rhs.x && y == rhs.y;
	}
	bool	operator!=( const _Vec2 &rhs ) const
	{
		return !(*this == rhs);
	}
public:
	T x;
	T y;
};

typedef _Vec2<float> Vec2;
typedef _Vec2<double> Ved2;
typedef _Vec2<int> Vei2;