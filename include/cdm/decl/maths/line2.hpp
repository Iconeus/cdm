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

#ifndef CDM_MATHS_DECL_LINE2_HPP
#define CDM_MATHS_DECL_LINE2_HPP 1

#include <cdm/decl/maths/constants.hpp>
#include <cdm/decl/maths/forward_declarations.hpp>

namespace cdm
{
template <typename T, line_representation representation>
struct line2_T
{
};

template <typename T>
struct line2_T<T, line_representation::SlopeIntercept>
{
	T slope;
	T y_intercept;

	line2_T() = default;
	line2_T(T s, T yi);
	line2_T(vector2_T<T> direction, T e = T(epsilon));
	line2_T(vector2_T<T> point1, vector2_T<T> point2);

	vector2_T<T> resolve_for_x(T x) const;
	vector2_T<T> resolve_for_y(T y) const;

	using underlying_type = T;
};

template <typename T>
struct line2_T<T, line_representation::Points>
{
	vector2_T<T> p1;
	vector2_T<T> p2;

	line2_T() = default;
	line2_T(vector2_T<T> point1, vector2_T<T> point2);

	// vector2_T<T> resolve_for_x(T x) const;
	// vector2_T<T> resolve_for_y(T y) const;

	using underlying_type = T;
};

template <line_representation representation>
using line2 = line2_T<float, representation>;
template <line_representation representation>
using line2d = line2_T<double, representation>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_LINE2_HPP
