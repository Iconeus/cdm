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

#ifndef CDM_MATHS_IMPL_SEGMENT3_HPP
#define CDM_MATHS_IMPL_SEGMENT3_HPP 1

#include <cdm/decl/maths/misc.hpp>
#include <cdm/decl/maths/plane.hpp>
#include <cdm/decl/maths/segment3.hpp>
#include <cdm/decl/maths/vector3.hpp>

#include <ostream>

namespace cdm
{
template <typename T>
constexpr bool collides(const segment3_T<T>& seg,
                        const plane_T<T>& plane,
                        T e) noexcept
{
	// distances to point
	T p0 = plane.evaluate(seg.origin);
	T p1 = plane.evaluate(seg.end);

	// are considered on the plane
	if (nearly_equal(p0, T(0), e) || nearly_equal(p1, T(0), e))
		return true;

	// if both points are on the same side of the plane
	if ((p0 > T(0) && p1 > T(0)) || (p0 < T(0) && p1 < T(0)))
		return false;  // no collision

	return true;
}

// I feel like there's a simpler and more efficient way to do this...
template <typename T>
constexpr bool collides(const segment3_T<T>& seg,
                        const plane_T<T>& plane,
                        vector3_T<T>& outPoint,
                        T e) noexcept
{
	// distances to point
	T p0 = plane.evaluate(seg.origin);
	T p1 = plane.evaluate(seg.end);

	// are considered on the plane
	if (nearly_equal(p0, T(0), e))
	{
		outPoint = seg.origin;
		return true;
	}
	if (nearly_equal(p1, T(0), e))
	{
		outPoint = seg.end;
		return true;
	}

	// if both points are on the same side of the plane
	if ((p0 > T(0) && p1 > T(0)) || (p0 < T(0) && p1 < T(0)))
		return false;  // no collision

	value_domain_T<T> d{p0, p1};
	unnormalized_value_T<T> v{d, T(0)};
	normalized_value_T<T> n{v};

	outPoint = element_wise_lerp(seg.origin, seg.end,
	                             vector3_T<normalized_value_T<T>>(n, n, n));

	return true;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, segment3_T<T> t)
{
	// clang-format off
	return os << "segment3_T(origin = " << t.origin << ",\n"
	          << "           end =    " << t.end << ")";
	// clang-format on
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_SEGMENT3_HPP
