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

#ifndef CDM_MATHS_DECL_POINT2_HPP
#define CDM_MATHS_DECL_POINT2_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>
#include <cdm/decl/maths/misc.hpp>
#include <cdm/decl/maths/vector.hpp>

#include <array>

namespace cdm
{
template <typename T>
struct point2_T
{
	T x, y;

	using underlying_type = T;
	static constexpr size_t component_count = 2;

	constexpr point2_T() = default;
	constexpr point2_T(T x_, T y_);
	explicit constexpr point2_T(const vector2_T<T>& v);

	static constexpr point2_T from_array(const std::array<T, 2>& arr);
	constexpr std::array<T, 2> to_array() const;

	template <typename U>
	constexpr operator point2_T<U>() const;

	constexpr point2_T& element_wise_clamp(const point2_T& min,
	                                       const point2_T& max);
	constexpr point2_T get_element_wise_clamped(const point2_T& min,
	                                            const point2_T& max) const;

	constexpr point2_T operator+(const point2_T& v) const;
	constexpr point2_T operator-(const point2_T& v) const;
	constexpr point2_T operator-() const;
	constexpr point2_T operator*(T t) const;
	constexpr point2_T operator/(T t) const;

	constexpr point2_T& operator+=(const point2_T& v);
	constexpr point2_T& operator-=(const point2_T& v);
	constexpr point2_T& operator*=(T t);
	constexpr point2_T& operator/=(T t);

	constexpr bool operator==(const point2_T& v) const;
	constexpr bool operator!=(const point2_T& v) const;

	constexpr bool nearly_equal(const point2_T& v, T e = T(epsilon)) const;

	template <typename Index>
	constexpr T& operator[](Index index);
	template <typename Index>
	constexpr const T& operator[](Index index) const;

	static constexpr point2_T zero();
	static constexpr point2_T one();
};

template <typename T>
constexpr point2_T<T> operator*(T t, const point2_T<T>& v);

namespace detail
{
template <typename T>
struct is_vector<point2_T<T>> : std::true_type
{
};
}  // namespace detail

using point2 = point2_T<float>;
using point2d = point2_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_POINT2_HPP
