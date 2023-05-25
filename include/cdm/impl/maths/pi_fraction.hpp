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

#ifndef CDM_MATHS_IMPL_PI_FRACTION_HPP
#define CDM_MATHS_IMPL_PI_FRACTION_HPP 1

#include <cdm/decl/maths/pi_fraction.hpp>

#include <ostream>

namespace cdm
{
template <std::signed_integral T>
constexpr pi_fraction_T<T>::pi_fraction_T(T num, T den)
    : numerator{num}, denominator{den}
{
}

template <std::signed_integral T>
template <typename U>
inline pi_fraction_T<T>::operator radian_T<U>() const
{
	return radian_T<U>((U(numerator) * U(pi)) / U(denominator));
}

template <std::signed_integral T>
template <typename U>
inline pi_fraction_T<T>::operator degree_T<U>() const
{
	return operator radian_T<U>();
}

template <std::signed_integral T>
constexpr pi_fraction_T<T> pi_fraction_T<T>::operator-() const
{
	return pi_fraction_T{-numerator, denominator};
}

template <typename U, typename T>
inline U sin(pi_fraction_T<T> d)
{
	if constexpr (d.numerator == T(0))
		return U(0);
	else if constexpr (d == static_pi_fraction<T, T(1), T(1)>{})
		return U(0);
	else if constexpr (d == static_pi_fraction<T, T(1), T(2)>{})
		return U(1);
	else if constexpr (d == static_pi_fraction<T, T(1), T(3)>{})
		return U(sqrt3_over_2);
	else if constexpr (d == static_pi_fraction<T, T(1), T(4)>{})
		return U(inv_sqrt2);
	else if constexpr (d == static_pi_fraction<T, T(1), T(6)>{})
		return U(0.5);

	else if constexpr (d == static_pi_fraction<T, T(-1), T(1)>{})
		return U(-0);
	else if constexpr (d == static_pi_fraction<T, T(-1), T(2)>{})
		return U(-1);
	else if constexpr (d == static_pi_fraction<T, T(-1), T(3)>{})
		return U(-sqrt3_over_2);
	else if constexpr (d == static_pi_fraction<T, T(-1), T(4)>{})
		return U(-inv_sqrt2);
	else if constexpr (d == static_pi_fraction<T, T(-1), T(6)>{})
		return U(-0.5);

	else if constexpr (d == static_pi_fraction<T, T(2), T(1)>{})
		return U(0);
	else if constexpr (d == static_pi_fraction<T, T(2), T(3)>{})
		return U(sqrt3_over_2);

	else if constexpr (d == static_pi_fraction<T, T(-2), T(1)>{})
		return U(-0);
	else if constexpr (d == static_pi_fraction<T, T(-2), T(3)>{})
		return U(-sqrt3_over_2);

	else if constexpr (d == static_pi_fraction<T, T(3), T(2)>{})
		return U(-1);
	else if constexpr (d == static_pi_fraction<T, T(3), T(4)>{})
		return U(inv_sqrt2);

	else if constexpr (d == static_pi_fraction<T, T(-3), T(2)>{})
		return U(1);
	else if constexpr (d == static_pi_fraction<T, T(-3), T(4)>{})
		return U(-inv_sqrt2);

	constexpr radian_T<U> r = d;
	return sin(r);
}

template <typename U, typename T>
inline U cos(pi_fraction_T<T> d)
{
	if constexpr (d.numerator == T(0))
		return U(1);
	else if constexpr (d.numerator == T(1) || d.numerator == T(-1))
	{
		if constexpr (d.denominator == T(1))
			return U(-1);
		else if constexpr (d.denominator == T(2))
			return U(0);
		else if constexpr (d.denominator == T(3))
			return U(0.5);
		else if constexpr (d.denominator == T(4))
			return U(inv_sqrt2);
		else if constexpr (d.denominator == T(6))
			return U(sqrt3_over_2);
	}
	else if constexpr (d.numerator == T(2) || d.numerator == T(-2))
	{
		if constexpr (d.denominator == T(1))
			return U(1);
		else if constexpr (d.denominator == T(3))
			return U(-0.5);
	}
	else if constexpr (d.numerator == T(3) || d.numerator == T(-3))
	{
		if constexpr (d.denominator == T(2))
			return U(0);
		else if constexpr (d.denominator == T(4))
			return U(-inv_sqrt2);
	}

	constexpr radian_T<U> r = d;
	return cos(r);
}

template <typename U, typename T>
inline U tan(pi_fraction_T<T> d)
{
	if constexpr (d.numerator == T(0))
		return U(0);
	else if constexpr (d.numerator == T(1))
	{
		if constexpr (d.denominator == T(1))
			return U(0);
		else if constexpr (d.denominator == T(2))
			return -std::numeric_limits<U>::infinity();
		else if constexpr (d.denominator == T(3))
			return U(sqrt3);
		else if constexpr (d.denominator == T(4))
			return U(1);
		else if constexpr (d.denominator == T(6))
			return U(inv_sqrt3);
	}
	else if constexpr (d.numerator == T(-1))
	{
		if constexpr (d.denominator == T(1))
			return U(-0);
		else if constexpr (d.denominator == T(2))
			return std::numeric_limits<U>::infinity();
		else if constexpr (d.denominator == T(3))
			return U(-sqrt3);
		else if constexpr (d.denominator == T(4))
			return U(-1);
		else if constexpr (d.denominator == T(6))
			return U(-inv_sqrt3);
	}
	else if constexpr (d.numerator == T(2))
	{
		if constexpr (d.denominator == T(1))
			return U(0);
		else if constexpr (d.denominator == T(3))
			return U(-sqrt3);
	}
	else if constexpr (d.numerator == T(-2))
	{
		if constexpr (d.denominator == T(1))
			return U(0);
		else if constexpr (d.denominator == T(3))
			return U(sqrt3);
	}
	else if constexpr (d.numerator == T(3))
	{
		if constexpr (d.denominator == T(2))
			return -std::numeric_limits<U>::infinity();
		else if constexpr (d.denominator == T(4))
			return U(-1);
	}
	else if constexpr (d.numerator == T(-3))
	{
		if constexpr (d.denominator == T(2))
			return std::numeric_limits<U>::infinity();
		else if constexpr (d.denominator == T(4))
			return U(1);
	}

	constexpr radian_T<U> r = d;
	return tan(r);
}

template <typename U, typename T>
inline U asin(pi_fraction_T<T> d)
{
	/// TODO: implement
	constexpr radian_T<U> r = d;
	return asin(r);
}

template <typename U, typename T>
inline U acos(pi_fraction_T<T> d)
{
	/// TODO: implement
	return acos(radian_T<U>(d));
}

template <typename U, typename T>
inline U atan(pi_fraction_T<T> d)
{
	/// TODO: implement
	return atan(radian_T<U>(d));
}

template <typename U, typename T>
inline U sinh(pi_fraction_T<T> d)
{
	/// TODO: implement
	constexpr radian_T<U> r = d;
	return sinh(r);
}

template <typename U, typename T>
inline U cosh(pi_fraction_T<T> d)
{
	/// TODO: implement
	constexpr radian_T<U> r = d;
	return cosh(r);
}

template <typename U, typename T>
inline U tanh(pi_fraction_T<T> d)
{
	/// TODO: implement
	constexpr radian_T<U> r = d;
	return tanh(r);
}

template <typename U, typename T>
inline U asinh(pi_fraction_T<T> d)
{
	/// TODO: implement
	constexpr radian_T<U> r = d;
	return asinh(r);
}

template <typename U, typename T>
inline U acosh(pi_fraction_T<T> d)
{
	/// TODO: implement
	constexpr radian_T<U> r = d;
	return acosh(r);
}

template <typename U, typename T>
inline U atanh(pi_fraction_T<T> d)
{
	/// TODO: implement
	constexpr radian_T<U> r = d;
	return atanh(r);
}

template <typename T>
inline std::ostream& operator<<(std::ostream& o, const pi_fraction_T<T>& f)
{
	return o << "pi_fraction_T(" << f.numerator << "pi / " << f.denominator
	         << ")";
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_PI_FRACTION_HPP
