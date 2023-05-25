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

#ifndef CDM_MATHS_IMPL_UNSCALED_TRANSFORM2_HPP
#define CDM_MATHS_IMPL_UNSCALED_TRANSFORM2_HPP 1

#include <cdm/decl/maths/radian.hpp>
#include <cdm/decl/maths/unscaled_transform2.hpp>
#include <cdm/decl/maths/vector2.hpp>

namespace cdm
{
template <typename T>
inline unscaled_transform2_T<T> unscaled_transform2_T<T>::operator*(
    unscaled_transform2_T<T> t) const
{
	unscaled_transform2_T<T> res;
	matrix2_T<T> r = matrix2_T<T>::rotation(rotation);
	res.position = r * t.position + position;
	res.rotation = rotation + t.rotation;
	return res;
}
template <typename T>
inline vector2_T<T> unscaled_transform2_T<T>::operator*(vector2_T<T> v) const
{
	matrix2_T<T> r = matrix2_T<T>::rotation(rotation);
	return r * v + position;
}

template <typename T>
constexpr unscaled_transform2_T<T> unscaled_transform2_T<T>::identity()
{
	return {
	    .position = vector2_T<T>::zero(),
	    .rotation = normalized<complex_T<T>>::already_normalized(
	        complex_T<T>::identity()),
	};
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_UNSCALED_TRANSFORM2_HPP
