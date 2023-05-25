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

#ifndef CDM_MATHS_IMPL_UNSCALED_TRANSFORM3_HPP
#define CDM_MATHS_IMPL_UNSCALED_TRANSFORM3_HPP 1

#include <cdm/decl/maths/quaternion.hpp>
#include <cdm/decl/maths/unscaled_transform3.hpp>
#include <cdm/decl/maths/vector3.hpp>

namespace cdm
{
template <typename T>
constexpr unscaled_transform3_T<T>&
unscaled_transform3_T<T>::translate_absolute(vector3_T<T> t)
{
	position += t;
	return *this;
}

template <typename T>
constexpr unscaled_transform3_T<T>&
unscaled_transform3_T<T>::translate_relative(vector3_T<T> t)
{
	position += rotation * t;
	return *this;
}

template <typename T>
constexpr unscaled_transform3_T<T>& unscaled_transform3_T<T>::rotate(
    quaternion_T<T> r)
{
	rotation = r * rotation;
	return *this;
}

template <typename T>
inline unscaled_transform3_T<T>& unscaled_transform3_T<T>::inverse()
{
	rotation.inverse();
	position = rotation * -position;
	return *this;
}

template <typename T>
inline unscaled_transform3_T<T> unscaled_transform3_T<T>::get_inversed() const
{
	unscaled_transform3_T<T> res{*this};
	res.inverse();
	return res;
}

template <typename T>
inline matrix4_T<T> unscaled_transform3_T<T>::to_matrix4() const
{
	matrix4_T<T> res{matrix4_T<T>::rotation(rotation)};

	res.column(3).row(0) = position.x;
	res.column(3).row(1) = position.y;
	res.column(3).row(2) = position.z;

	return res;
}

template <typename T>
constexpr unscaled_transform3_T<T> unscaled_transform3_T<T>::operator*(
    const unscaled_transform3_T<T>& t) const
{
	unscaled_transform3_T<T> res;
	res.position = rotation * t.position + position;
	res.rotation = rotation * t.rotation;
	return res;
}

template <typename T>
constexpr vector3_T<T> unscaled_transform3_T<T>::operator*(
    vector3_T<T> v) const
{
	return rotation * v + position;
}

template <typename T>
constexpr quaternion_T<T> unscaled_transform3_T<T>::operator*(
    quaternion_T<T> q) const
{
	return rotation * q;
}

template <typename T>
constexpr unscaled_transform3_T<T> unscaled_transform3_T<T>::identity()
{
	return {
	    .position = vector3_T<T>::zero(),
	    .rotation = quaternion_T<T>::identity(),
	};
}

template <typename T>
inline unscaled_transform3_T<T> inverse(unscaled_transform3_T<T> t)
{
	t.rotation = inverse(t.rotation);
	t.position = t.rotation * -t.position;
	return t;
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_UNSCALED_TRANSFORM3_HPP
