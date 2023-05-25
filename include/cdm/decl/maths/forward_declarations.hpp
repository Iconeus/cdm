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

#ifndef CDM_MATHS_FORWARD_DECLARATIONS_HPP
#define CDM_MATHS_FORWARD_DECLARATIONS_HPP 1

#include <cdm/concepts.hpp>

namespace cdm
{
// clang-format off
template <typename T> concept normalizable = requires(T& t, const T& ct)
{
	{ t.normalize() } -> std::convertible_to<T>;
	{ t.get_normalized() } -> std::convertible_to<T>;
	{ ct.get_normalized() } -> std::convertible_to<T>;
};
// clang-format on

template <normalizable T>
class normalized;

template <typename T>
struct complex_T;

template <typename T>
struct radian_T;

template <typename T>
struct degree_T;

template <std::signed_integral T>
struct pi_fraction_T;

template <std::signed_integral T, T NumeratorT, T DenominatorT>
struct static_pi_fraction_T;

template <typename T>
struct vector2_T;

template <typename T>
struct point2_T;

template <typename T>
class direction2_T;

template <typename T>
struct vector3_T;

template <typename T>
struct point3_T;

template <typename T>
class direction3_T;

template <typename T>
struct vector4_T;

template <typename T>
struct matrix2_T;

template <typename T>
struct matrix3_T;

template <typename T>
struct matrix4_T;

template <typename T>
struct perspective_T;

template <typename T>
struct euler_angles_T;

template <typename T>
struct quaternion_T;

enum class line_representation
{
	SlopeIntercept,
	Points,
	PointAngleDegree,
	PointAngleRadian,
	PointAnglePiFraction,
};
template <typename T, line_representation representation>
struct line_T;

template <typename T>
struct segment2_T;

template <typename T>
struct segment3_T;

template <typename T>
struct plane_T;

template <typename T>
struct oriented_plane_T;

template <typename T>
struct aabb2_T;

template <typename T>
struct aabb3_T;

template <typename T>
struct circle_T;

template <typename T>
struct ray2_T;

template <typename T>
struct ray3_T;

template <typename T>
struct transform2_T;

template <typename T>
struct transform3_T;

template <typename T>
struct uniform_transform2_T;

template <typename T>
struct uniform_transform3_T;

template <typename T>
struct unscaled_transform2_T;

template <typename T>
struct unscaled_transform3_T;

template <arithmetic T>
class value_domain_T;

template <arithmetic T>
class unnormalized_value_T;

template <arithmetic T>
class normalized_value_T;
}  // namespace cdm

#endif  // CDM_MATHS_CONSTANTS_HPP
