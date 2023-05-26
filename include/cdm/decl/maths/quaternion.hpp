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

#ifndef CDM_MATHS_DECL_QUATERNION_HPP
#define CDM_MATHS_DECL_QUATERNION_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>

#include <array>
#include <iosfwd>

namespace cdm
{
template <typename T>
struct quaternion_T
{
	T x, y, z, w;

	quaternion_T() = default;
	constexpr quaternion_T(T x_, T y_, T z_, T w_);
	constexpr quaternion_T(std::array<T, 4> a);
	quaternion_T(direction3_T<T> axis, radian_T<T> angle);
	template <std::signed_integral U, U NumeratorT, U DenominatorT>
	quaternion_T(direction3_T<T> axis,
	             static_pi_fraction_T<U, NumeratorT, DenominatorT> angle);

	template <typename U>
	explicit constexpr operator quaternion_T<U>() const;

	constexpr operator std::array<T, 4>() const;

	template <typename U = T>
	constexpr std::array<U, 4> to_array() const;

	static constexpr quaternion_T identity();
	static quaternion_T from_rotation_matrix(const matrix3_T<T>& m);
	static quaternion_T look_at(
	    direction3_T<T> forward,
	    direction3_T<T> upward = direction3_T<T>::posY());

	T norm() const;
	constexpr T norm_squared() const;

	quaternion_T& inverse();
	constexpr quaternion_T& conjugate();
	quaternion_T& normalize();
	constexpr quaternion_T& clamp(quaternion_T min, quaternion_T max);

	quaternion_T get_inversed() const;
	constexpr quaternion_T get_conjugated() const;
	quaternion_T get_normalized() const;
	constexpr quaternion_T get_clamped(quaternion_T min,
	                                   quaternion_T max) const;

	euler_angles_T<T> to_euler_angles() const;

	constexpr quaternion_T operator+(quaternion_T q) const;
	constexpr quaternion_T operator-(quaternion_T q) const;

	// TODO: implement operator* for normalized<>
	// if result is normalized too
	constexpr quaternion_T operator*(quaternion_T q) const;

	constexpr vector3_T<T> operator*(vector3_T<T> v) const;
	constexpr direction3_T<T> operator*(direction3_T<T> d) const;
	constexpr point3_T<T> operator*(point3_T<T> p) const;
	constexpr quaternion_T operator*(T f) const;
	constexpr quaternion_T operator/(T f) const;

	constexpr quaternion_T& operator+=(quaternion_T q);
	constexpr quaternion_T& operator-=(quaternion_T q);
	constexpr quaternion_T& operator*=(quaternion_T q);
	constexpr quaternion_T& operator*=(T f);
	constexpr quaternion_T& operator/=(T f);

	constexpr quaternion_T operator-() const;

	constexpr bool operator==(quaternion_T v) const;
	constexpr bool operator!=(quaternion_T v) const;

	using underlying_type = T;
};

template <typename T>
constexpr T dot(quaternion_T<T> lhs, quaternion_T<T> rhs);
template <typename T>
constexpr quaternion_T<T> cross(quaternion_T<T> lhs, quaternion_T<T> rhs);
template <typename T>
constexpr quaternion_T<T> lerp(quaternion_T<T> begin,
                               quaternion_T<T> end,
                               T percent);
template <typename T>
quaternion_T<T> nlerp(quaternion_T<T> begin, quaternion_T<T> end, T percent);
template <typename T>
quaternion_T<T> slerp(quaternion_T<T> begin, quaternion_T<T> end, T percent);

template <typename T>
std::ostream& operator<<(std::ostream& os, quaternion_T<T> q);

using quaternion = quaternion_T<float>;
using quaterniond = quaternion_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_QUATERNION_HPP
