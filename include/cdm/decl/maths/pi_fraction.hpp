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

#ifndef CDM_MATHS_DECL_PI_FRACTION_HPP
#define CDM_MATHS_DECL_PI_FRACTION_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>

#include <iosfwd>

namespace cdm
{
template <std::signed_integral T>
struct pi_fraction_T
{
	T numerator;
	T denominator;

	pi_fraction_T() = default;
	constexpr pi_fraction_T(T num, T den);
	pi_fraction_T(const pi_fraction_T& d) = default;
	pi_fraction_T(pi_fraction_T&& d) = default;

	pi_fraction_T& operator=(const pi_fraction_T&) = default;
	pi_fraction_T& operator=(pi_fraction_T&&) = default;

	template <typename U>
	operator radian_T<U>() const;
	template <typename U>
	operator degree_T<U>() const;

	constexpr pi_fraction_T operator-() const;

	using underlying_type = T;
};

template <typename U, typename T>
U sin(pi_fraction_T<T> d);
template <typename U, typename T>
U cos(pi_fraction_T<T> d);
template <typename U, typename T>
U tan(pi_fraction_T<T> d);
template <typename U, typename T>
U asin(pi_fraction_T<T> d);
template <typename U, typename T>
U acos(pi_fraction_T<T> d);
template <typename U, typename T>
U atan(pi_fraction_T<T> d);
template <typename U, typename T>
U sinh(pi_fraction_T<T> d);
template <typename U, typename T>
U cosh(pi_fraction_T<T> d);
template <typename U, typename T>
U tanh(pi_fraction_T<T> d);
template <typename U, typename T>
U asinh(pi_fraction_T<T> d);
template <typename U, typename T>
U acosh(pi_fraction_T<T> d);
template <typename U, typename T>
U atanh(pi_fraction_T<T> d);

template <typename T>
std::ostream& operator<<(std::ostream& o, const pi_fraction_T<T>& f);
}  // namespace cdm

#endif  // CDM_MATHS_DECL_PI_FRACTION_HPP
