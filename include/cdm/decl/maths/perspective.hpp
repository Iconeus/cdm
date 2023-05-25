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

#ifndef CDM_MATHS_DECL_PERSPECTIVE_HPP
#define CDM_MATHS_DECL_PERSPECTIVE_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>

#include <array>

namespace cdm
{
template <typename T>
struct perspective_T
{
private:
	radian_T<T> m_angle;
	T m_ratio;
	T m_invRatio;
	T m_near;
	T m_far;
	T m_focalLength;

public:
	perspective_T(radian_T<T> angle, T ratio, T near, T far);
	template <std::signed_integral U, U NumeratorT, U DenominatorT>
	perspective_T(static_pi_fraction_T<U, NumeratorT, DenominatorT> angle,
	              T ratio,
	              T near,
	              T far);

	void set(radian_T<T> angle, T ratio, T near, T far);
	template <std::signed_integral U, U NumeratorT, U DenominatorT>
	void set(static_pi_fraction_T<U, NumeratorT, DenominatorT> angle,
	         T ratio,
	         T near,
	         T far);

	void set_angle(radian_T<T> angle);
	template <std::signed_integral U, U NumeratorT, U DenominatorT>
	void set_angle(static_pi_fraction_T<U, NumeratorT, DenominatorT> angle);
	constexpr radian_T<T> get_angle() const;

	constexpr void set_ratio(T ratio);
	constexpr T get_ratio() const;

	constexpr void set_near(T near_plane_T);
	constexpr T get_near() const;

	constexpr void set_far(T far_plane_T);
	constexpr T get_far() const;

	constexpr matrix4_T<T> to_matrix4() const;
	constexpr matrix4_T<T> to_inverse_matrix4() const;

	template <typename U>
	friend constexpr matrix4_T<U> operator*(const matrix4_T<U>& m,
	                                        const perspective_T<U>& p);
	template <typename U>
	friend constexpr matrix4_T<U> operator*(const perspective_T<U>& p,
	                                        const matrix4_T<U>& m);
	template <typename U>
	friend constexpr vector4_T<U> operator*(const perspective_T<U>& p,
	                                        const vector4_T<U>& v);
	template <typename U>
	friend constexpr matrix4_T<U> operator*(const unscaled_Transform3_T<U>& t,
	                                        const perspective_T<U>& p);
	template <typename U>
	friend constexpr matrix4_T<U> operator*(const perspective_T<U>& p,
	                                        const unscaled_Transform3_T<U>& t);

	using underlying_type = T;
};

using perspective = perspective_T<float>;
using perspectived = perspective_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_PERSPECTIVE_HPP
