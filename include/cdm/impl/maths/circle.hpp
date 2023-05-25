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

#ifndef CDM_MATHS_IMPL_CIRCLE_HPP
#define CDM_MATHS_IMPL_CIRCLE_HPP 1

#include <cdm/decl/maths/circle.hpp>
#include <cdm/decl/maths/vector2.hpp>

namespace cdm
{
template <typename T>
constexpr bool circle_T<T>::evaluate(vector2_T<T> point, T e) const
{
	return nearly_equal(distance_squared_between(origin, point),
	                    radius * radius, e);
}

template <typename T>
inline T circle_T<T>::distance(vector2_T<T> point) const
{
	return std::abs(signed_distance(point));
}

template <typename T>
inline T circle_T<T>::signed_distance(vector2_T<T> point) const
{
	return distance_between(origin, point) - radius;
}

template <typename T>
constexpr T circle_T<T>::distance_squared(vector2_T<T> point) const
{
	return std::abs(signed_distance_squared(point));
}

template <typename T>
constexpr T circle_T<T>::signed_distance_squared(vector2_T<T> point) const
{
	return distance_squared_between(origin, point) - radius * radius;
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_CIRCLE_HPP
