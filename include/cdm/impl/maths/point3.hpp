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

#ifndef CDM_MATHS_IMPL_POINT3_HPP
#define CDM_MATHS_IMPL_POINT3_HPP 1

#include <cdm/decl/maths/point3.hpp>

#include <string>

namespace cdm
{
template <typename T>
constexpr point3_T<T>::point3_T(T x_, T y_, T z_) : x(x_), y(y_), z(z_)
{
}

template <typename T>
constexpr point3_T<T>::point3_T(const vector3_T<T>& v)
    : point3_T(v.x, v.y, v.z)
{
}

template <typename T>
template <typename U>
constexpr point3_T<T>::operator point3_T<U>() const
{
	return point3_T<U>{
	    static_cast<U>(x),
	    static_cast<U>(y),
	    static_cast<U>(z),
	};
}

template <typename T>
constexpr point3_T<T> point3_T<T>::from_array(const std::array<T, 3>& arr)
{
	return {
	    arr[0],
	    arr[1],
	    arr[2],
	};
}

template <typename T>
constexpr std::array<T, 3> point3_T<T>::to_array() const
{
	return {x, y, z};
}

template <typename T>
constexpr point3_T<T>& point3_T<T>::element_wise_clamp(const point3_T<T>& min,
                                                       const point3_T<T>& max)
{
	return cdm::element_wise_clamp(*this, min, max);
}

template <typename T>
constexpr point3_T<T> point3_T<T>::get_element_wise_clamped(
    const point3_T<T>& min,
    const point3_T<T>& max) const
{
	return cdm::get_element_wise_clamped(*this, min, max);
}

template <typename T>
constexpr point3_T<T> point3_T<T>::operator+(const point3_T<T>& v) const
{
	return {
	    x + v.x,
	    y + v.y,
	    z + v.z,
	};
}

template <typename T>
constexpr point3_T<T> point3_T<T>::operator-(const point3_T<T>& v) const
{
	return {
	    x - v.x,
	    y - v.y,
	    z - v.z,
	};
}

template <typename T>
constexpr point3_T<T> point3_T<T>::operator-() const
{
	return {
	    -x,
	    -y,
	    -z,
	};
}

template <typename T>
constexpr point3_T<T> point3_T<T>::operator*(T t) const
{
	return {
	    x * t,
	    y * t,
	    z * t,
	};
}

template <typename T>
constexpr point3_T<T> point3_T<T>::operator/(T t) const
{
	return {
	    x / t,
	    y / t,
	    z / t,
	};
}

template <typename T>
constexpr point3_T<T>& point3_T<T>::operator+=(const point3_T<T>& v)
{
	*this = *this + v;
	return *this;
}

template <typename T>
constexpr point3_T<T>& point3_T<T>::operator-=(const point3_T<T>& v)
{
	*this = *this - v;
	return *this;
}

template <typename T>
constexpr point3_T<T>& point3_T<T>::operator*=(T t)
{
	*this = *this * t;
	return *this;
}

template <typename T>
constexpr point3_T<T>& point3_T<T>::operator/=(T t)
{
	*this = *this / t;
	return *this;
}

template <typename T>
constexpr bool point3_T<T>::operator==(const point3_T<T>& v) const
{
	return x == v.x && y == v.y && z == v.z;
}

template <typename T>
constexpr bool point3_T<T>::operator!=(const point3_T<T>& v) const
{
	return !operator==(v);
}

template <typename T>
constexpr bool point3_T<T>::nearly_equal(const point3_T<T>& v, T e) const
{
	return cdm::nearly_equal(*this, v, e);
}

template <typename T>
template <typename Index>
constexpr T& point3_T<T>::operator[](Index index)
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	}

#ifndef NDEBUG
	throw std::out_of_range("attempting to index element " +
	                        std::to_string(index));
#else
	return x;
#endif
}

template <typename T>
template <typename Index>
constexpr const T& point3_T<T>::operator[](Index index) const
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	}

#ifndef NDEBUG
	throw std::out_of_range("attempting to index element " +
	                        std::to_string(index));
#else
	return x;
#endif
}

template <typename T>
constexpr point3_T<T> point3_T<T>::zero()
{
	return {T(0), T(0), T(0)};
}

template <typename T>
constexpr point3_T<T> point3_T<T>::one()
{
	return {T(1), T(1), T(1)};
}

template <typename T>
constexpr point3_T<T> operator*(T f, const point3_T<T>& v)
{
	return v * f;
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_POINT3_HPP
