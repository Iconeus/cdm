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

#ifndef CDM_MATHS_IMPL_PLANE_HPP
#define CDM_MATHS_IMPL_PLANE_HPP 1

#include <cdm/decl/maths/plane.hpp>
#include <cdm/decl/maths/ray3.hpp>
#include <cdm/decl/maths/vector3.hpp>

#include <ostream>

namespace cdm
{
template <typename T>
template <typename U>
constexpr plane_T<T>::operator plane_T<U>() const
{
	return plane_T<U>{static_cast<vector3_T<U>>(origin),
	                  static_cast<direction3_T<U>>(normal)};
}

template <typename T>
constexpr T plane_T<T>::evaluate(vector3_T<T> point) const
{
	return normal.x() * (point.x - origin.x) +  //
	       normal.y() * (point.y - origin.y) +  //
	       normal.z() * (point.z - origin.z);   //
}

template <typename T>
constexpr vector3_T<T> plane_T<T>::project3d(vector3_T<T> point) const
{
	T distance = evaluate(point);
	return point - normal * distance;
}

template <typename T>
constexpr vector2_T<T> plane_T<T>::project2d(
    vector3_T<T> point,
    direction3_T<T> plane_Tangent) const
{
	auto bitangent = direction3_T<T>(cross(normal, plane_Tangent));
	auto tangent = direction3_T<T>(cross(bitangent, normal));

	auto TBN = matrix3_T<T>::rows(
	    vector3_T<T>(tangent), vector3_T<T>(bitangent), vector3_T<T>(normal));

	vector3_T<T> plane_space_point = point - origin;

	return (TBN * plane_space_point).xy();
}

template <typename T>
constexpr vector3_T<T> plane_T<T>::unproject(
    vector2_T<T> point,
    direction3_T<T> plane_Tangent) const
{
	auto bitangent = direction3_T<T>(cross(normal, plane_Tangent));
	auto tangent = direction3_T<T>(cross(bitangent, normal));

	auto invTBN =
	    matrix3_T<T>::rows(vector3_T<T>(tangent), vector3_T<T>(bitangent),
	                       vector3_T<T>(normal))
	        .get_inversed();

	auto plane_space_point = vector3_T<T>{point, T(0)};

	return (invTBN * plane_space_point) + origin;
}

template <typename T>
constexpr direction3_T<T> plane_T<T>::computeTangent(T epsilon_) const
{
	auto tangent = project3d(vector3_T{T(1), T(0), T(0)} + origin) - origin;
	if (norm_squared(tangent) < epsilon_)
		return direction3_T<T>(
		    project3d(vector3_T{T(0), T(1), T(0)} + origin) - origin);
	return direction3_T<T>(tangent);
}

template <typename T>
constexpr bool collides(const plane_T<T>& plane,
                        ray3_T<T> r,
                        vector3_T<T>& collision_point)
{
	T denom = dot(plane.normal, r.direction);
	if (abs(denom) > T(0.0001))
	{
		T t =
		    -dot(plane.origin - r.origin, vector3_T<T>(plane.normal)) / denom;
		if (t >= T(0))
		{
			collision_point = r.origin + r.direction * t;
			return true;
		}
	}
	return false;
}

template <typename T>
constexpr bool collides_bidirectional(const plane_T<T>& plane,
                                      ray3_T<T> r,
                                      vector3_T<T>& collision_point)
{
	T denom = dot(plane.normal, r.direction);
	if (abs(denom) > T(0.0001))
	{
		T t =
		    -dot(plane.origin - r.origin, vector3_T<T>(plane.normal)) / denom;

		collision_point = r.origin + *r.direction * t;
		return true;
	}
	return false;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, plane_T<T> p)
{
	return os << "plane_T(origin = " << p.origin << ", normal = " << *p.normal
	          << ")";
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_PLANE_HPP
