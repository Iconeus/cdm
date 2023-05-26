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

#include <array>

namespace cdm
{
template <typename T>
struct aabb2_T
{
	point2_T<T> min;
	point2_T<T> max;
	
	constexpr bool contains(point2_T<T> p) const;

	constexpr point2_T<T> get_center() const;
	constexpr std::array<point2_T<T>, 4> get_points() const;

	constexpr aabb2_T& grow(const aabb2_T& box);
	constexpr aabb2_T& grow(point2_T<T> point);

	constexpr aabb2_T operator+(const aabb2_T& rhs) const;
	constexpr aabb2_T operator+(point2_T<T> rhs) const;
	
	constexpr aabb2_T& operator+=(const aabb2_T& rhs);
	constexpr aabb2_T& operator+=(point2_T<T> rhs);

	using underlying_type = T;
};

template <typename T>
constexpr aabb2_T<T> operator+(point2_T<T> lhs, const aabb2_T<T>& rhs);

template <typename T>
constexpr bool collides(const aabb2_T<T>& b0, const aabb2_T<T>& b1);

using aabb2 = aabb2_T<float>;
using aabb2d = aabb2_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_AABB2_HPP
