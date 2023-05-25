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

#ifndef CDM_MATHS_IMPL_VECTOR2_HPP
#define CDM_MATHS_IMPL_VECTOR2_HPP 1

#include <cdm/decl/maths/vector2.hpp>

#include <cmath>
#include <ostream>

namespace cdm
{
template <typename T>
constexpr vector2_T<T>::vector2_T(T x_, T y_) : x{x_}, y{y_}
{
}

template <typename T>
constexpr vector2_T<T>::vector2_T(std::array<T, 2> a) : vector2_T(a[0], a[1])
{
}

template <typename T>
template <typename U>
constexpr vector2_T<T>::operator vector2_T<U>() const
{
	return vector2_T<U>{static_cast<U>(x), static_cast<U>(y)};
}

template <typename T>
constexpr vector2_T<T>::operator std::array<T, 2>() const
{
	return {x, y};
}

template <typename T>
template <typename U>
constexpr std::array<U, 2> vector2_T<T>::to_array() const
{
	return {static_cast<U>(x), static_cast<U>(y)};
}

template <typename T>
inline T vector2_T<T>::norm() const
{
	return std::sqrt(norm_squared());
}

template <typename T>
constexpr T vector2_T<T>::norm_squared() const
{
	return x * x + y * y;
}

template <typename T>
inline vector2_T<T>& vector2_T<T>::normalize()
{
	T n{norm()};
	x /= n;
	y /= n;
	return *this;
}

template <typename T>
inline vector2_T<T> vector2_T<T>::get_normalized() const
{
	vector2_T res{*this};
	res.normalize();
	return res;
}

template <typename T>
constexpr vector2_T<T>& vector2_T<T>::clamp(vector2_T<T> min, vector2_T<T> max)
{
	x = std::clamp(x, min.x, max.x);
	y = std::clamp(y, min.y, max.y);
	return *this;
}

template <typename T>
constexpr vector2_T<T> vector2_T<T>::get_clamped(vector2_T<T> min,
                                                 vector2_T<T> max) const
{
	vector2_T res{*this};
	res.clamp(min, max);
	return res;
}

template <typename T>
constexpr T& vector2_T<T>::operator[](size_t i)
{
	if (i == 0)
		return x;
	else
		return y;
}

template <typename T>
constexpr const T& vector2_T<T>::operator[](size_t i) const
{
	if (i == 0)
		return x;
	else
		return y;
}

template <typename T>
constexpr vector2_T<T> vector2_T<T>::operator+(vector2_T<T> v) const
{
	return {x + v.x, y + v.y};
}

template <typename T>
constexpr vector2_T<T> vector2_T<T>::operator-(vector2_T<T> v) const
{
	return {x - v.x, y - v.y};
}

template <typename T>
constexpr vector2_T<T>& vector2_T<T>::operator+=(vector2_T<T> v)
{
	*this = *this + v;
	return *this;
}

template <typename T>
constexpr vector2_T<T>& vector2_T<T>::operator-=(vector2_T<T> v)
{
	*this = *this - v;
	return *this;
}

template <typename T>
constexpr vector2_T<T> vector2_T<T>::operator-() const
{
	return {-x, -y};
}

template <typename T>
constexpr bool vector2_T<T>::operator==(vector2_T<T> v) const
{
	return x == v.x && y == v.y;
}

template <typename T>
constexpr bool vector2_T<T>::operator!=(vector2_T<T> v) const
{
	return !operator==(v);
}

template <typename T>
constexpr vector2_T<T> vector2_T<T>::zero()
{
	return {T(0), T(0)};
}

template <typename T>
constexpr vector2_T<T> vector2_T<T>::one()
{
	return {T(1), T(1)};
}

template <typename T>
constexpr vector2_T<T> operator*(T f, vector2_T<T> v)
{
	return v * f;
}

template <typename T>
constexpr vector2_T<T> operator*(vector2_T<T> v, T f)
{
	return {v.x * f, v.y * f};
}

template <typename T>
constexpr vector2_T<T> operator/(vector2_T<T> v, T f)
{
	return {v.x / f, v.y / f};
}

template <typename T>
constexpr vector2_T<T>& operator*=(vector2_T<T>& v, T f)
{
	v = v * f;
	return v;
}

template <typename T>
constexpr vector2_T<T>& operator/=(vector2_T<T>& v, T f)
{
	v = v / f;
	return v;
}

template <typename T>
inline T norm(vector2_T<T> v)
{
	return std::sqrt(norm_squared(v));
}

template <typename T>
constexpr T norm_squared(vector2_T<T> v)
{
	return v.x * v.x + v.y * v.y;
}

template <typename T>
inline vector2_T<T> normalize(vector2_T<T> v)
{
	T n = v.norm();
	v.x /= n;
	v.y /= n;
	return v;
}

template <typename T>
constexpr T dot(vector2_T<T> lhs, vector2_T<T> rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

template <typename T>
constexpr T cross(vector2_T<T> lhs, vector2_T<T> rhs)
{
	return lhs.x * rhs.y - lhs.y * rhs.x;
}

template <typename T>
constexpr vector2_T<T> lerp(vector2_T<T> begin, vector2_T<T> end, T percent)
{
	// return (end - begin) * percent + begin;
	return {
	    std::lerp(begin.x, end.x, percent),
	    std::lerp(begin.y, end.y, percent),
	};
}

template <typename T>
inline vector2_T<T> nlerp(vector2_T<T> begin, vector2_T<T> end, T percent)
{
	return lerp(begin, end, percent).get_normalized();
}

template <typename T>
inline vector2_T<T> slerp(vector2_T<T> begin, vector2_T<T> end, T percent)
{
	const radian_T angle = angle_between(begin, end) * percent;
	const T s = sin(angle);
	const T c = cos(angle);

	normalized<vector2_T<T>> res{
	    {c * begin.x - s * begin.y, s * begin.x + c * begin.y}};

	T f = cdm::lerp(begin.norm(), end.norm(), percent);
	return res * f;
}

template <typename T>
inline T distance_between(vector2_T<T> v1, vector2_T<T> v2)
{
	return (v1 - v2).norm();
}

template <typename T>
constexpr T distance_squared_between(vector2_T<T> v1, vector2_T<T> v2)
{
	return (v1 - v2).norm_squared();
}

template <typename T>
constexpr vector2_T<T> from_to(vector2_T<T> from, vector2_T<T> to)
{
	return {to.x - from.x, to.y - from.y};
}

template <typename T>
inline radian_T<T> angle_between(vector2_T<T> v1, vector2_T<T> v2)
{
	return radian_T{atan2(v2.y, v2.x) - atan2(v1.y, v1.x)};
}

template <typename T>
constexpr bool nearly_equal(vector2_T<T> v1, vector2_T<T> v2, T e)
{
	return cdm::nearly_equal(v1.x, v2.x, e) &&
	       cdm::nearly_equal(v1.y, v2.y, e);
}

template <typename T>
constexpr vector2_T<T> element_wise_min(vector2_T<T> v0, vector2_T<T> v1)
{
	return {
	    std::min(v0.x, v1.x),
	    std::min(v0.y, v1.y),
	};
}

template <typename T>
constexpr vector2_T<T> element_wise_max(vector2_T<T> v0, vector2_T<T> v1)
{
	return {
	    std::max(v0.x, v1.x),
	    std::max(v0.y, v1.y),
	};
}

template <typename T>
inline vector2_T<T> element_wise_abs(vector2_T<T> v)
{
	return {
	    std::abs(v.x),
	    std::abs(v.y),
	};
}

template <typename T>
constexpr vector2_T<T> element_wise_lerp(
    vector2_T<T> begin,
    vector2_T<T> end,
    const vector2_T<const normalized_value_T<T>>& percent)
{
	return {
	    std::lerp(begin.x, end.x, percent.x.value()),
	    std::lerp(begin.y, end.y, percent.y.value()),
	};
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, vector2_T<T> v)
{
	return os << "vector2_T(" << v.x << ", " << v.y << ")";
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_VECTOR2_HPP
