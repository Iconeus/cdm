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

#ifndef CDM_MATHS_DECL_RADIAN_HPP
#define CDM_MATHS_DECL_RADIAN_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>

#include <array>
#include <compare>
#include <iosfwd>

namespace cdm
{
template <typename T>
struct radian_T
{
private:
	T angle;

public:
	radian_T() = default;
	explicit constexpr radian_T(T f);
	radian_T(const radian_T& r) = default;
	radian_T(radian_T&& r) = default;
	constexpr radian_T(degree_T<T> d);

	explicit constexpr operator T() const;

	template <typename U>
	explicit constexpr operator radian_T<U>() const;

	constexpr radian_T& operator+=(radian_T r);
	constexpr radian_T& operator-=(radian_T r);
	constexpr radian_T& operator*=(radian_T r);
	constexpr radian_T& operator/=(radian_T r);

	constexpr radian_T operator-() const;

	radian_T& operator=(const radian_T& r) = default;
	constexpr radian_T& operator=(degree_T<T> d);

	std::partial_ordering operator<=>(const radian_T&) const = default;

	using underlying_type = T;
};

template <typename T>
constexpr radian_T<T> operator+(radian_T<T>, radian_T<T>);
template <typename T>
constexpr radian_T<T> operator-(radian_T<T>, radian_T<T>);
template <typename T>
constexpr radian_T<T> operator*(T, radian_T<T>);
template <typename T>
constexpr radian_T<T> operator*(radian_T<T>, T);
template <typename T>
constexpr radian_T<T> operator/(radian_T<T>, T);
template <typename T>
constexpr radian_T<T>& operator+=(radian_T<T>&, T);
template <typename T>
constexpr radian_T<T>& operator-=(radian_T<T>&, T);
template <typename T>
constexpr radian_T<T>& operator*=(radian_T<T>&, T);
template <typename T>
constexpr radian_T<T>& operator/=(radian_T<T>&, T);

template <typename T>
T sin(radian_T<T>);
template <typename T>
T cos(radian_T<T>);
template <typename T>
T tan(radian_T<T>);
template <typename T>
T asin(radian_T<T>);
template <typename T>
T acos(radian_T<T>);
template <typename T>
T atan(radian_T<T>);
template <typename T>
T sinh(radian_T<T>);
template <typename T>
T cosh(radian_T<T>);
template <typename T>
T tanh(radian_T<T>);
template <typename T>
T asinh(radian_T<T>);
template <typename T>
T acosh(radian_T<T>);
template <typename T>
T atanh(radian_T<T>);

template <typename T>
std::ostream& operator<<(std::ostream& o, const radian_T<T>& a);

using radian = radian_T<float>;
using radiand = radian_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_RADIAN_HPP
