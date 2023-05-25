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

#ifndef CDM_MATHS_IMPL_STATIC_PI_FRACTION_HPP
#define CDM_MATHS_IMPL_STATIC_PI_FRACTION_HPP 1

#include <cdm/decl/maths/static_pi_fraction.hpp>

#include <ostream>

namespace cdm
{
namespace detail
{
template <std::signed_integral T, T NumeratorT, T DenominatorT>
inline consteval std::pair<T, T> resign()
{
	static_assert(DenominatorT != T(0));

	if constexpr (DenominatorT < T(0))
		return {-NumeratorT, -DenominatorT};
	else
		return {NumeratorT, DenominatorT};
}

template <std::signed_integral T, T NumeratorT, T DenominatorT>
inline consteval std::pair<T, T> simplify()
{
	constexpr auto fraction = resign<T, NumeratorT, DenominatorT>();
	constexpr auto numt = fraction.first;
	constexpr auto dent = fraction.second;

	if constexpr (numt % dent == T(0))
		return {numt / dent, T(1)};
	else if constexpr (dent % numt == T(0))
	{
		if constexpr (numt > T(0))
			return {T(1), dent / numt};
		else
			return {T(-1), -dent / numt};
	}
	else
		return {numt, dent};
}

template <std::signed_integral T, T NumeratorT, T DenominatorT>
inline consteval std::pair<T, T> wrap()
{
	constexpr auto fraction = simplify<T, NumeratorT, DenominatorT>();
	constexpr auto numt = fraction.first;
	constexpr auto dent = fraction.second;

	static_assert(dent != T(0));

	if constexpr (dent == T(1))
		return {numt % T(2), dent};
	else if constexpr (dent == T(2))
		return {numt % T(4), dent};
	else
		return {numt, dent};
}
}  // namespace detail

template <std::signed_integral T, T NumeratorT, T DenominatorT>
template <typename U>
constexpr static_pi_fraction_T<T, NumeratorT, DenominatorT>::operator radian_T<
    U>() const
{
	if constexpr (numerator == T(0))
		return radian_T<U>(U(0));
	else
		return radian_T<U>((U(numerator) * U(pi)) / U(denominator));
}

template <std::signed_integral T, T NumeratorT, T DenominatorT>
template <typename U>
constexpr static_pi_fraction_T<T, NumeratorT, DenominatorT>::operator degree_T<
    U>() const
{
	if constexpr (numerator == T(0))
		return degree_T<U>(U(0));
	else
		return degree_T<U>(
		    radian_T<U>((U(numerator) * U(pi)) / U(denominator)));
}

template <std::signed_integral T, T NumeratorT, T DenominatorT>
constexpr static_pi_fraction_T<T, NumeratorT, DenominatorT>::
operator pi_fraction_T<T>() const
{
	return {numerator, denominator};
}

template <std::signed_integral T,
          T NumeratorTL,
          T DenominatorTL,
          T NumeratorTR,
          T DenominatorTR>
constexpr bool operator==(
    const static_pi_fraction_T<T, NumeratorTL, DenominatorTL>& lhs,
    const static_pi_fraction_T<T, NumeratorTR, DenominatorTR>& rhs)
{
	return lhs.numerator == rhs.numerator &&
	       lhs.denominator == rhs.denominator;
}

template <std::signed_integral T,
          T NumeratorTL,
          T DenominatorTL,
          T NumeratorTR,
          T DenominatorTR>
constexpr bool operator!=(
    const static_pi_fraction_T<T, NumeratorTL, DenominatorTL>& lhs,
    const static_pi_fraction_T<T, NumeratorTR, DenominatorTR>& rhs)
{
	return !(lhs == rhs);
}

template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
inline U sin(static_pi_fraction_T<T, NumeratorT, DenominatorT> d)
{
	if constexpr (d.numerator == T(0))
		return U(0);
	else if constexpr (d == static_pi_fraction_T<T, T(1), T(1)>{})
		return U(0);
	else if constexpr (d == static_pi_fraction_T<T, T(1), T(2)>{})
		return U(1);
	else if constexpr (d == static_pi_fraction_T<T, T(1), T(3)>{})
		return U(sqrt3_over_2);
	else if constexpr (d == static_pi_fraction_T<T, T(1), T(4)>{})
		return U(inv_sqrt2);
	else if constexpr (d == static_pi_fraction_T<T, T(1), T(6)>{})
		return U(0.5);

	else if constexpr (d == static_pi_fraction_T<T, T(-1), T(1)>{})
		return U(-0);
	else if constexpr (d == static_pi_fraction_T<T, T(-1), T(2)>{})
		return U(-1);
	else if constexpr (d == static_pi_fraction_T<T, T(-1), T(3)>{})
		return U(-sqrt3_over_2);
	else if constexpr (d == static_pi_fraction_T<T, T(-1), T(4)>{})
		return U(-inv_sqrt2);
	else if constexpr (d == static_pi_fraction_T<T, T(-1), T(6)>{})
		return U(-0.5);

	else if constexpr (d == static_pi_fraction_T<T, T(2), T(1)>{})
		return U(0);
	else if constexpr (d == static_pi_fraction_T<T, T(2), T(3)>{})
		return U(sqrt3_over_2);

	else if constexpr (d == static_pi_fraction_T<T, T(-2), T(1)>{})
		return U(-0);
	else if constexpr (d == static_pi_fraction_T<T, T(-2), T(3)>{})
		return U(-sqrt3_over_2);

	else if constexpr (d == static_pi_fraction_T<T, T(3), T(2)>{})
		return U(-1);
	else if constexpr (d == static_pi_fraction_T<T, T(3), T(4)>{})
		return U(inv_sqrt2);

	else if constexpr (d == static_pi_fraction_T<T, T(-3), T(2)>{})
		return U(1);
	else if constexpr (d == static_pi_fraction_T<T, T(-3), T(4)>{})
		return U(-inv_sqrt2);

	constexpr radian_T<U> r = d;
	return sin(r);
}

template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
inline U cos(static_pi_fraction_T<T, NumeratorT, DenominatorT> d)
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

template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
inline U tan(static_pi_fraction_T<T, NumeratorT, DenominatorT> d)
{
	if constexpr (d.numerator == T(0))
		return U(0);
	else if constexpr (d.numerator == T(1))
	{
		if constexpr (d.denominator == T(1))
			return U(0);
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
		if constexpr (d.denominator == T(4))
			return U(-1);
	}
	else if constexpr (d.numerator == T(-3))
	{
		if constexpr (d.denominator == T(4))
			return U(1);
	}

	constexpr radian_T<U> r = d;
	return tan(r);
}

template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
inline U asin(static_pi_fraction_T<T, NumeratorT, DenominatorT> d)
{
	/// TODO: implement
	constexpr radian_T<U> r = d;
	return asin(r);
}

template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
inline U acos(static_pi_fraction_T<T, NumeratorT, DenominatorT> d)
{
	/// TODO: implement
	return acos(radian_T<U>(d));
}

template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
inline U atan(static_pi_fraction_T<T, NumeratorT, DenominatorT> d)
{
	/// TODO: implement
	return atan(radian_T<U>(d));
}

template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
inline U sinh(static_pi_fraction_T<T, NumeratorT, DenominatorT> d)
{
	/// TODO: implement
	constexpr radian_T<U> r = d;
	return sinh(r);
}

template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
inline U cosh(static_pi_fraction_T<T, NumeratorT, DenominatorT> d)
{
	/// TODO: implement
	constexpr radian_T<U> r = d;
	return cosh(r);
}

template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
inline U tanh(static_pi_fraction_T<T, NumeratorT, DenominatorT> d)
{
	/// TODO: implement
	constexpr radian_T<U> r = d;
	return tanh(r);
}

template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
inline U asinh(static_pi_fraction_T<T, NumeratorT, DenominatorT> d)
{
	/// TODO: implement
	constexpr radian_T<U> r = d;
	return asinh(r);
}

template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
inline U acosh(static_pi_fraction_T<T, NumeratorT, DenominatorT> d)
{
	/// TODO: implement
	constexpr radian_T<U> r = d;
	return acosh(r);
}

template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
inline U atanh(static_pi_fraction_T<T, NumeratorT, DenominatorT> d)
{
	/// TODO: implement
	constexpr radian_T<U> r = d;
	return atanh(r);
}

template <typename T, T NumT, T DenT>
inline std::ostream& operator<<(std::ostream& o,
                                const static_pi_fraction_T<T, NumT, DenT>& f)
{
	return o << "static_pi_fraction_T(" << f.numerator << "*pi / "
	         << f.denominator << ")";
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_STATIC_PI_FRACTION_HPP
