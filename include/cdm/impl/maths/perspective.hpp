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

#ifndef CDM_MATHS_IMPL_PERSPECTIVE_HPP
#define CDM_MATHS_IMPL_PERSPECTIVE_HPP 1

#include <cdm/decl/maths/matrix4.hpp>
#include <cdm/decl/maths/perspective.hpp>
#include <cdm/decl/maths/radian.hpp>
#include <cdm/decl/maths/static_pi_fraction.hpp>
#include <cdm/decl/maths/unscaled_transform3.hpp>

namespace cdm
{
template <typename T>
inline perspective_T<T>::perspective_T(radian_T<T> angle,
                                       T ratio,
                                       T near,
                                       T far)
    : m_angle{angle},
      m_ratio{ratio},
      m_invRatio{T(1) / m_ratio},
      m_near{near},
      m_far{far},
      m_focalLength{T(1) / tan(m_angle / T(2))}
{
}

template <typename T>
template <std::signed_integral U, U NumeratorT, U DenominatorT>
inline perspective_T<T>::perspective_T(
    static_pi_fraction_T<U, NumeratorT, DenominatorT> angle,
    T ratio,
    T near,
    T far)
    : perspective_T(angle, ratio, near, far),
      m_focalLength{
          T(1) /
          tan<T>(static_pi_fraction<U, NumeratorT, DenominatorT * U(2)>{})}
{
}

template <typename T>
inline void perspective_T<T>::set(radian_T<T> angle, T ratio, T near, T far)
{
	m_angle = angle;
	m_ratio = ratio;
	m_invRatio = T(1) / m_ratio;
	m_near = near;
	m_far = far;
	m_focalLength = T(1) / tan(m_angle / T(2));
}

template <typename T>
template <std::signed_integral U, U NumeratorT, U DenominatorT>
inline void perspective_T<T>::set(
    static_pi_fraction_T<U, NumeratorT, DenominatorT> angle,
    T ratio,
    T near,
    T far)
{
	set(angle, ratio, near, far);
	m_focalLength =
	    T(1) /
	    tan<T>(static_pi_fraction<U, NumeratorT, DenominatorT * U(2)>{});
}

template <typename T>
inline void perspective_T<T>::set_angle(radian_T<T> angle)
{
	m_angle = angle;
	m_focalLength = T(1) / tan(angle / T(2));
}

template <typename T>
template <std::signed_integral U, U NumeratorT, U DenominatorT>
inline void perspective_T<T>::set_angle(
    static_pi_fraction_T<U, NumeratorT, DenominatorT> angle)
{
	m_angle = angle;
	m_focalLength =
	    T(1) /
	    tan<T>(static_pi_fraction<U, NumeratorT, DenominatorT * U(2)>{});
}

template <typename T>
constexpr radian_T<T> perspective_T<T>::get_angle() const
{
	return m_angle;
}

template <typename T>
constexpr void perspective_T<T>::set_ratio(T ratio)
{
	m_ratio = ratio;
	m_invRatio = T(1) / m_ratio;
}

template <typename T>
constexpr T perspective_T<T>::get_ratio() const
{
	return m_ratio;
}

template <typename T>
constexpr void perspective_T<T>::set_near(T near_plane_T)
{
	m_near = near_plane_T;
}

template <typename T>
constexpr T perspective_T<T>::get_near() const
{
	return m_near;
}

template <typename T>
constexpr void perspective_T<T>::set_far(T far_plane_T)
{
	m_far = far_plane_T;
}

template <typename T>
constexpr T perspective_T<T>::get_far() const
{
	return m_far;
}

template <typename T>
constexpr matrix4_T<T> perspective_T<T>::to_matrix4() const
{
	matrix4_T<T> res{matrix4_T<T>::zero()};
	const T a = m_focalLength * m_invRatio;
	const T b = m_focalLength;
	const T farMinusNear = m_far - m_near;
	const T invFarMinusNear = T(1) / farMinusNear;
	const T c = m_near * invFarMinusNear;
	const T d = m_far * c;

	res.column(0).row(0) = a;
	res.column(1).row(1) = b;
	res.column(2).row(2) = c;
	res.column(2).row(3) = T(-1);
	res.column(3).row(2) = d;

	//      0   1   2   3
	//   +-----------------+
	// 0 |  a   0   0   0  |
	// 1 |  0   b   0   0  |
	// 2 |  0   0   c   d  |
	// 3 |  0   0  -1   0  |
	//   +-----------------+

	return res;
}

template <typename T>
constexpr matrix4_T<T> perspective_T<T>::to_inverse_matrix4() const
{
	matrix4_T<T> res{matrix4_T<T>::zero()};
	const T a = m_focalLength * m_invRatio;
	const T b = m_focalLength;
	const T farMinusNear = m_far - m_near;
	const T invFarMinusNear = T(1) / farMinusNear;
	const T c = m_near * invFarMinusNear;
	const T d = m_far * c;

	res.column(0).row(0) = T(1) / a;
	res.column(1).row(1) = T(1) / b;
	res.column(3).row(2) = T(-1);
	res.column(2).row(3) = T(1) / d;
	res.column(3).row(3) = c / d;

	//      0   1   2   3
	//   +-----------------+
	// 0 | 1/a  0   0   0  |
	// 1 |  0  1/b  0   0  |
	// 2 |  0   0   0  -1  |
	// 3 |  0   0  1/d c/d |
	//   +-----------------+

	return res;
}

template <typename T>
constexpr matrix4_T<T> operator*(const matrix4_T<T>& m,
                                 const perspective_T<T>& p)
{
	const T a = p.m_focalLength * p.m_invRatio;
	const T b = p.m_focalLength;
	const T farMinusNear = p.m_far - p.m_near;
	const T invFarMinusNear = T(1) / farMinusNear;
	const T c = p.m_near * invFarMinusNear;
	const T d = p.m_far * c;

	matrix4_T<T> res;
	res.column(0).row(0) = a * m.column(0).row(0);
	res.column(1).row(0) = b * m.column(1).row(0);
	res.column(2).row(0) = c * m.column(2).row(0) - m.column(3).row(0);
	res.column(3).row(0) = d * m.column(2).row(0);
	res.column(0).row(1) = a * m.column(0).row(1);
	res.column(1).row(1) = b * m.column(1).row(1);
	res.column(2).row(1) = c * m.column(2).row(1) - m.column(3).row(1);
	res.column(3).row(1) = d * m.column(2).row(1);
	res.column(0).row(2) = a * m.column(0).row(2);
	res.column(1).row(2) = b * m.column(1).row(2);
	res.column(2).row(2) = c * m.column(2).row(2) - m.column(3).row(2);
	res.column(3).row(2) = d * m.column(2).row(2);
	res.column(0).row(3) = a * m.column(0).row(3);
	res.column(1).row(3) = b * m.column(1).row(3);
	res.column(2).row(3) = c * m.column(2).row(3) - m.column(3).row(3);
	res.column(3).row(3) = d * m.column(2).row(3);
	return res;
}

template <typename T>
constexpr matrix4_T<T> operator*(const perspective_T<T>& p,
                                 const matrix4_T<T>& m)
{
	const T a = p.m_focalLength * p.m_invRatio;
	const T b = p.m_focalLength;
	const T farMinusNear = p.m_far - p.m_near;
	const T invFarMinusNear = T(1) / farMinusNear;
	const T c = p.m_near * invFarMinusNear;
	const T d = p.m_far * c;

	matrix4_T<T> res;
	res.column(0).row(0) = m.column(0).row(0) * a;
	res.column(1).row(0) = m.column(1).row(0) * a;
	res.column(2).row(0) = m.column(2).row(0) * a;
	res.column(3).row(0) = m.column(3).row(0) * a;
	res.column(0).row(1) = m.column(0).row(1) * b;
	res.column(1).row(1) = m.column(1).row(1) * b;
	res.column(2).row(1) = m.column(2).row(1) * b;
	res.column(3).row(1) = m.column(3).row(1) * b;
	res.column(0).row(2) = m.column(0).row(2) * c + m.column(0).row(3) * d;
	res.column(1).row(2) = m.column(1).row(2) * c + m.column(1).row(3) * d;
	res.column(2).row(2) = m.column(2).row(2) * c + m.column(2).row(3) * d;
	res.column(3).row(2) = m.column(3).row(2) * c + m.column(3).row(3) * d;
	res.column(0).row(3) = -m.column(0).row(2);
	res.column(1).row(3) = -m.column(1).row(2);
	res.column(2).row(3) = -m.column(2).row(2);
	res.column(3).row(3) = -m.column(3).row(2);
	return res;
}

template <typename T>
constexpr vector4_T<T> operator*(const perspective_T<T>& p,
                                 const vector4_T<T>& v)
{
	const T a = p.m_focalLength * p.m_invRatio;
	const T b = p.m_focalLength;
	const T farMinusNear = p.m_far - p.m_near;
	const T invFarMinusNear = T(1) / farMinusNear;
	const T c = p.m_near * invFarMinusNear;
	const T d = p.m_far * c;

	//                       +---+
	//                       | x |
	//                       | y |
	//                       | z |
	//                       | w |
	//      0   1   2   3    +---+
	//   +-----------------+
	// 0 |  a   0   0   0  |
	// 1 |  0   b   0   0  |
	// 2 |  0   0   c   d  |
	// 3 |  0   0  -1   0  |
	//   +-----------------+

	return {
	    a * v.x,
	    b * v.y,
	    c * v.z + d * v.w,
	    -v.z,
	};
}

template <typename T>
constexpr matrix4_T<T> operator*(const unscaled_transform3_T<T>& t,
                                 const perspective_T<T>& p)
{
	const T a = p.m_focalLength * p.m_invRatio;
	const T b = p.m_focalLength;
	const T farMinusNear = p.m_far - p.m_near;
	const T invFarMinusNear = T(1) / farMinusNear;
	const T c = p.m_near * invFarMinusNear;
	const T d = p.m_far * c;
	const T xx = t.rotation.x * t.rotation.x;
	const T yy = t.rotation.y * t.rotation.y;
	const T zz = t.rotation.z * t.rotation.z;
	const T wx = t.rotation.w * t.rotation.x;
	const T wy = t.rotation.w * t.rotation.y;
	const T wz = t.rotation.w * t.rotation.z;
	const T xy = t.rotation.x * t.rotation.y;
	const T xz = t.rotation.x * t.rotation.z;
	const T yz = t.rotation.y * t.rotation.z;

	return {
	    a * (T(1) - T(2) * (yy + zz)),
	    b * (T(2) * (xy - wz)),
	    c * (T(2) * (xz + wy)) - t.position.x,
	    d * (T(2) * (xz + wy)),

	    a * (T(2) * (xy + wz)),
	    b * (T(1) - T(2) * (xx + zz)),
	    c * (T(2) * (yz - wx)) - t.position.y,
	    d * (T(2) * (yz - wx)),

	    a * (T(2) * (xz - wy)),
	    b * (T(2) * (yz + wx)),
	    c * (T(1) - T(2) * (xx + yy)) - t.position.z,
	    d * (T(1) - T(2) * (xx + yy)),

	    T(0),
	    T(0),
	    T(-1),
	    T(0),
	};
}

template <typename T>
constexpr matrix4_T<T> operator*(const perspective_T<T>& p,
                                 const unscaled_transform3_T<T>& t)
{
	const T a = p.m_focalLength * p.m_invRatio;
	const T b = p.m_focalLength;
	const T farMinusNear = p.m_far - p.m_near;
	const T invFarMinusNear = T(1) / farMinusNear;
	const T c = p.m_near * invFarMinusNear;
	const T d = p.m_far * c;
	const T xx = t.rotation.x * t.rotation.x;
	const T yy = t.rotation.y * t.rotation.y;
	const T zz = t.rotation.z * t.rotation.z;
	const T wx = t.rotation.w * t.rotation.x;
	const T wy = t.rotation.w * t.rotation.y;
	const T wz = t.rotation.w * t.rotation.z;
	const T xy = t.rotation.x * t.rotation.y;
	const T xz = t.rotation.x * t.rotation.z;
	const T yz = t.rotation.y * t.rotation.z;

	matrix4_T<T> res;

	res.row(0).column(0) = (T(1) - T(2) * (yy + zz)) * a;
	res.row(0).column(1) = (T(2) * (xy - wz)) * a;
	res.row(0).column(2) = (T(2) * (xz + wy)) * a;
	res.row(0).column(3) = t.position.x * a;

	res.row(1).column(0) = (T(2) * (xy + wz)) * b;
	res.row(1).column(1) = (T(1) - T(2) * (xx + zz)) * b;
	res.row(1).column(2) = (T(2) * (yz - wx)) * b;
	res.row(1).column(3) = t.position.y * b;

	res.row(2).column(0) = (T(2) * (xz - wy)) * c;
	res.row(2).column(1) = (T(2) * (yz + wx)) * c;
	res.row(2).column(2) = (T(1) - T(2) * (xx + yy)) * c;
	res.row(2).column(3) = t.position.z * c + d;

	res.row(3).column(0) = -(T(2) * (xz - wy));
	res.row(3).column(1) = -(T(2) * (yz + wx));
	res.row(3).column(2) = -(T(1) - T(2) * (xx + yy));
	res.row(3).column(3) = -t.position.z;

	return res;
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_PERSPECTIVE_HPP
