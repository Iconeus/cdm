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

#ifndef CDM_MATHS_IMPL_AABB3_HPP
#define CDM_MATHS_IMPL_AABB3_HPP 1

#include <cdm/decl/maths/aabb3.hpp>
#include <cdm/decl/maths/vector3.hpp>

namespace cdm
{
template <typename T>
constexpr bool aabb3_T<T>::contains(vector3_T<T> p) const
{
	return p.x >= min.x && p.x <= max.x && p.y >= min.y && p.y <= max.y &&
	       p.z >= min.z && p.z <= max.z;
}

template <typename T>
constexpr vector3_T<T> aabb3_T<T>::get_center() const
{
	return (max + min) / T(2);
}

template <typename T>
constexpr aabb3_T<T> aabb3_T<T>::operator+(aabb3_T<T> rhs) const
{
	aabb3_T<T> res;
	res.min.x = std::min(min.x, rhs.min.x);
	res.min.y = std::min(min.y, rhs.min.y);
	res.min.z = std::min(min.z, rhs.min.z);
	res.max.x = std::max(max.x, rhs.max.x);
	res.max.y = std::max(max.y, rhs.max.y);
	res.max.z = std::max(max.z, rhs.max.z);

	return res;
}

template <typename T>
constexpr bool collides(aabb3_T<T> b, ray3_T<T> r)
{
	constexpr vector3_T<T> inv{
	    T(1) / r.direction->x,  //
	    T(1) / r.direction->y,  //
	    T(1) / r.direction->z   //
	};

	T t1 = (b.min.x - r.origin.x) * inv.x;
	T t2 = (b.max.x - r.origin.x) * inv.x;

	T tmin = std::min(t1, t2);
	T tmax = std::max(t1, t2);

	t1 = (b.min.y - r.origin.y) * inv.y;
	t2 = (b.max.y - r.origin.y) * inv.y;

	tmin = std::max(tmin, std::min(t1, t2));
	tmax = std::min(tmax, std::max(t1, t2));

	t1 = (b.min.z - r.origin.z) * inv.z;
	t2 = (b.max.z - r.origin.z) * inv.z;

	tmin = std::max(tmin, std::min(t1, t2));
	tmax = std::min(tmax, std::max(t1, t2));

	return tmax >= tmin;
}

template <typename T>
constexpr bool collides(aabb3_T<T> b1, aabb3_T<T> b2)
{
	if (b1.contains(b2.min))
		return true;
	if (b1.contains(b2.max))
		return true;
	if (b2.contains(b1.min))
		return true;
	if (b2.contains(b1.max))
		return true;

	std::array<vector3_T<T>, 6> otherPoints;
	otherPoints[0] = {b1.min.x, b1.min.y, b1.max.z};
	otherPoints[1] = {b1.min.x, b1.max.y, b1.min.z};
	otherPoints[2] = {b1.max.x, b1.min.y, b1.min.z};
	otherPoints[3] = {b1.min.x, b1.max.y, b1.max.z};
	otherPoints[4] = {b1.max.x, b1.min.y, b1.max.z};
	otherPoints[5] = {b1.max.x, b1.max.y, b1.min.z};

	for (auto& p : otherPoints)
		if (b2.contains(p))
			return true;

	otherPoints[0] = {b2.min.x, b2.min.y, b2.max.z};
	otherPoints[1] = {b2.min.x, b2.max.y, b2.min.z};
	otherPoints[2] = {b2.max.x, b2.min.y, b2.min.z};
	otherPoints[3] = {b2.min.x, b2.max.y, b2.max.z};
	otherPoints[4] = {b2.max.x, b2.min.y, b2.max.z};
	otherPoints[5] = {b2.max.x, b2.max.y, b2.min.z};

	for (auto& p : otherPoints)
		if (b1.contains(p))
			return true;

	return false;
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_AABB3_HPP
