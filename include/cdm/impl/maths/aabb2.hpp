/* cdm_maths v3.0.0
   C++20 geometric library
   https://github.com/WubiCookie/cdm
   no warranty implied; use at your own risk

LICENSE

       DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                   Version 2, December 2004

Copyright (C) 2022 Charles Seizilles de Mazancourt <charles DOT de DOT
mazancourt AT hotmail DOT fr>

Everyone is permitted to copy and distribute verbatim or modified
copies of this license document, and changing it is allowed as long
as the name is changed.

           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

 0. You just DO WHAT THE FUCK YOU WANT TO.

CREDITS

Written by Charles Seizilles de Mazancourt
*/

#ifndef CDM_MATHS_IMPL_AABB2_HPP
#define CDM_MATHS_IMPL_AABB2_HPP 1

#include <cdm/decl/maths/aabb2.hpp>
#include <cdm/decl/maths/point2.hpp>

namespace cdm
{
template <typename T>
constexpr bool aabb2_T<T>::contains(point2_T<T> v) const
{
	return p.x >= min.x && p.x <= max.x &&  //
	       p.y >= min.y && p.y <= max.y;    //
}

template <typename T>
constexpr point2_T<T> aabb2_T<T>::get_center() const
{
	return (max + min) / T(2);
}

template <typename T>
constexpr std::array<point2_T<T>, 4> aabb2_T<T>::get_points() const
{
	return std::array<point2_T<T>, 4>{
	    point2_T<T>{box.min.x, box.min.y},
	    point2_T<T>{box.max.x, box.min.y},
	    point2_T<T>{box.min.x, box.max.y},
	    point2_T<T>{box.max.x, box.max.y},
	};
}

template <typename T>
constexpr aabb2_T<T>& aabb2_T<T>::grow(const aabb2_T<T>& box)
{
	grow(box.min);
	grow(box.max);
	return *this;
}

template <typename T>
constexpr aabb2_T<T>& aabb2_T<T>::grow(point2_T<T> point)
{
	box.min = cdm::element_wise_min(box.min, point);
	box.max = cdm::element_wise_max(box.max, point);
	return *this;
}

template <typename T>
constexpr aabb2_T<T> aabb2_T<T>::operator+(const aabb2_T<T>& rhs) const
{
	aabb2_T<T> res = *this;
	res.grow(rhs);
	return res;
}

template <typename T>
constexpr aabb2_T<T> aabb2_T<T>::operator+(point2_T<T> rhs) const
{
	aabb2_T<T> res = *this;
	res.grow(rhs);
	return res;
}

template <typename T>
constexpr aabb2_T<T>& aabb2_T<T>::operator+=(const aabb2_T<T>& rhs)
{
	return grow(rhs);
}

template <typename T>
constexpr aabb2_T<T>& aabb2_T<T>::operator+=(point2_T<T> rhs)
{
	return grow(rhs);
}

template <typename T>
constexpr aabb2_T<T> operator+(point2_T<T> lhs, const aabb2_T<T>& rhs)
{
	return rhs + lhs;
}

template <typename T>
constexpr bool collides(const aabb2_T<T>& b0, const aabb2_T<T>& b1)
{
	return collides(b0, b1.origin) ||
	       collides(b0, b1.origin + vector2_T<T>(b1.dimension.x, T(0))) ||
	       collides(b0, b1.origin + vector2_T<T>(T(0), b1.dimension.y)) ||
	       collides(b0, b1.origin + b1.dimension);
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_AABB2_HPP
