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

#ifndef CDM_MATHS_DECL_TRANSFORM3_HPP
#define CDM_MATHS_DECL_TRANSFORM3_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>

#include <iosfwd>

namespace cdm
{
template <typename T>
struct transform3_T
{
	vector3_T<T> position;
	quaternion_T<T> rotation;
	vector3_T<T> scale;

	constexpr transform3_T& translate_absolute(vector3_T<T> t);
	constexpr transform3_T& translate_relative(vector3_T<T> t);
	constexpr transform3_T& rotate(quaternion_T<T> r);

	matrix4_T<T> to_matrix4() const;

	constexpr transform3_T operator*(const transform3_T& t) const;
	constexpr vector3_T<T> operator*(vector3_T<T> v) const;
	constexpr quaternion_T<T> operator*(quaternion_T<T> q) const;

	static constexpr transform3_T identity();

	using underlying_type = T;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, transform3_T<T> t);

using transform3 = transform3_T<float>;
using transform3d = transform3_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_TRANSFORM3_HPP