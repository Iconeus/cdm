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

#ifndef CDM_MATHS_DECL_DIRECTION2_HPP
#define CDM_MATHS_DECL_DIRECTION2_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>
#include <cdm/decl/maths/misc.hpp>
#include <cdm/decl/maths/vector2.hpp>

#include <array>

namespace cdm
{
template <typename T>
class direction2_T
{
public:
	using underlying_type = T;
	static constexpr size_t component_count = 2;

	constexpr direction2_T() = default;
	constexpr direction2_T(T x_, T y_);
	explicit constexpr direction2_T(const vector2_T<T>& v);

	constexpr const T& x() const;
	constexpr const T& y() const;

	constexpr std::array<T, 2> to_array() const;

	template <typename U>
	constexpr operator direction2_T<U>() const;

	constexpr direction2_T operator-() const;

	constexpr bool operator==(const direction2_T& v) const;
	constexpr bool operator!=(const direction2_T& v) const;

	constexpr bool nearly_equal(const direction2_T& v, T e = T(epsilon)) const;

	template <typename Index>
	constexpr const T& operator[](Index index) const;

	static constexpr direction2_T already_normalized(T x_, T y_);
	static constexpr direction2_T already_normalized(const vector2_T<T>& v);

	static constexpr direction2_T posX();
	static constexpr direction2_T posY();
	static constexpr direction2_T negX();
	static constexpr direction2_T negY();

private:
	T m_x;
	T m_y;
};

template <typename T>
constexpr vector2_T<T> operator*(T t, const direction2_T<T>& d);
template <typename T>
constexpr vector2_T<T> operator*(const direction2_T<T>& d, T t);

namespace detail
{
template <typename T>
struct is_vector<direction2_T<T>> : std::true_type
{
};
}  // namespace detail

using direction2 = direction2_T<float>;
using direction2d = direction2_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_DIRECTION2_HPP
