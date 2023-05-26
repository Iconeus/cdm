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

#ifndef CDM_MATHS_DECL_VECTOR3_HPP
#define CDM_MATHS_DECL_VECTOR3_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>
#include <cdm/decl/maths/misc.hpp>
#include <cdm/decl/maths/vector.hpp>

#include <array>

namespace cdm
{
template <typename T>
struct vector3_T
{
	T x, y, z;

	using underlying_type = T;
	static constexpr size_t component_count = 3;

	constexpr vector3_T() = default;
	constexpr vector3_T(T x_, T y_, T z_);
	constexpr vector3_T(const vector2_T<T>& v, T z_);
	constexpr vector3_T(const point3_T<T>& p);
	constexpr vector3_T(const direction3_T<T>& d);

	static constexpr vector3_T from_array(const std::array<T, 3>& arr);
	constexpr std::array<T, 3> to_array() const;

	template <typename U>
	constexpr operator vector3_T<U>() const;

	constexpr vector2_T<T> xy() const;

	constexpr T norm() const;
	constexpr T norm_squared() const;
	constexpr vector3_T& normalize();
	constexpr vector3_T get_normalized() const;
	constexpr vector3_T& element_wise_clamp(const vector3_T& min,
	                                        const vector3_T& max);
	constexpr vector3_T get_element_wise_clamped(const vector3_T& min,
	                                             const vector3_T& max) const;

	constexpr vector3_T& set_length(T length);

	constexpr vector3_T operator+(const vector3_T& v) const;
	constexpr vector3_T operator-(const vector3_T& v) const;
	constexpr vector3_T operator-() const;
	constexpr vector3_T operator*(T t) const;
	constexpr vector3_T operator/(T t) const;

	constexpr vector3_T& operator+=(const vector3_T& v);
	constexpr vector3_T& operator-=(const vector3_T& v);
	constexpr vector3_T& operator*=(T t);
	constexpr vector3_T& operator/=(T t);

	constexpr bool operator==(const vector3_T& v) const;
	constexpr bool operator!=(const vector3_T& v) const;

	constexpr bool nearly_equal(const vector3_T& v, T e = T(epsilon)) const;

	template <typename Index>
	constexpr T& operator[](Index index);
	template <typename Index>
	constexpr const T& operator[](Index index) const;

	static constexpr vector3_T zero();
	static constexpr vector3_T one();
};

template <typename T>
constexpr vector3_T<T> operator*(T t, const vector3_T<T>& v);

namespace detail
{
template <typename T>
struct is_vector<vector3_T<T>> : std::true_type
{
};
}  // namespace detail

using vector3 = vector3_T<float>;
using vector3d = vector3_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_VECTOR3_HPP
