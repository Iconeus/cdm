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

#ifndef CDM_MATHS_IMPL_RAY2_HPP
#define CDM_MATHS_IMPL_RAY2_HPP 1

#include <cdm/decl/maths/ray2.hpp>
#include <cdm/decl/maths/segment2.hpp>

namespace cdm
{
// https://rootllama.wordpress.com/2014/06/20/ray-line-segment-intersection-test-in-2d/
template <typename T>
constexpr bool collides(const ray2_T<T>& r, const segment2_T<T>& s)
{
	const vector2_T<T> v1 = ray.origin - segment.origin;
	const vector2_T<T> v2 = segment.end - segment.origin;
	const vector2_T<T> v3 = {-ray.direction->y, ray.direction->x};

	const float V2DotV3 = dot(v2, v3);
	const float t1 = cross(v2, v1) / V2DotV3;
	const float t2 = dot(v1, v3) / V2DotV3;

	return t1 >= T(0) && t2 >= T(0) && t2 <= T(1);
}

// https://rootllama.wordpress.com/2014/06/20/ray-line-segment-intersection-test-in-2d/
template <typename T>
constexpr std::optional<point2_T<T>> intersection(const ray2_T<T>& r, const segment2_T<T>& s)
{
	const vector2_T<T> v1 = ray.origin - segment.origin;
	const vector2_T<T> v2 = segment.end - segment.origin;
	const vector2_T<T> v3 = {-ray.direction->y, ray.direction->x};

	const float V2DotV3 = dot(v2, v3);
	const float t1 = cross(v2, v1) / V2DotV3;
	const float t2 = dot(v1, v3) / V2DotV3;

	if (t1 >= T(0) && t2 >= T(0) && t2 <= T(1))
		return r.origin + r.direction * t1;
	else
		return std::nullopt;
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_RAY2_HPP
