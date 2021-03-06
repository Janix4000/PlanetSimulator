/******************************************************************************************
*	Chili DirectX Framework Version 16.10.01											  *
*	ChiliMath.h																			  *
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

#ifndef PI
#define PI 3.14159265f
#endif

#define TWO_PI 2.0f * PI
#define PI_D 3.1415926535897932
#define TWO_PI_D 2.0 * PI_D


#include <math.h>


template <typename T>
inline auto sq( const T& x )
{
	return x * x;
}

template<typename T>
inline T wrap_angle( T theta )
{
	const T modded = fmod( theta,(T)2.0 * (T)PI_D );
	return (modded > (T)PI_D) ?
		(modded - (T)2.0 * (T)PI_D) :
		modded;
}

template<typename T>
inline T interpolate( const T& src,const T& dst,float alpha )
{
	return src + (dst - src) * alpha;
}

template<typename T>
inline T map(const T& base, const T& oldMin, const T& oldMax, const T& newMin, const T& newMax)
{
	return ((base - oldMin) / (oldMax - oldMin)) * (newMax - newMin) + newMin;
}

template<typename T>
inline T getInDeegrees(T inRadians)
{
	return T(360) * inRadians / T(TWO_PI_D);
}