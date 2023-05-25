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

#ifndef CDM_MATHS_IMPL_UNIFORM_TRANSFORM3_HPP
#define CDM_MATHS_IMPL_UNIFORM_TRANSFORM3_HPP 1

#include <cdm/decl/maths/quaternion.hpp>
#include <cdm/decl/maths/uniform_transform3.hpp>
#include <cdm/decl/maths/vector3.hpp>

namespace cdm
{
template <typename T>
inline matrix4_T<T> uniform_transform3_T<T>::to_matrix4() const
{
	matrix4_T<T> res{matrix4_T<T>::rotation(rotation)};

	res.column(0).row(0) = res.column(0).row(0) * scale;
	res.column(0).row(1) = res.column(0).row(1) * scale;
	res.column(0).row(2) = res.column(0).row(2) * scale;

	res.column(1).row(0) = res.column(1).row(0) * scale;
	res.column(1).row(1) = res.column(1).row(1) * scale;
	res.column(1).row(2) = res.column(1).row(2) * scale;

	res.column(2).row(0) = res.column(2).row(0) * scale;
	res.column(2).row(1) = res.column(2).row(1) * scale;
	res.column(2).row(2) = res.column(2).row(2) * scale;

	res.column(3).row(0) = position.x;
	res.column(3).row(1) = position.y;
	res.column(3).row(2) = position.z;

	return res;
}

template <typename T>
constexpr uniform_transform3_T<T> uniform_transform3_T<T>::operator*(
    const uniform_transform3_T<T>& t) const
{
	uniform_transform3_T<T> res;
	res.position = rotation * (scale * t.position) + position;
	res.rotation = rotation * t.rotation;
	res.scale = scale * t.scale;
	return res;
}

template <typename T>
constexpr vector3_T<T> uniform_transform3_T<T>::operator*(vector3_T<T> v) const
{
	return rotation * (scale * v) + position;
}

template <typename T>
constexpr quaternion_T<T> uniform_transform3_T<T>::operator*(
    quaternion_T<T> q) const
{
	return rotation * q;
}

template <typename T>
constexpr uniform_transform3_T<T> uniform_transform3_T<T>::identity()
{
	return {
	    .position = vector3_T<T>::zero(),
	    .rotation = quaternion_T<T>::identity(),
	    .scale = T(1),
	};
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_UNIFORM_TRANSFORM3_HPP