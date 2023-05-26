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

#ifndef CDM_MATHS_IMPL_DEGREE_HPP
#define CDM_MATHS_IMPL_DEGREE_HPP 1

#include <cdm/decl/maths/degree.hpp>
#include <cdm/decl/maths/radian.hpp>

#include <ostream>

namespace cdm
{
template <typename T>
constexpr degree_T<T>::degree_T(T f) : angle(f)
{
}

template <typename T>
constexpr degree_T<T>::degree_T(radian_T<T> r)
    : angle(static_cast<T>(r) * T(rad_to_deg))
{
}

template <typename T>
template <typename U>
constexpr degree_T<T>::operator degree_T<U>() const
{
	return degree_T<U>{U(angle)};
}

template <typename T>
constexpr degree_T<T>::operator T() const
{
	return angle;
}

template <typename T>
constexpr degree_T<T>& degree_T<T>::operator+=(degree_T d)
{
	angle += d.angle;
	return *this;
}

template <typename T>
constexpr degree_T<T>& degree_T<T>::operator-=(degree_T d)
{
	angle -= d.angle;
	return *this;
}

template <typename T>
constexpr degree_T<T>& degree_T<T>::operator*=(degree_T d)
{
	angle *= d.angle;
	return *this;
}

template <typename T>
constexpr degree_T<T>& degree_T<T>::operator/=(degree_T d)
{
	angle /= d.angle;
	return *this;
}

template <typename T>
constexpr degree_T<T> degree_T<T>::operator-() const
{
	return degree_T(-angle);
}

template <typename T>
constexpr degree_T<T>& degree_T<T>::operator=(radian_T<T> r)
{
	degree_T<T> d(r);
	*this = d;
	return *this;
}

template <typename T>
constexpr degree_T<T> operator+(degree_T<T> d1, degree_T<T> d2)
{
	return degree_T<T>{static_cast<T>(d1) + static_cast<T>(d2)};
}

template <typename T>
constexpr degree_T<T> operator-(degree_T<T> d1, degree_T<T> d2)
{
	return degree_T<T>{static_cast<T>(d1) - static_cast<T>(d2)};
}

template <typename T>
constexpr degree_T<T> operator*(T f, degree_T<T> d)
{
	return degree_T<T>{static_cast<T>(d) * f};
}

template <typename T>
constexpr degree_T<T> operator*(degree_T<T> d, T f)
{
	return degree_T<T>{f * static_cast<T>(d)};
}

template <typename T>
constexpr degree_T<T> operator/(degree_T<T> d, T f)
{
	return degree_T<T>{static_cast<T>(d) / f};
}

template <typename T>
constexpr degree_T<T>& operator+=(degree_T<T>& d, T f)
{
	d = d + f;
	return d;
}

template <typename T>
constexpr degree_T<T>& operator-=(degree_T<T>& d, T f)
{
	d = d - f;
	return d;
}

template <typename T>
constexpr degree_T<T>& operator*=(degree_T<T>& d, T f)
{
	d = d * f;
	return d;
}

template <typename T>
constexpr degree_T<T>& operator/=(degree_T<T>& d, T f)
{
	d = d / f;
	return d;
}

template <typename T>
inline T sin(degree_T<T> d)
{
	return sin(radian_T<T>(d));
}

template <typename T>
inline T cos(degree_T<T> d)
{
	return cos(radian_T<T>(d));
}

template <typename T>
inline T tan(degree_T<T> d)
{
	return tan(radian_T<T>(d));
}

template <typename T>
inline T asin(degree_T<T> d)
{
	return asin(radian_T<T>(d));
}

template <typename T>
inline T acos(degree_T<T> d)
{
	return acos(radian_T<T>(d));
}

template <typename T>
inline T atan(degree_T<T> d)
{
	return atan(radian_T<T>(d));
}

template <typename T>
inline T sinh(degree_T<T> d)
{
	return sinh(radian_T<T>(d));
}

template <typename T>
inline T cosh(degree_T<T> d)
{
	return cosh(radian_T<T>(d));
}

template <typename T>
inline T tanh(degree_T<T> d)
{
	return tanh(radian_T<T>(d));
}

template <typename T>
inline T asinh(degree_T<T> d)
{
	return asinh(radian_T<T>(d));
}

template <typename T>
inline T acosh(degree_T<T> d)
{
	return acosh(radian_T<T>(d));
}

template <typename T>
inline T atanh(degree_T<T> d)
{
	return atanh(radian_T<T>(d));
}

template <typename T>
inline std::ostream& operator<<(std::ostream& o, const degree_T<T>& a)
{
	return o << "degree_T(" << static_cast<T>(a) << ")";
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_DEGREE_HPP
