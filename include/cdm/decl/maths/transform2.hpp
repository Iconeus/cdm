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

#ifndef CDM_MATHS_DECL_TRANSFORM2_HPP
#define CDM_MATHS_DECL_TRANSFORM2_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>

namespace cdm
{
template <typename T>
struct transform2_T
{
	vector2_T<T> position;
	normalized<complex_T<T>> rotation;
	vector2_T<T> scale;

	constexpr transform2_T operator*(const transform2_T& t) const;
	constexpr vector2_T<T> operator*(vector2_T<T> v) const;

	static constexpr transform2_T identity();

	using underlying_type = T;
};

using transform2 = transform2_T<float>;
using transform2d = transform2_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_TRANSFORM2_HPP
