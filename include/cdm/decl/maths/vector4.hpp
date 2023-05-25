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

#ifndef CDM_MATHS_DECL_VECTOR4_HPP
#define CDM_MATHS_DECL_VECTOR4_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>
#include <cdm/decl/maths/misc.hpp>

#include <array>
#include <iosfwd>

namespace cdm
{
template <typename T>
struct vector4_T
{
	T x, y, z, w;

	vector4_T() = default;
	constexpr vector4_T(T x_, T y_, T z_, T w_);
	constexpr vector4_T(vector2_T<T> v, T z_, T w_);
	constexpr vector4_T(vector3_T<T> v, T w_);
	constexpr vector4_T(std::array<T, 4> a);

	template <typename U>
	explicit constexpr operator vector4_T<U>() const;

	constexpr operator std::array<T, 4>() const;

	template <typename U = T>
	constexpr std::array<U, 4> to_array() const;

	constexpr vector2_T<T> xy() const;
	constexpr vector3_T<T> xyz() const;

	T norm() const;
	constexpr T norm_squared() const;
	vector4_T& normalize();
	vector4_T get_normalized() const;
	constexpr vector4_T& clamp(vector4_T min, vector4_T max);
	constexpr vector4_T get_clamped(vector4_T min, vector4_T max) const;

	constexpr vector4_T operator+(vector4_T v) const;
	constexpr vector4_T operator-(vector4_T v) const;

	constexpr vector4_T& operator+=(vector4_T v);
	constexpr vector4_T& operator-=(vector4_T v);

	constexpr vector4_T operator-() const;

	constexpr bool operator==(vector4_T v) const;
	constexpr bool operator!=(vector4_T v) const;

	static constexpr vector4_T zero();
	static constexpr vector4_T one();

	using underlying_type = T;
};

template <typename T>
constexpr vector4_T<T> operator*(T f, vector4_T<T> v);
template <typename T>
constexpr vector4_T<T> operator*(vector4_T<T> v, T f);
template <typename T>
constexpr vector4_T<T> operator/(vector4_T<T> v, T f);
template <typename T>
constexpr vector4_T<T>& operator*=(vector4_T<T>& v, T f);
template <typename T>
constexpr vector4_T<T>& operator/=(vector4_T<T>& v, T f);

// template <typename T>
// T norm(vector4_T<T> v);
// template <typename T>
// constexpr T norm_squared(vector4_T<T> v);
// template <typename T>
// vector4_T<T> normalize(vector4_T<T> v);
// template <typename T>
// constexpr T dot(vector4_T<T> lhs, vector4_T<T> rhs);
// template <typename T>
// constexpr vector4_T<T> lerp(vector4_T<T> begin, vector4_T<T> end, T
// percent); template <typename T> vector4_T<T> nlerp(vector4_T<T> begin,
// vector4_T<T> end, T percent); template <typename T> T
// distance_between(vector4_T<T> v1, vector4_T<T> v2); template <typename T>
// constexpr T distance_squared_between(vector4_T<T> v1, vector4_T<T> v2);
// template <typename T>
// constexpr vector4_T<T> from_to(vector4_T<T> from, vector4_T<T> to);
// template <typename T>
// constexpr bool nearly_equal(vector4_T<T> v1, vector4_T<T> v2, T e =
// epsilon); template <typename T> constexpr vector4_T<T>
// element_wise_min(vector4_T<T> v0, vector4_T<T> v1); template <typename T>
// constexpr vector4_T<T> element_wise_max(vector4_T<T> v0, vector4_T<T> v1);
// template <typename T>
// vector4_T<T> element_wise_abs(vector4_T<T> v);
// template <typename T>
// constexpr vector4_T<T> element_wise_lerp(vector4_T<T> begin,
//                                          vector4_T<T> end,
//                                          vector4_T<T> percent);

template <typename T>
std::ostream& operator<<(std::ostream& os, vector4_T<T> v);

namespace detail
{
template <typename T>
struct is_vector<vector4_T<T>> : std::true_type
{
};
}  // namespace detail

using vector4 = vector4_T<float>;
using vector4d = vector4_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_VECTOR4_HPP
