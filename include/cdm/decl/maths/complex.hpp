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

#ifndef CDM_MATHS_DECL_COMPLEX_HPP
#define CDM_MATHS_DECL_COMPLEX_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>

namespace cdm
{
template <typename T>
struct complex_T
{
	T r;
	T i;

	complex_T() = default;
	constexpr complex_T(T r_, T i_);
	explicit constexpr complex_T(radian_T<T> angle);
	complex_T(const complex_T&) = default;
	complex_T(complex_T&&) = default;
	complex_T& operator=(const complex_T&) = default;
	complex_T& operator=(complex_T&&) = default;

	radian_T<T> angle() const;

	T norm() const;
	constexpr T norm_squared() const;

	complex_T& normalize();
	complex_T get_normalized() const;

	constexpr complex_T& conjugate();
	constexpr complex_T get_conjugated() const;

	constexpr complex_T operator+(complex_T c) const;
	constexpr complex_T operator-(complex_T c) const;

	constexpr complex_T& operator+=(complex_T c);
	constexpr complex_T& operator-=(complex_T c);
	constexpr complex_T& operator*=(complex_T c);

	static constexpr complex_T identity();

	using underlying_type = T;
};

template <typename T>
constexpr complex_T<T> operator*(complex_T<T> c1, complex_T<T> c2);
template <typename T>
constexpr complex_T<T> operator*(complex_T<T> c, T f);
template <typename T>
constexpr complex_T<T> operator*(normalized<complex_T<T>> c1, complex_T<T> c2);
template <typename T>
constexpr complex_T<T> operator*(complex_T<T> c1, normalized<complex_T<T>> c2);
template <typename T>
constexpr normalized<complex_T<T>> operator*(normalized<complex_T<T>> c1,
                                             normalized<complex_T<T>> c2);
template <typename T>
constexpr vector2_T<T> operator*(complex_T<T> c, vector2_T<T> v);
template <typename T>
constexpr vector2_T<T> operator*(normalized<complex_T<T>> c, vector2_T<T> v);

template <typename T>
T norm(complex_T<T> c);
template <typename T>
constexpr T norm_squared(complex_T<T> c);
template <typename T>
complex_T<T> normalize(complex_T<T> c);
template <typename T>
constexpr complex_T<T> conjugate(complex_T<T> c);
template <typename T>
radian_T<T> angle_between(complex_T<T> c1, complex_T<T> c2);

using complex = complex_T<float>;
using complexd = complex_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_COMPLEX_HPP
