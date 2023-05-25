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

#ifndef CDM_MATHS_DECL_ORIENTED_PLANE_HPP
#define CDM_MATHS_DECL_ORIENTED_PLANE_HPP 1

#include <cdm/decl/maths/constants.hpp>
#include <cdm/decl/maths/forward_declarations.hpp>

#include <array>
#include <iosfwd>

namespace cdm
{
template <typename T>
struct oriented_plane_T
{
	vector3_T<T> origin;
	direction3_T<T> normal;
	direction3_T<T> tangent;

	oriented_plane_T() = default;
	oriented_plane_T(const oriented_plane_T&) = default;
	oriented_plane_T(oriented_plane_T&&) = default;
	oriented_plane_T& operator=(const oriented_plane_T&) = default;
	oriented_plane_T& operator=(oriented_plane_T&&) = default;

	constexpr oriented_plane_T(vector3_T<T> origin_,
	                           direction3_T<T> normal_,
	                           direction3_T<T> tangent_);
	constexpr oriented_plane_T(plane_T<T> plane, direction3_T<T> tangent_);

	template <typename U>
	explicit constexpr operator oriented_plane_T<U>() const;

	constexpr T evaluate(vector3_T<T> point) const;
	constexpr vector3_T<T> project3d(vector3_T<T> point) const;
	constexpr vector2_T<T> project2d(vector3_T<T> point) const;
	constexpr vector3_T<T> unproject(vector2_T<T> point) const;

	using underlying_type = T;
};

template <typename T>
constexpr bool collides(const oriented_plane_T<T>& plane,
                        ray3_T<T> r,
                        vector3_T<T>& collision_point,
                        T e = T(epsilon));

template <typename T>
constexpr bool collides_bidirectional(const oriented_plane_T<T>& plane,
                                      ray3_T<T> r,
                                      vector3_T<T>& collision_point,
                                      T e = T(epsilon));

template <typename T>
std::ostream& operator<<(std::ostream& os, oriented_plane_T<T> p);

using oriented_plane = oriented_plane_T<float>;
using oriented_planed = oriented_plane_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_ORIENTED_PLANE_HPP
