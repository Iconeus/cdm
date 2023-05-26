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

#ifndef CDM_MATHS_DECL_DIRECTION3_HPP
#define CDM_MATHS_DECL_DIRECTION3_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>
#include <cdm/decl/maths/misc.hpp>
#include <cdm/decl/maths/vector3.hpp>

#include <array>

namespace cdm
{
template <typename T>
class direction3_T
{
public:
	using underlying_type = T;
	static constexpr size_t component_count = 3;

	constexpr direction3_T() = default;
	constexpr direction3_T(T x_, T y_, T z_);
	explicit constexpr direction3_T(const vector3_T<T>& v);

	constexpr const T& x() const;
	constexpr const T& y() const;
	constexpr const T& z() const;

	constexpr std::array<T, 3> to_array() const;

	template <typename U>
	constexpr operator direction3_T<U>() const;

	constexpr direction3_T operator-() const;

	constexpr bool operator==(const direction3_T& v) const;
	constexpr bool operator!=(const direction3_T& v) const;

	constexpr bool nearly_equal(const direction3_T& v, T e = T(epsilon)) const;

	template <typename Index>
	constexpr const T& operator[](Index index) const;

	static constexpr direction3_T already_normalized(T x_, T y_, T z_);
	static constexpr direction3_T already_normalized(const vector3_T<T>& v);

	static constexpr direction3_T posX();
	static constexpr direction3_T posY();
	static constexpr direction3_T posZ();
	static constexpr direction3_T negX();
	static constexpr direction3_T negY();
	static constexpr direction3_T negZ();

private:
	T m_x;
	T m_y;
	T m_z;
};

template <typename T>
constexpr vector3_T<T> operator*(T t, const direction3_T<T>& d);
template <typename T>
constexpr vector3_T<T> operator*(const direction3_T<T>& d, T t);

namespace detail
{
template <typename T>
struct is_vector<direction3_T<T>> : std::true_type
{
};
}  // namespace detail

using direction3 = direction3_T<float>;
using direction3d = direction3_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_DIRECTION3_HPP
