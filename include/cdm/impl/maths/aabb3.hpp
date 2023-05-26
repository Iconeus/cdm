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
constexpr bool aabb3_T<T>::contains(point3_T<T> p) const
{
	return p.x >= min.x && p.x <= max.x &&  //
	       p.y >= min.y && p.y <= max.y &&  //
	       p.z >= min.z && p.z <= max.z;    //
}

template <typename T>
constexpr point3_T<T> aabb3_T<T>::get_center() const
{
	return (max + min) / T(2);
}

template <typename T>
constexpr std::array<point3_T<T>, 8> aabb3_T<T>::get_points() const
{
	return std::array<point3_T<T>, 8>{
	    point3_T<T>{box.min.x, box.min.y, box.min.z},
	    point3_T<T>{box.max.x, box.min.y, box.min.z},
	    point3_T<T>{box.min.x, box.max.y, box.min.z},
	    point3_T<T>{box.max.x, box.max.y, box.min.z},
	    point3_T<T>{box.min.x, box.min.y, box.max.z},
	    point3_T<T>{box.max.x, box.min.y, box.max.z},
	    point3_T<T>{box.min.x, box.max.y, box.max.z},
	    point3_T<T>{box.max.x, box.max.y, box.max.z},
	};
}

template <typename T>
constexpr aabb3_T<T>& aabb3_T<T>::grow(const aabb3_T<T>& box)
{
	grow(box.min);
	grow(box.max);
	return *this;
}

template <typename T>
constexpr aabb3_T<T>& aabb3_T<T>::grow(point3_T<T> point)
{
	box.min = cdm::element_wise_min(box.min, point);
	box.max = cdm::element_wise_max(box.max, point);
	return *this;
}

template <typename T>
constexpr aabb3_T<T> aabb3_T<T>::operator+(const aabb3_T<T>& rhs) const
{
	aabb3_T<T> res = *this;
	res.grow(rhs);
	return res;
}

template <typename T>
constexpr aabb3_T<T> aabb3_T<T>::operator+(point3_T<T> rhs) const
{
	aabb3_T<T> res = *this;
	res.grow(rhs);
	return res;
}

template <typename T>
constexpr aabb3_T<T>& aabb3_T<T>::operator+=(const aabb3_T<T>& rhs)
{
	return grow(rhs);
}

template <typename T>
constexpr aabb3_T<T>& aabb3_T<T>::operator+=(point3_T<T> rhs)
{
	return grow(rhs);
}

template <typename T>
constexpr aabb3_T<T> operator+(point3_T<T> lhs, const aabb3_T<T>& rhs)
{
	return rhs + lhs;
}

template <typename T>
constexpr bool collides(const aabb3_T<T>& b, const ray3_T<T>& r)
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
constexpr bool collides(const aabb3_T<T>& b, const plane_T<T>& p)
{
	int evals = 0;
	for (const auto& point : b.get_points())
	{
		const T eval = p.evaluate(point);
		evals += -int(eval < T(0)) + int(eval > T(0));
	}

	return std::abs(evals) != 8;
}

template <typename T>
constexpr bool collides(const aabb3_T<T>& b, const oriented_plane_T<T>& p)
{
	int evals = 0;
	for (const auto& point : b.get_points())
	{
		const T eval = p.evaluate(point);
		evals += -int(eval < T(0)) + int(eval > T(0));
	}

	return std::abs(evals) != 8;
}

template <typename T>
constexpr bool collides(const aabb3_T<T>& b0, const aabb3_T<T>& b1)
{
	/// TODO this is wrong!
	///
	///         +--------------+
	///         |              |
	///         |              |
	///     +---|--------------|---+
	///     |   |              |   |
	///     |   |              |   |
	///     |   |              |   |
	///     |   |              |   |
	///     +---|--------------|---+
	///         |              |
	///         |              |
	///         +--------------+
	///
	/// ^ this return false
	///

	std::array<point3_T<T>, 8> points = b0.get_points();

	for (auto& p : points)
		if (b1.contains(p))
			return true;

	points = b1.get_points();

	for (auto& p : points)
		if (b0.contains(p))
			return true;

	return false;
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_AABB3_HPP
