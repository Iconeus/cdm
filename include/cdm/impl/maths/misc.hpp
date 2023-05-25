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

#ifndef CDM_MATHS_IMPL_MISC_HPP
#define CDM_MATHS_IMPL_MISC_HPP 1

#include <cdm/decl/maths/misc.hpp>
#include <cdm/impl/maths/normalized_value.hpp>

namespace cdm
{
namespace detail
{
template <int x, int y, typename T>
constexpr T get_quaternion_T_matrix_element(quaternion_T<T> q)
{
	static_assert(x >= 0 && x < 3, "x must be [0;2]");
	static_assert(y >= 0 && y < 3, "y must be [0;2]");
	if constexpr (y == 0)
	{
		if constexpr (x == 0)
			return T(1) - T(2) * (q.y * q.y + q.z * q.z);
		if constexpr (x == 1)
			return T(2) * (q.x * q.y - q.z * q.w);
		if constexpr (x == 2)
			return T(2) * (q.x * q.z + q.y * q.w);
	}
	if constexpr (y == 1)
	{
		if constexpr (x == 0)
			return T(2) * (q.x * q.y + q.z * q.w);
		if constexpr (x == 1)
			return T(1) - T(2) * (q.x * q.x + q.z * q.z);
		if constexpr (x == 2)
			return T(2) * (q.y * q.z - q.x * q.w);
	}
	if constexpr (y == 2)
	{
		if constexpr (x == 0)
			return T(2) * (q.x * q.z - q.y * q.w);
		if constexpr (x == 1)
			return T(2) * (q.y * q.z + q.x * q.w);
		if constexpr (x == 2)
			return T(1) - T(2) * (q.x * q.x + q.y * q.y);
	}
}

template <std::floating_point T>
constexpr T sqrtNewtonRaphson(T x, T curr, T prev)
{
	return curr == prev
	           ? curr
	           : sqrtNewtonRaphson(x, T(0.5) * (curr + x / curr), curr);
}
}  // namespace detail

template <typename Functor, typename T>
inline std::vector<vector3_T<T>> function2D_sampler(const Functor& functor,
                                                    T min,
                                                    T max,
                                                    T step)
{
	std::vector<vector3_T<T>> res;

	if (min > max)
		std::swap(min, max);

	if (step < epsilon)
		step = epsilon;

	for (T f = min; f < max; f += step)
	{
		res.push_back(functor(f));
	}

	return res;
}

template <typename Functor, typename T>
inline std::vector<std::vector<vector3_T<T>>> function3D_sampler(
    const Functor& functor,
    vector2_T<T> min,
    vector2_T<T> max,
    vector2_T<T> step)
{
	std::vector<std::vector<vector3_T<T>>> res;

	if (min.x > max.x)
		std::swap(min.x, max.x);
	if (min.y > max.y)
		std::swap(min.y, max.y);

	if (step.x < epsilon)
		step.x = epsilon;
	if (step.y < epsilon)
		step.y = epsilon;

	size_t xCount = 0;
	size_t yCount = 0;

	for (T x = min.x; x < max.x; x += step.x)
		xCount++;
	for (T y = min.y; y < max.y; y += step.y)
		yCount++;
	res.reserve(yCount);

	for (T y = min.y; y < max.y; y += step.y)
	{
		std::vector<vector3_T<T>> row;
		row.reserve(xCount);
		for (T x = min.x; x < max.x; x += step.x)
		{
			row.push_back(functor(x, y));
		}
		res.push_back(std::move(row));
	}

	return res;
}

template <typename T>
inline bool nearly_equal(T f1, T f2, T e)
{
	return std::abs(f1 - f2) < e;
}

template <typename T>
constexpr int sign(T val)
{
	return (T(0) <= val) - (val < T(0));
}

template <typename T>
constexpr int signnum(T val)
{
	return (T(0) < val) - (val < T(0));
}

template <typename T>
constexpr T element_wise_min(T v0, T v1)
{
	return std::min(v0, v1);
}

template <typename T>
constexpr T element_wise_max(T v0, T v1)
{
	return std::max(v0, v1);
}

template <typename T>
inline T element_wise_abs(T v)
{
	return std::abs(v);
}

template <typename T>
constexpr T element_wise_lerp(T begin,
                              T end,
                              const normalized_value_T<T>& alpha)
{
	return std::lerp(begin, end, alpha.value());
}

template <typename T>
    requires arithmetic<T> || vector<T> || matrix<T>
constexpr T zero()
{
	if constexpr (arithmetic<T>)
		return T(0);
	else
		return T::zero();
}

template <typename T>
    requires arithmetic<T> || vector<T> || matrix<T>
constexpr T one()
{
	if constexpr (arithmetic<T>)
		return T(1);
	else
		return T::one();
}

template <std::floating_point T>
constexpr T sqrt(T x)
{
	return x >= T(0) && x < std::numeric_limits<T>::infinity()
	           ? detail::sqrtNewtonRaphson(x, x, T(0))
	           : std::numeric_limits<T>::quiet_NaN();
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_MISC_HPP
