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

#ifndef CDM_MATHS_DECL_AABB2_HPP
#define CDM_MATHS_DECL_AABB2_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>

namespace cdm
{
template <typename T>
struct aabb2_T
{
	vector2_T<T> origin;
	vector2_T<T> dimention;

	constexpr bool contains(vector2_T<T> v) const;

	using underlying_type = T;
};

template <typename T>
constexpr bool collides(aabb2_T<T> r1, aabb2_T<T> r2);

using aabb2 = aabb2_T<float>;
using aabb2d = aabb2_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_AABB2_HPP
