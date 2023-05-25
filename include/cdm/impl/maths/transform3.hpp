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

#ifndef CDM_MATHS_IMPL_TRANSFORM3_HPP
#define CDM_MATHS_IMPL_TRANSFORM3_HPP 1

#include <cdm/decl/maths/quaternion.hpp>
#include <cdm/decl/maths/transform3.hpp>
#include <cdm/decl/maths/vector3.hpp>

#include <ostream>

namespace cdm
{
template <typename T>
constexpr transform3_T<T>& transform3_T<T>::translate_absolute(vector3_T<T> t)
{
	position += t;
	return *this;
}

template <typename T>
constexpr transform3_T<T>& transform3_T<T>::translate_relative(vector3_T<T> t)
{
	position += rotation * t;
	return *this;
}

template <typename T>
constexpr transform3_T<T>& transform3_T<T>::rotate(quaternion_T<T> r)
{
	rotation = r * rotation;
	return *this;
}

template <typename T>
inline matrix4_T<T> transform3_T<T>::to_matrix4() const
{
	matrix4_T<T> res{matrix4_T<T>::rotation(rotation)};

	res.column(0).row(0) = res.column(0).row(0) * scale.x;
	res.column(0).row(1) = res.column(0).row(1) * scale.y;
	res.column(0).row(2) = res.column(0).row(2) * scale.z;

	res.column(1).row(0) = res.column(1).row(0) * scale.x;
	res.column(1).row(1) = res.column(1).row(1) * scale.y;
	res.column(1).row(2) = res.column(1).row(2) * scale.z;

	res.column(2).row(0) = res.column(2).row(0) * scale.x;
	res.column(2).row(1) = res.column(2).row(1) * scale.y;
	res.column(2).row(2) = res.column(2).row(2) * scale.z;

	res.column(3).row(0) = position.x;
	res.column(3).row(1) = position.y;
	res.column(3).row(2) = position.z;

	return res;
}

template <typename T>
constexpr transform3_T<T> transform3_T<T>::operator*(
    const transform3_T<T>& t) const
{
	transform3_T<T> res{*this};
	// res.position = rotation *
	//                   vector3_T{
	//                       scale.x * t.position.x,  //
	//                       scale.y * t.position.y,  //
	//                       scale.z * t.position.z,  //
	//                   } +
	//               position;
	// res.rotation = rotation * t.rotation;
	// res.scale = vector3_T{
	//    scale.x * t.scale.x,  //
	//    scale.y * t.scale.y,  //
	//    scale.z * t.scale.z,  //
	//};

	// res.position = res.position * t.rotation;
	// res.rotation = res.rotation * t.rotation;
	////res.scale = t.rotation * res.scale;

	// res.position.x *= t.scale.x;
	// res.position.y *= t.scale.y;
	// res.position.z *= t.scale.z;
	// res.scale.x *= t.scale.x;
	// res.scale.y *= t.scale.y;
	// res.scale.z *= t.scale.z;

	res.position += t.position;

	return res;
}

template <typename T>
constexpr vector3_T<T> transform3_T<T>::operator*(vector3_T<T> v) const
{
	vector3_T<T> res = rotation * v;
	res.x *= scale.x;
	res.y *= scale.y;
	res.z *= scale.z;
	return res + position;
}

template <typename T>
constexpr quaternion_T<T> transform3_T<T>::operator*(quaternion_T<T> q) const
{
	return rotation * q;
}

template <typename T>
constexpr transform3_T<T> transform3_T<T>::identity()
{
	return {
	    .position = vector3_T<T>::zero(),
	    .rotation = quaternion_T<T>::identity(),
	    .scale = vector3_T<T>::one(),
	};
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, transform3_T<T> t)
{
	// clang-format off
	return os << "transform3_T(position = " << t.position << ",\n"
	          << "             rotation = " << t.rotation << ",\n"
	          << "             scale =    " << t.scale << ")";
	// clang-format on
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_TRANSFORM3_HPP
