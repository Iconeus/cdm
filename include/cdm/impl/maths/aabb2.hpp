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

#ifndef CDM_MATHS_IMPL_AABB2_HPP
#define CDM_MATHS_IMPL_AABB2_HPP 1

#include <cdm/decl/maths/aabb2.hpp>
#include <cdm/decl/maths/vector2.hpp>

namespace cdm
{
template <typename T>
constexpr bool aabb2_T<T>::contains(vector2_T<T> v) const
{
	return (v.x >= origin.x) && (v.x <= origin.x + dimention.x) &&
	       (v.y >= origin.y) && (v.y <= origin.y + dimention.y);
}

template <typename T>
constexpr bool collides(aabb2_T<T> r1, aabb2_T<T> r2)
{
	return collides(r1, r2.origin) ||
	       collides(r1, r2.origin + vector2_T<T>(r2.dimention.x, T(0))) ||
	       collides(r1, r2.origin + vector2_T<T>(T(0), r2.dimention.y)) ||
	       collides(r1, r2.origin + r2.dimention);
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_AABB2_HPP
