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
#include "Vec2.h"

template <typename T>
class _Vec3 : public _Vec2<T>
{
public:
	_Vec3() {}
	_Vec3( T x,T y,T z )
		:
		_Vec2( x,y ),
		z( z )
	{}
	_Vec3( const _Vec3& vect )
		:
		_Vec3( vect.x,vect.y,vect.z )
	{}
	template <typename T2>
	explicit operator _Vec3<T2>() const
	{
		return{ (T2)x,(T2)y,(T2)z };
	}
	T		lenSq() const
	{
		return sq( *this );
	}
	T		len() const
	{
		return sqrt( LenSq() );
	}
	_Vec2	getPerpendicular() const = delete;
	_Vec2&	rotate(double theta) = delete;
	_Vec3&	normalize()
	{
		const T length = Len();
		x /= length;
		y /= length;
		z /= length;
		return *this;
	}
	_Vec3	getNormalized() const
	{
		_Vec3 norm = *this;
		norm.Normalize();
		return norm;
	}
	_Vec3&	setLen(T size)
	{
		normalize();
		x *= size;
		y *= size;
		z *= size;
		return *this;
	}
	_Vec3	operator-() const
	{
		return _Vec3( -x,-y,-z );
	}
	_Vec3&	operator=( const _Vec3 &rhs )
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}
	_Vec3&	operator+=( const _Vec3 &rhs )
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}
	_Vec3&	operator-=( const _Vec3 &rhs )
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}
	T		operator*( const _Vec3 &rhs ) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}
	_Vec3	operator+( const _Vec3 &rhs ) const
	{
		return _Vec3( *this ) += rhs;
	}
	_Vec3	operator-( const _Vec3 &rhs ) const
	{
		return _Vec3( *this ) -= rhs;
	}
	_Vec3&	operator*=( const T &rhs )
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}
	_Vec3	operator*( const T &rhs ) const
	{
		return _Vec3( *this ) *= rhs;
	}
	_Vec3	operator%( const _Vec3& rhs ) const
	{
		return _Vec3(
			y * rhs.z - z * rhs.y,
			z * rhs.x - x * rhs.z,
			x * rhs.y - y * rhs.x );
	}
	_Vec3&	operator/=( const T &rhs )
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}
	_Vec3	operator/( const T &rhs ) const
	{
		return _Vec3( *this ) /= rhs;
	}
	bool	operator==( const _Vec3 &rhs ) const
	{
		return x == rhs.x && y == rhs.y && rhs.z = z;
	}
	bool	operator!=( const _Vec3 &rhs ) const
	{
		return !(*this == rhs);
	}
public:
	T z;
};

typedef _Vec3<float> Vec3;
typedef _Vec3<double> Ved3;
typedef _Vec3<int> Vei3;