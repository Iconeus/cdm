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

#ifndef CDM_MATHS_IMPL_TRANSFORM2_HPP
#define CDM_MATHS_IMPL_TRANSFORM2_HPP 1

#include <cdm/decl/maths/complex.hpp>
#include <cdm/decl/maths/transform2.hpp>
#include <cdm/decl/maths/vector2.hpp>

namespace cdm
{
template <typename T>
constexpr transform2_T<T> transform2_T<T>::operator*(
    const transform2_T<T>& t) const
{
	transform2_T<T> res;
	res.position =
	    rotation * vector2_T(scale.x * t.position.x, scale.y * t.position.y) +
	    position;
	res.rotation = rotation + t.rotation;
	res.scale = vector2_T(scale.x * t.scale.x, scale.y * t.scale.y);
	return res;
}

template <typename T>
constexpr vector2_T<T> transform2_T<T>::operator*(vector2_T<T> v) const
{
	return rotation * vector2_T(scale.x * v.x, scale.y * v.y) + position;
}

template <typename T>
constexpr transform2_T<T> transform2_T<T>::identity()
{
	return {
	    .position = vector2_T<T>::zero(),
	    .rotation = normalized<complex_T<T>>::already_normalized(
	        complex_T<T>::identity()),
	    .scale = vector2_T<T>::one(),
	};
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_TRANSFORM2_HPP
