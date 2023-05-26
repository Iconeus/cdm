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

#ifndef CDM_MATHS_IMPL_ORIENTED_PLANE_HPP
#define CDM_MATHS_IMPL_ORIENTED_PLANE_HPP 1

#include <cdm/decl/maths/oriented_plane.hpp>
#include <cdm/decl/maths/plane.hpp>
#include <cdm/decl/maths/ray3.hpp>
#include <cdm/decl/maths/vector3.hpp>

#include <ostream>

namespace cdm
{
template <typename T>
constexpr oriented_plane_T<T>::oriented_plane_T(vector3_T<T> origin_,
                                                direction3_T<T> normal_,
                                                direction3_T<T> tangent_)
    : origin(origin_), normal(normal_)
{
	const auto bitangent = direction3_T<T>(cross(normal, tangent_));
	tangent = direction3_T<T>(cross(bitangent, normal));
}

template <typename T>
constexpr oriented_plane_T<T>::oriented_plane_T(plane_T<T> plane,
                                                direction3_T<T> tangent_)
    : oriented_plane_T(plane.origin, plane.normal, tangent_)
{
}

template <typename T>
template <typename U>
constexpr oriented_plane_T<T>::operator oriented_plane_T<U>() const
{
	return oriented_plane_T<U>{
	    static_cast<vector3_T<U>>(origin),
	    static_cast<direction3_T<U>>(normal),
	    static_cast<direction3_T<U>>(tangent),
	};
}

template <typename T>
constexpr T oriented_plane_T<T>::evaluate(vector3_T<T> point) const
{
	return normal.x() * (point.x - origin.x) +  //
	       normal.y() * (point.y - origin.y) +  //
	       normal.z() * (point.z - origin.z);   //
}

template <typename T>
constexpr vector3_T<T> oriented_plane_T<T>::project3d(vector3_T<T> point) const
{
	T distance = evaluate(point);
	return point - vector3_T<T>(normal) * distance;
}

template <typename T>
constexpr vector2_T<T> oriented_plane_T<T>::project2d(vector3_T<T> point) const
{
	const auto bitangent = direction3_T<T>(cross(normal, tangent));

	const auto TBN = matrix3_T<T>::rows(
	    vector3_T<T>(tangent), vector3_T<T>(bitangent), vector3_T<T>(normal));

	const vector3_T<T> pointInPlaneSpace = point - origin;

	return (TBN * pointInPlaneSpace).xy();
}

template <typename T>
constexpr vector3_T<T> oriented_plane_T<T>::unproject(vector2_T<T> point) const
{
	const auto bitangent = direction3_T<T>(cross(normal, tangent));

	const auto invTBN =
	    matrix3_T<T>::rows(vector3_T<T>(tangent), vector3_T<T>(bitangent),
	                       vector3_T<T>(normal))
	        .get_inversed();

	auto pointInPlaneSpace = vector3_T<T>{point, T(0)};

	return (invTBN * pointInPlaneSpace) + origin;
}

template <typename T>
constexpr bool collides(const oriented_plane_T<T>& plane,
                        ray3_T<T> r,
                        vector3_T<T>& collision_point,
                        T e)
{
	T denom = dot(plane.normal, r.direction);
	if (abs(denom) > e)
	{
		T t = -dot(plane.origin - r.origin, plane.normal) / denom;
		if (t >= T(0))
		{
			collision_point = r.origin + r.direction * t;
			return true;
		}
	}
	return false;
}

template <typename T>
constexpr bool collides_bidirectional(const oriented_plane_T<T>& plane,
                                      ray3_T<T> r,
                                      vector3_T<T>& collision_point,
                                      T e)
{
	T denom = dot(plane.normal, r.direction);
	if (abs(denom) > e)
	{
		T t =
		    -dot(plane.origin - r.origin, vector3_T<T>(plane.normal)) / denom;

		collision_point = r.origin + r.direction * t;
		return true;
	}
	return false;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, oriented_plane_T<T> p)
{
	// clang-format off
	return os << "oriented_plane_T(origin = " << p.origin
	                         << ", normal = " << p.normal
	                         << ", tangent = " << p.tangent
	                         << ")";
	// clang-format on
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_ORIENTED_PLANE_HPP
