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

#ifndef CDM_MATHS_DECL_VECTOR2_HPP
#define CDM_MATHS_DECL_VECTOR2_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>
#include <cdm/decl/maths/misc.hpp>

#include <array>
#include <iosfwd>

namespace cdm
{
template <typename T>
struct vector2_T
{
	T x, y;

	vector2_T() = default;
	constexpr vector2_T(T x_, T y_);
	constexpr vector2_T(std::array<T, 2> a);

	template <typename U>
	explicit constexpr operator vector2_T<U>() const;

	constexpr operator std::array<T, 2>() const;

	template <typename U = T>
	constexpr std::array<U, 2> to_array() const;

	T norm() const;
	constexpr T norm_squared() const;
	vector2_T& normalize();
	vector2_T get_normalized() const;
	constexpr vector2_T& clamp(vector2_T min, vector2_T max);
	constexpr vector2_T get_clamped(vector2_T min, vector2_T max) const;

	constexpr T& operator[](size_t i);
	constexpr const T& operator[](size_t i) const;

	constexpr vector2_T operator+(vector2_T v) const;
	constexpr vector2_T operator-(vector2_T v) const;

	constexpr vector2_T& operator+=(vector2_T v);
	constexpr vector2_T& operator-=(vector2_T v);

	constexpr vector2_T operator-() const;

	constexpr bool operator==(vector2_T v) const;
	constexpr bool operator!=(vector2_T v) const;

	static constexpr vector2_T zero();
	static constexpr vector2_T one();

	using underlying_type = T;
};

template <typename T>
constexpr vector2_T<T> operator*(T f, vector2_T<T> v);
template <typename T>
constexpr vector2_T<T> operator*(vector2_T<T> v, T f);
template <typename T>
constexpr vector2_T<T> operator/(vector2_T<T> v, T f);
template <typename T>
constexpr vector2_T<T>& operator*=(vector2_T<T>& v, T f);
template <typename T>
constexpr vector2_T<T>& operator/=(vector2_T<T>& v, T f);

template <typename T>
T norm(vector2_T<T> v);
template <typename T>
constexpr T norm_squared(vector2_T<T> v);
template <typename T>
vector2_T<T> normalize(vector2_T<T> v);
template <typename T>
constexpr T dot(vector2_T<T> lhs, vector2_T<T> rhs);
template <typename T>
constexpr T cross(vector2_T<T> lhs, vector2_T<T> rhs);
template <typename T>
constexpr vector2_T<T> lerp(vector2_T<T> begin, vector2_T<T> end, T percent);
template <typename T>
vector2_T<T> nlerp(vector2_T<T> begin, vector2_T<T> end, T percent);
template <typename T>
vector2_T<T> slerp(vector2_T<T> begin, vector2_T<T> end, T percent);
template <typename T>
T distance_between(vector2_T<T> v1, vector2_T<T> v2);
template <typename T>
constexpr T distance_squared_between(vector2_T<T> v1, vector2_T<T> v2);
template <typename T>
constexpr vector2_T<T> from_to(vector2_T<T> from, vector2_T<T> to);
template <typename T>
radian_T<T> angle_between(vector2_T<T> v1, vector2_T<T> v2);
template <typename T>
constexpr bool nearly_equal(vector2_T<T> v1,
                            vector2_T<T> v2,
                            T e = T(epsilon));
template <typename T>
constexpr vector2_T<T> element_wise_min(vector2_T<T> v0, vector2_T<T> v1);
template <typename T>
constexpr vector2_T<T> element_wise_max(vector2_T<T> v0, vector2_T<T> v1);
template <typename T>
vector2_T<T> element_wise_abs(vector2_T<T> v);
template <typename T>
constexpr vector2_T<T> element_wise_lerp(vector2_T<T> begin,
                                         vector2_T<T> end,
                                         vector2_T<T> percent);

template <typename T>
std::ostream& operator<<(std::ostream& os, vector2_T<T> v);

namespace detail
{
template <typename T>
struct is_vector<vector2_T<T>> : std::true_type
{
};
}  // namespace detail

using vector2 = vector2_T<float>;
using vector2d = vector2_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_VECTOR2_HPP
