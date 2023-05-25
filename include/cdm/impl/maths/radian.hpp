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

#ifndef CDM_MATHS_IMPL_RADIAN_HPP
#define CDM_MATHS_IMPL_RADIAN_HPP 1

#include <cdm/decl/maths/degree.hpp>
#include <cdm/decl/maths/radian.hpp>

#include <ostream>

namespace cdm
{
template <typename T>
constexpr radian_T<T>::radian_T(T f) : angle(f)
{
}
template <typename T>
constexpr radian_T<T>::radian_T(degree_T<T> d)
    : angle(static_cast<T>(d) * T(deg_To_rad))
{
}

template <typename T>
constexpr radian_T<T>::operator T() const
{
	return angle;
}

template <typename T>
template <typename U>
constexpr radian_T<T>::operator radian_T<U>() const
{
	return radian_T<U>{U(angle)};
}

template <typename T>
constexpr radian_T<T>& radian_T<T>::operator+=(radian_T<T> r)
{
	angle += r.angle;
	return *this;
}

template <typename T>
constexpr radian_T<T>& radian_T<T>::operator-=(radian_T<T> r)
{
	angle -= r.angle;
	return *this;
}

template <typename T>
constexpr radian_T<T>& radian_T<T>::operator*=(radian_T<T> r)
{
	angle *= r.angle;
	return *this;
}

template <typename T>
constexpr radian_T<T>& radian_T<T>::operator/=(radian_T<T> r)
{
	angle /= r.angle;
	return *this;
}

template <typename T>
constexpr radian_T<T> radian_T<T>::operator-() const
{
	return radian_T<T>{-angle};
}

template <typename T>
constexpr radian_T<T>& radian_T<T>::operator=(degree_T<T> d)
{
	angle = d.angle * T(deg_To_rad);
	return *this;
}

template <typename T>
constexpr radian_T<T> operator+(radian_T<T> r1, radian_T<T> r2)
{
	return radian_T<T>{static_cast<T>(r1) + static_cast<T>(r2)};
}

template <typename T>
constexpr radian_T<T> operator-(radian_T<T> r1, radian_T<T> r2)
{
	return radian_T<T>{static_cast<T>(r1) - static_cast<T>(r2)};
}

template <typename T>
constexpr radian_T<T> operator*(T f, radian_T<T> r)
{
	return radian_T<T>{static_cast<T>(r) * f};
}

template <typename T>
constexpr radian_T<T> operator*(radian_T<T> r, T f)
{
	return radian_T<T>{f * static_cast<T>(r)};
}

template <typename T>
constexpr radian_T<T> operator/(radian_T<T> r, T f)
{
	return radian_T<T>{static_cast<T>(r) / f};
}

template <typename T>
constexpr radian_T<T>& operator+=(radian_T<T>& r, T f)
{
	r = r + f;
	return r;
}

template <typename T>
constexpr radian_T<T>& operator-=(radian_T<T>& r, T f)
{
	r = r - f;
	return r;
}

template <typename T>
constexpr radian_T<T>& operator*=(radian_T<T>& r, T f)
{
	r = r * f;
	return r;
}

template <typename T>
constexpr radian_T<T>& operator/=(radian_T<T>& r, T f)
{
	r = r / f;
	return r;
}

template <typename T>
inline T sin(radian_T<T> r)
{
	return std::sin(static_cast<T>(r));
}

template <typename T>
inline T cos(radian_T<T> r)
{
	return std::cos(static_cast<T>(r));
}

template <typename T>
inline T tan(radian_T<T> r)
{
	return std::tan(static_cast<T>(r));
}

template <typename T>
inline T asin(radian_T<T> r)
{
	return std::asin(static_cast<T>(r));
}

template <typename T>
inline T acos(radian_T<T> r)
{
	return std::acos(static_cast<T>(r));
}

template <typename T>
inline T atan(radian_T<T> r)
{
	return std::atan(static_cast<T>(r));
}

template <typename T>
inline T sinh(radian_T<T> r)
{
	return std::sinh(static_cast<T>(r));
}

template <typename T>
inline T cosh(radian_T<T> r)
{
	return std::cosh(static_cast<T>(r));
}

template <typename T>
inline T tanh(radian_T<T> r)
{
	return std::tanh(static_cast<T>(r));
}

template <typename T>
inline T asinh(radian_T<T> r)
{
	return std::asinh(static_cast<T>(r));
}

template <typename T>
inline T acosh(radian_T<T> r)
{
	return std::acosh(static_cast<T>(r));
}

template <typename T>
inline T atanh(radian_T<T> r)
{
	return std::atanh(static_cast<T>(r));
}

template <typename T>
inline std::ostream& operator<<(std::ostream& o, const radian_T<T>& a)
{
	return o << "radian_T(" << static_cast<T>(a) << ")";
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_RADIAN_HPP
