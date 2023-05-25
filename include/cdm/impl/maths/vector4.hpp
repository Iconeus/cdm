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

#ifndef CDM_MATHS_IMPL_VECTOR4_HPP
#define CDM_MATHS_IMPL_VECTOR4_HPP 1

#include <cdm/decl/maths/vector2.hpp>
#include <cdm/decl/maths/vector3.hpp>
#include <cdm/decl/maths/vector4.hpp>

#include <ostream>

namespace cdm
{
template <typename T>
constexpr vector4_T<T>::vector4_T(T x_, T y_, T z_, T w_)
    : x{x_}, y{y_}, z{z_}, w{w_}
{
}

template <typename T>
constexpr vector4_T<T>::vector4_T(vector2_T<T> v, T z_, T w_)
    : vector4_T(v.x, v.y, z_, w_)
{
}

template <typename T>
constexpr vector4_T<T>::vector4_T(vector3_T<T> v, T w_)
    : vector4_T(v.x, v.y, v.z, w_)
{
}

template <typename T>
constexpr vector4_T<T>::vector4_T(std::array<T, 4> a)
    : vector4_T(a[0], a[1], a[2], a[3])
{
}

template <typename T>
template <typename U>
constexpr vector4_T<T>::operator vector4_T<U>() const
{
	return vector4_T<U>{static_cast<U>(x), static_cast<U>(y),
	                    static_cast<U>(z), static_cast<U>(w)};
}

template <typename T>
constexpr vector4_T<T>::operator std::array<T, 4>() const
{
	return {x, y, z, w};
}

template <typename T>
template <typename U>
constexpr std::array<U, 4> vector4_T<T>::to_array() const
{
	return {static_cast<U>(x), static_cast<U>(y), static_cast<U>(z),
	        static_cast<U>(w)};
}

template <typename T>
constexpr vector2_T<T> vector4_T<T>::xy() const
{
	return {x, y};
}
template <typename T>
constexpr vector3_T<T> vector4_T<T>::xyz() const
{
	return {x, y, z};
}

template <typename T>
inline T vector4_T<T>::norm() const
{
	return std::sqrt(norm_squared());
}

template <typename T>
constexpr T vector4_T<T>::norm_squared() const
{
	return x * x + y * y + z * z + w * w;
}

template <typename T>
inline vector4_T<T>& vector4_T<T>::normalize()
{
	T n = norm();
	x /= n;
	y /= n;
	z /= n;
	w /= n;
	return *this;
}

template <typename T>
inline vector4_T<T> vector4_T<T>::get_normalized() const
{
	vector4_T res{*this};
	res.normalize();
	return res;
}

template <typename T>
constexpr vector4_T<T>& vector4_T<T>::clamp(vector4_T<T> min, vector4_T<T> max)
{
	x = std::clamp(x, min.x, max.x);
	y = std::clamp(y, min.y, max.y);
	z = std::clamp(z, min.z, max.z);
	w = std::clamp(w, min.w, max.w);
	return *this;
}

template <typename T>
constexpr vector4_T<T> vector4_T<T>::get_clamped(vector4_T<T> min,
                                                 vector4_T<T> max) const
{
	vector4_T res{*this};
	res.clamp(min, max);
	return res;
}

template <typename T>
constexpr vector4_T<T> vector4_T<T>::operator+(vector4_T<T> v) const
{
	return {x + v.x, y + v.y, z + v.z, w + v.w};
}
template <typename T>
constexpr vector4_T<T> vector4_T<T>::operator-(vector4_T<T> v) const
{
	return {x - v.x, y - v.y, z - v.z, w - v.w};
}

template <typename T>
constexpr vector4_T<T>& vector4_T<T>::operator+=(vector4_T<T> v)
{
	*this = *this + v;
	return *this;
}
template <typename T>
constexpr vector4_T<T>& vector4_T<T>::operator-=(vector4_T<T> v)
{
	*this = *this - v;
	return *this;
}

template <typename T>
constexpr vector4_T<T> vector4_T<T>::operator-() const
{
	return {-x, -y, -z, -w};
}

template <typename T>
constexpr bool vector4_T<T>::operator==(vector4_T<T> v) const
{
	return x == v.x && y == v.y && z == v.z && w == v.w;
}

template <typename T>
constexpr bool vector4_T<T>::operator!=(vector4_T<T> v) const
{
	return !operator==(v);
}

template <typename T>
constexpr vector4_T<T> vector4_T<T>::zero()
{
	return {T(0), T(0), T(0), T(0)};
}

template <typename T>
constexpr vector4_T<T> vector4_T<T>::one()
{
	return {T(1), T(1), T(1), T(1)};
}

template <typename T>
constexpr vector4_T<T> operator*(T f, vector4_T<T> v)
{
	return v * f;
}

template <typename T>
constexpr vector4_T<T> operator*(vector4_T<T> v, T f)
{
	return {v.x * f, v.y * f, v.z * f, v.w * f};
}

template <typename T>
constexpr vector4_T<T> operator/(vector4_T<T> v, T f)
{
	return {v.x / f, v.y / f, v.z / f, v.w / f};
}

template <typename T>
constexpr vector4_T<T>& operator*=(vector4_T<T>& v, T f)
{
	v = v * f;
	return v;
}

template <typename T>
constexpr vector4_T<T>& operator/=(vector4_T<T>& v, T f)
{
	v = v / f;
	return v;
}

template <typename T>
inline T norm(vector4_T<T> v)
{
	return v.norm();
}

template <typename T>
constexpr T norm_squared(vector4_T<T> v)
{
	return v.norm_squared();
}

template <typename T>
inline vector4_T<T> normalize(vector4_T<T> v)
{
	v.normalize();
	return v;
}

template <typename T>
constexpr T dot(vector4_T<T> lhs, vector4_T<T> rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

template <typename T>
constexpr vector4_T<T> lerp(vector4_T<T> begin, vector4_T<T> end, T percent)
{
	return (end - begin) * percent + begin;
}

template <typename T>
inline vector4_T<T> nlerp(vector4_T<T> begin, vector4_T<T> end, T percent)
{
	return normalize(lerp(begin, end, percent));
}

template <typename T>
inline T distance_between(vector4_T<T> v1, vector4_T<T> v2)
{
	return (v1 - v2).norm();
}

template <typename T>
constexpr T distance_squared_between(vector4_T<T> v1, vector4_T<T> v2)
{
	return (v1 - v2).norm_squared();
}

template <typename T>
constexpr vector4_T<T> from_to(vector4_T<T> from, vector4_T<T> to)
{
	return to - from;
}

template <typename T>
constexpr bool nearly_equal(vector4_T<T> v1, vector4_T<T> v2, T e)
{
	return nearly_equal(v1.x, v2.x, e) && nearly_equal(v1.y, v2.y, e) &&
	       nearly_equal(v1.z, v2.z, e) && nearly_equal(v1.w, v2.w, e);
}

template <typename T>
constexpr vector4_T<T> element_wise_min(vector4_T<T> v0, vector4_T<T> v1)
{
	return {
	    std::min(v0.x, v1.x),
	    std::min(v0.y, v1.y),
	    std::min(v0.z, v1.z),
	    std::min(v0.w, v1.w),
	};
}

template <typename T>
constexpr vector4_T<T> element_wise_max(vector4_T<T> v0, vector4_T<T> v1)
{
	return {
	    std::max(v0.x, v1.x),
	    std::max(v0.y, v1.y),
	    std::max(v0.z, v1.z),
	    std::max(v0.w, v1.w),
	};
}

template <typename T>
inline vector4_T<T> element_wise_abs(vector4_T<T> v)
{
	return {
	    std::abs(v.x),
	    std::abs(v.y),
	    std::abs(v.z),
	    std::abs(v.w),
	};
}

// template <typename T>
// constexpr vector4_T<T> element_wise_lerp(vector4_T<T> begin,
//                                          vector4_T<T> end,
//                                          const vector4_T<const
//                                          normalized_value_T<T>>& percent)
//{
//	return {
//	    std::lerp(begin.x, end.x, percent.x.value()),
//	    std::lerp(begin.y, end.y, percent.y.value()),
//	    std::lerp(begin.z, end.z, percent.z.value()),
//	    std::lerp(begin.w, end.w, percent.w.value()),
//	};
// }

template <typename T>
inline std::ostream& operator<<(std::ostream& os, vector4_T<T> v)
{
	return os << "vector4_T(" << v.x << ", " << v.y << ", " << v.z << ", "
	          << v.w << ")";
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_VECTOR4_HPP
