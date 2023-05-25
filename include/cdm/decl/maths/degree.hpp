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

#ifndef CDM_MATHS_DECL_DEGREE_HPP
#define CDM_MATHS_DECL_DEGREE_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>

#include <array>
#include <iosfwd>

namespace cdm
{
template <typename T>
struct degree_T
{
private:
	T angle;

public:
	degree_T() = default;
	explicit constexpr degree_T(T f);
	degree_T(const degree_T& d) = default;
	degree_T(degree_T&& d) = default;
	constexpr degree_T(radian_T<T> r);

	explicit constexpr operator T() const;

	template <typename U>
	explicit constexpr operator degree_T<U>() const;

	constexpr degree_T& operator+=(degree_T d);
	constexpr degree_T& operator-=(degree_T d);
	constexpr degree_T& operator*=(degree_T d);
	constexpr degree_T& operator/=(degree_T d);

	constexpr degree_T operator-() const;

	degree_T& operator=(const degree_T& d) = default;
	constexpr degree_T& operator=(radian_T<T> r);

	std::partial_ordering operator<=>(const degree_T&) const = default;

	using underlying_type = T;
};

template <typename T>
constexpr degree_T<T> operator+(degree_T<T>, degree_T<T>);
template <typename T>
constexpr degree_T<T> operator-(degree_T<T>, degree_T<T>);
template <typename T>
constexpr degree_T<T> operator*(T, degree_T<T>);
template <typename T>
constexpr degree_T<T> operator*(degree_T<T>, T);
template <typename T>
constexpr degree_T<T> operator/(degree_T<T>, T);
template <typename T>
constexpr degree_T<T>& operator+=(degree_T<T>&, T);
template <typename T>
constexpr degree_T<T>& operator-=(degree_T<T>&, T);
template <typename T>
constexpr degree_T<T>& operator*=(degree_T<T>&, T);
template <typename T>
constexpr degree_T<T>& operator/=(degree_T<T>&, T);

template <typename T>
T sin(degree_T<T>);
template <typename T>
T cos(degree_T<T>);
template <typename T>
T tan(degree_T<T>);
template <typename T>
T asin(degree_T<T>);
template <typename T>
T acos(degree_T<T>);
template <typename T>
T atan(degree_T<T>);
template <typename T>
T sinh(degree_T<T>);
template <typename T>
T cosh(degree_T<T>);
template <typename T>
T tanh(degree_T<T>);
template <typename T>
T asinh(degree_T<T>);
template <typename T>
T acosh(degree_T<T>);
template <typename T>
T atanh(degree_T<T>);

template <typename T>
std::ostream& operator<<(std::ostream& o, const degree_T<T>& a);

using degree = degree_T<float>;
using degreed = degree_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_DEGREE_HPP
