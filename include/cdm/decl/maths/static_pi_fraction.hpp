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

#ifndef CDM_MATHS_DECL_STATIC_PI_FRACTION_HPP
#define CDM_MATHS_DECL_STATIC_PI_FRACTION_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>

#include <iosfwd>

namespace cdm
{
namespace detail
{
template <std::signed_integral T, T NumeratorT, T DenominatorT>
consteval std::pair<T, T> wrap();
}  // namespace detail

template <std::signed_integral T, T NumeratorT, T DenominatorT>
struct static_pi_fraction_T
{
	static_assert(DenominatorT != T(0), "the denominator can not be 0");

	static constexpr T numerator{
	    detail::wrap<T, NumeratorT, DenominatorT>().first};
	static constexpr T denominator{
	    detail::wrap<T, NumeratorT, DenominatorT>().second};

	template <typename U>
	constexpr operator radian_T<U>() const;
	template <typename U>
	constexpr operator degree_T<U>() const;
	constexpr operator pi_fraction_T<T>() const;

	constexpr static_pi_fraction_T<T, -numerator, denominator> operator-()
	    const;

	using underlying_type = T;
};

template <std::signed_integral T,
          T NumeratorTL,
          T DenominatorTL,
          T NumeratorTR,
          T DenominatorTR>
constexpr bool operator==(
    const static_pi_fraction_T<T, NumeratorTL, DenominatorTL>& lhs,
    const static_pi_fraction_T<T, NumeratorTR, DenominatorTR>& rhs);
template <std::signed_integral T,
          T NumeratorTL,
          T DenominatorTL,
          T NumeratorTR,
          T DenominatorTR>
constexpr bool operator!=(
    const static_pi_fraction_T<T, NumeratorTL, DenominatorTL>& lhs,
    const static_pi_fraction_T<T, NumeratorTR, DenominatorTR>& rhs);

template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
U sin(static_pi_fraction_T<T, NumeratorT, DenominatorT> d);
template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
U cos(static_pi_fraction_T<T, NumeratorT, DenominatorT> d);
template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
U tan(static_pi_fraction_T<T, NumeratorT, DenominatorT> d);
template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
U asin(static_pi_fraction_T<T, NumeratorT, DenominatorT> d);
template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
U acos(static_pi_fraction_T<T, NumeratorT, DenominatorT> d);
template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
U atan(static_pi_fraction_T<T, NumeratorT, DenominatorT> d);
template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
U sinh(static_pi_fraction_T<T, NumeratorT, DenominatorT> d);
template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
U cosh(static_pi_fraction_T<T, NumeratorT, DenominatorT> d);
template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
U tanh(static_pi_fraction_T<T, NumeratorT, DenominatorT> d);
template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
U asinh(static_pi_fraction_T<T, NumeratorT, DenominatorT> d);
template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
U acosh(static_pi_fraction_T<T, NumeratorT, DenominatorT> d);
template <typename U, std::signed_integral T, T NumeratorT, T DenominatorT>
U atanh(static_pi_fraction_T<T, NumeratorT, DenominatorT> d);

template <typename T, T NumT, T DenT>
std::ostream& operator<<(std::ostream& o,
                         const static_pi_fraction_T<T, NumT, DenT>& f);

template <std::int_fast32_t NumT, std::int_fast32_t DenT>
using static_pi_fraction = static_pi_fraction_T<::int_fast32_t, NumT, DenT>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_STATIC_PI_FRACTION_HPP
