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

#ifndef CDM_MATHS_IMPL_UNIFORM_TRANSFORM2_HPP
#define CDM_MATHS_IMPL_UNIFORM_TRANSFORM2_HPP 1

#include <cdm/decl/maths/radian.hpp>
#include <cdm/decl/maths/uniform_transform2.hpp>
#include <cdm/decl/maths/vector2.hpp>

namespace cdm
{
template <typename T>
inline uniform_transform2_T<T> uniform_transform2_T<T>::operator*(
    uniform_transform2_T<T> t) const
{
	uniform_transform2_T<T> res;
	matrix2_T<T> r = matrix2_T<T>::rotation(rotation);
	res.position = r * (scale * t.position) + position;
	res.rotation = rotation + t.rotation;
	res.scale = scale * t.scale;
	return res;
}

template <typename T>
inline vector2_T<T> uniform_transform2_T<T>::operator*(vector2_T<T> v) const
{
	matrix2_T<T> r = matrix2_T<T>::rotation(rotation);
	return r * (scale * v) + position;
}

template <typename T>
constexpr uniform_transform2_T<T> uniform_transform2_T<T>::identity()
{
	return {
	    .position = vector2_T<T>::zero(),
	    .rotation = normalized<complex_T<T>>::already_normalized(
	        complex_T<T>::identity()),
	    .scale = T(1),
	};
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_UNIFORM_TRANSFORM2_HPP
