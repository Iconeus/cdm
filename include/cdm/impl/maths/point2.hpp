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

#ifndef CDM_MATHS_IMPL_POINT2_HPP
#define CDM_MATHS_IMPL_POINT2_HPP 1

#include <cdm/decl/maths/point2.hpp>

#include <string>

namespace cdm
{
template <typename T>
constexpr point2_T<T>::point2_T(T x_, T y_) : x(x_), y(y_)
{
}

template <typename T>
constexpr point2_T<T>::point2_T(const vector2_T<T>& v) : point2_T(v.x, v.y)
{
}

template <typename T>
template <typename U>
constexpr point2_T<T>::operator point2_T<U>() const
{
	return point2_T<U>{
	    static_cast<U>(x),
	    static_cast<U>(y),
	};
}

template <typename T>
constexpr point2_T<T> point2_T<T>::from_array(const std::array<T, 2>& arr)
{
	return {
	    arr[0],
	    arr[1],
	};
}

template <typename T>
constexpr std::array<T, 2> point2_T<T>::to_array() const
{
	return {x, y};
}

template <typename T>
constexpr point2_T<T>& point2_T<T>::element_wise_clamp(const point2_T<T>& min,
                                                       const point2_T<T>& max)
{
	return cdm::element_wise_clamp(*this, min, max);
}

template <typename T>
constexpr point2_T<T> point2_T<T>::get_element_wise_clamped(
    const point2_T<T>& min,
    const point2_T<T>& max) const
{
	return cdm::get_element_wise_clamped(*this, min, max);
}

template <typename T>
constexpr point2_T<T> point2_T<T>::operator+(const point2_T<T>& v) const
{
	return {
	    x + v.x,
	    y + v.y,
	};
}

template <typename T>
constexpr point2_T<T> point2_T<T>::operator-(const point2_T<T>& v) const
{
	return {
	    x - v.x,
	    y - v.y,
	};
}

template <typename T>
constexpr point2_T<T> point2_T<T>::operator-() const
{
	return {
	    -x,
	    -y,
	};
}

template <typename T>
constexpr point2_T<T> point2_T<T>::operator*(T t) const
{
	return {
	    x * t,
	    y * t,
	};
}

template <typename T>
constexpr point2_T<T> point2_T<T>::operator/(T t) const
{
	return {
	    x / t,
	    y / t,
	};
}

template <typename T>
constexpr point2_T<T>& point2_T<T>::operator+=(const point2_T<T>& v)
{
	*this = *this + v;
	return *this;
}

template <typename T>
constexpr point2_T<T>& point2_T<T>::operator-=(const point2_T<T>& v)
{
	*this = *this - v;
	return *this;
}

template <typename T>
constexpr point2_T<T>& point2_T<T>::operator*=(T t)
{
	*this = *this * t;
	return *this;
}

template <typename T>
constexpr point2_T<T>& point2_T<T>::operator/=(T t)
{
	*this = *this / t;
	return *this;
}

template <typename T>
constexpr bool point2_T<T>::operator==(const point2_T<T>& v) const
{
	return x == v.x && y == v.y;
}

template <typename T>
constexpr bool point2_T<T>::operator!=(const point2_T<T>& v) const
{
	return !operator==(v);
}

template <typename T>
constexpr bool point2_T<T>::nearly_equal(const point2_T<T>& v, T e) const
{
	return cdm::nearly_equal(*this, v, e);
}

template <typename T>
template <typename Index>
constexpr T& point2_T<T>::operator[](Index index)
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
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
constexpr const T& point2_T<T>::operator[](Index index) const
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	}

#ifndef NDEBUG
	throw std::out_of_range("attempting to index element " +
	                        std::to_string(index));
#else
	return x;
#endif
}

template <typename T>
constexpr point2_T<T> point2_T<T>::zero()
{
	return {T(0), T(0)};
}

template <typename T>
constexpr point2_T<T> point2_T<T>::one()
{
	return {T(1), T(1)};
}

template <typename T>
constexpr point2_T<T> operator*(T f, const point2_T<T>& v)
{
	return v * f;
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_POINT2_HPP
