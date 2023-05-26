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

#ifndef CDM_MATHS_IMPL_MATRIX4_HPP
#define CDM_MATHS_IMPL_MATRIX4_HPP 1

#include <cdm/decl/maths/complex.hpp>
#include <cdm/decl/maths/matrix2.hpp>
#include <cdm/decl/maths/matrix3.hpp>
#include <cdm/decl/maths/matrix4.hpp>
#include <cdm/decl/maths/perspective.hpp>
#include <cdm/decl/maths/radian.hpp>
#include <cdm/decl/maths/vector3.hpp>
#include <cdm/decl/maths/vector4.hpp>
#include <cdm/decl/maths/vector_proxy.hpp>

#include <cassert>
#include <iomanip>
#include <ostream>

namespace cdm
{
template <typename T>
constexpr matrix4_T<T>::matrix4_T(T e00,
                                  T e10,
                                  T e20,
                                  T e30,
                                  T e01,
                                  T e11,
                                  T e21,
                                  T e31,
                                  T e02,
                                  T e12,
                                  T e22,
                                  T e32,
                                  T e03,
                                  T e13,
                                  T e23,
                                  T e33)
    : m00{e00},
      m10{e10},
      m20{e20},
      m30{e30},
      m01{e01},
      m11{e11},
      m21{e21},
      m31{e31},
      m02{e02},
      m12{e12},
      m22{e22},
      m32{e32},
      m03{e03},
      m13{e13},
      m23{e23},
      m33{e33}
{
}

template <typename T>
constexpr matrix4_T<T>::matrix4_T(matrix2_T<T> m)
    : matrix4_T(m.m00,
                m.m10,
                T(0),
                T(0),
                m.m10,
                m.m11,
                T(0),
                T(0),
                T(0),
                T(0),
                T(1),
                T(0),
                T(0),
                T(0),
                T(0),
                T(1))
{
}

template <typename T>
constexpr matrix4_T<T>::matrix4_T(const matrix3_T<T>& m)
    : matrix4_T(m.m00,
                m.m10,
                m.m20,
                T(0),
                m.m01,
                m.m11,
                m.m21,
                T(0),
                m.m02,
                m.m12,
                m.m22,
                T(0),
                T(0),
                T(0),
                T(0),
                T(1))
{
}

template <typename T>
constexpr matrix4_T<T>::matrix4_T(const perspective_T<T>& p)
    : matrix4_T(p.to_matrix4())
{
}

template <typename T>
constexpr matrix4_T<T>::matrix4_T(const transform3_T<T>& t)
    : matrix4_T(t.to_matrix4())
{
}

template <typename T>
constexpr matrix4_T<T>::matrix4_T(const uniform_transform3_T<T>& t)
    : matrix4_T(t.to_matrix4())
{
}

template <typename T>
constexpr matrix4_T<T>::matrix4_T(const unscaled_transform3_T<T>& t)
    : matrix4_T(t.to_matrix4())
{
}

template <typename T>
constexpr matrix4_T<T>::matrix4_T(const std::array<T, 16>& a)
    : matrix4_T(a[0],
                a[1],
                a[2],
                a[3],
                a[4],
                a[5],
                a[6],
                a[7],
                a[8],
                a[9],
                a[10],
                a[11],
                a[12],
                a[13],
                a[14],
                a[15])
{
}

template <typename T>
template <typename U>
constexpr matrix4_T<T>::operator matrix4_T<U>() const
{
	return {
	    U(m00), U(m10), U(m20), U(m30),  //
	    U(m01), U(m11), U(m21), U(m31),  //
	    U(m02), U(m12), U(m22), U(m32),  //
	    U(m03), U(m13), U(m23), U(m33),  //
	};
}

template <typename T>
constexpr matrix4_T<T>::operator std::array<T, 16>() const
{
	return {
	    m00, m10, m20, m30,  //
	    m01, m11, m21, m31,  //
	    m02, m12, m22, m32,  //
	    m03, m13, m23, m33   //
	};
}

template <typename T>
template <typename U>
constexpr std::array<U, 16> matrix4_T<T>::to_array() const
{
	return {
	    static_cast<U>(m00),  //
	    static_cast<U>(m10),  //
	    static_cast<U>(m20),  //
	    static_cast<U>(m30),  //
	    static_cast<U>(m01),  //
	    static_cast<U>(m11),  //
	    static_cast<U>(m21),  //
	    static_cast<U>(m31),  //
	    static_cast<U>(m02),  //
	    static_cast<U>(m12),  //
	    static_cast<U>(m22),  //
	    static_cast<U>(m32),  //
	    static_cast<U>(m03),  //
	    static_cast<U>(m13),  //
	    static_cast<U>(m23),  //
	    static_cast<U>(m33)   //
	};
}

template <typename T>
constexpr matrix4_T<T> matrix4_T<T>::zero()
{
	return {
	    T(0), T(0), T(0), T(0),  //
	    T(0), T(0), T(0), T(0),  //
	    T(0), T(0), T(0), T(0),  //
	    T(0), T(0), T(0), T(0),  //
	};
}

template <typename T>
constexpr matrix4_T<T> matrix4_T<T>::identity()
{
	return {
	    T(1), T(0), T(0), T(0),  //
	    T(0), T(1), T(0), T(0),  //
	    T(0), T(0), T(1), T(0),  //
	    T(0), T(0), T(0), T(1),  //
	};
}

template <typename T>
constexpr matrix4_T<T> matrix4_T<T>::rows(vector4_T<T> row0,
                                          vector4_T<T> row1,
                                          vector4_T<T> row2,
                                          vector4_T<T> row3)
{
	return {
	    row0.x, row0.y, row0.z, row0.w,  //
	    row1.x, row1.y, row1.z, row1.w,  //
	    row2.x, row2.y, row2.z, row2.w,  //
	    row3.x, row3.y, row3.z, row3.w   //
	};
}

template <typename T>
constexpr matrix4_T<T> matrix4_T<T>::columns(vector4_T<T> column0,
                                             vector4_T<T> column1,
                                             vector4_T<T> column2,
                                             vector4_T<T> column3)
{
	return {
	    column0.x, column1.x, column2.x, column3.x,  //
	    column0.y, column1.y, column2.y, column3.y,  //
	    column0.z, column1.z, column2.z, column3.z,  //
	    column0.w, column1.w, column2.w, column3.w   //
	};
}

template <typename T>
inline matrix4_T<T> matrix4_T<T>::rotation(direction3_T<T> axis,
                                           radian_T<T> angle)
{
	return matrix4_T<T>(matrix3_T<T>::rotation(axis, angle));
}

template <typename T>
inline matrix4_T<T> matrix4_T<T>::rotation(direction3_T<T> axis,
                                           normalized<complex_T<T>> angle)
{
	return matrix4_T<T>(matrix3_T<T>::rotation(axis, angle));
}

template <typename T>
template <std::signed_integral U, U NumeratorT, U DenominatorT>
inline matrix4_T<T> matrix4_T<T>::rotation(
    direction3_T<T> axis,
    static_pi_fraction_T<U, NumeratorT, DenominatorT> angle)
{
	return matrix4_T<T>(matrix3_T<T>::rotation(axis, angle));
}

template <typename T>
inline matrix4_T<T> matrix4_T<T>::rotation(euler_angles_T<T> r)
{
	return matrix4_T<T>(matrix3_T<T>::rotation(r));
}

template <typename T>
inline matrix4_T<T> matrix4_T<T>::rotation(quaternion_T<T> q)
{
	return matrix4_T<T>(matrix3_T<T>::rotation(q));
}

template <typename T>
constexpr matrix4_T<T> matrix4_T<T>::translation(vector3_T<T> t)
{
	return {
	    T(1), T(0), T(0), t.x,  //
	    T(0), T(1), T(0), t.y,  //
	    T(0), T(0), T(1), t.z,  //
	    T(0), T(0), T(0), T(1)  //
	};
}

template <typename T>
constexpr matrix4_T<T> matrix4_T<T>::translation(T x, T y, T z)
{
	return translation({x, y, z});
}

template <typename T>
constexpr matrix4_T<T> matrix4_T<T>::scale(vector3_T<T> s)
{
	return matrix4_T<T>(matrix3_T<T>::scale(s));
}

template <typename T>
constexpr matrix4_T<T> matrix4_T<T>::scale(T x, T y, T z)
{
	return matrix4_T<T>(matrix3_T<T>::scale(x, y, z));
}

template <typename T>
constexpr matrix4_T<T> matrix4_T<T>::scale(T s)
{
	return matrix4_T<T>(matrix3_T<T>::scale(s));
}

template <typename T>
constexpr matrix4_T<T> matrix4_T<T>::look_at(vector3_T<T> from,
                                             vector3_T<T> to,
                                             direction3_T<T> up)
{
	direction3_T<T> forward = (from - to);
	direction3_T<T> right = cross(up, forward);
	direction3_T<T> true_up = cross(forward, right);

	return {right->x, true_up->x, forward->x, from->x,
	        right->y, true_up->y, forward->y, from->y,
	        right->z, true_up->z, forward->z, from->z,
	        T(0),     T(0),       T(0),       T(1)};
}

template <typename T>
constexpr matrix4_T<T> matrix4_T<T>::orthographic(T left,
                                                  T right,
                                                  T top,
                                                  T bottom,
                                                  T near,
                                                  T far)
{
	T a = T(1) / (right - left);
	T b = T(1) / (bottom - top);
	T c = T(1) / (near - far);

	return {
	    T(2) * a, T(0),     T(0), -(right + left) * a,
	    T(0),     T(2) * b, T(0), -(bottom + top) * b,
	    T(0),     T(0),     c,    near * c,
	    T(0),     T(0),     T(0), T(1),
	};
}

template <typename T>
inline matrix4_T<T> matrix4_T<T>::rotation_around_x(radian_T<T> angle)
{
	return matrix4_T<T>(matrix3_T<T>::rotation_around_x(angle));
}

template <typename T>
inline matrix4_T<T> matrix4_T<T>::rotation_around_y(radian_T<T> angle)
{
	return matrix4_T<T>(matrix3_T<T>::rotation_around_y(angle));
}

template <typename T>
inline matrix4_T<T> matrix4_T<T>::rotation_around_z(radian_T<T> angle)
{
	return matrix4_T<T>(matrix3_T<T>::rotation_around_z(angle));
}

template <typename T>
inline matrix4_T<T> matrix4_T<T>::rotation_around_x(
    normalized<complex_T<T>> angle)
{
	return matrix4_T<T>(matrix3_T<T>::rotation_around_x(angle));
}

template <typename T>
inline matrix4_T<T> matrix4_T<T>::rotation_around_y(
    normalized<complex_T<T>> angle)
{
	return matrix4_T<T>(matrix3_T<T>::rotation_around_y(angle));
}

template <typename T>
inline matrix4_T<T> matrix4_T<T>::rotation_around_z(
    normalized<complex_T<T>> angle)
{
	return matrix4_T<T>(matrix3_T<T>::rotation_around_z(angle));
}

template <typename T>
template <std::signed_integral U, U NumeratorT, U DenominatorT>
inline matrix4_T<T> matrix4_T<T>::rotation_around_x(
    static_pi_fraction_T<U, NumeratorT, DenominatorT> angle)
{
	return matrix4_T<T>(matrix3_T<T>::rotation_around_x(angle));
}

template <typename T>
template <std::signed_integral U, U NumeratorT, U DenominatorT>
inline matrix4_T<T> matrix4_T<T>::rotation_around_y(
    static_pi_fraction_T<U, NumeratorT, DenominatorT> angle)
{
	return matrix4_T<T>(matrix3_T<T>::rotation_around_y(angle));
}

template <typename T>
template <std::signed_integral U, U NumeratorT, U DenominatorT>
inline matrix4_T<T> matrix4_T<T>::rotation_around_z(
    static_pi_fraction_T<U, NumeratorT, DenominatorT> angle)
{
	return matrix4_T<T>(matrix3_T<T>::rotation_around_z(angle));
}

template <typename T>
constexpr bool matrix4_T<T>::is_orthogonal() const
{
	return nearly_equal(m00 * m01 + m10 * m11 + m20 * m21 + m30 * m31, T(0)) &&
	       nearly_equal(m00 * m02 + m10 * m12 + m20 * m22 + m30 * m32, T(0)) &&
	       nearly_equal(m00 * m03 + m10 * m13 + m20 * m23 + m30 * m33, T(0)) &&
	       nearly_equal(m01 * m02 + m11 * m12 + m21 * m22 + m31 * m32, T(0)) &&
	       nearly_equal(m01 * m03 + m11 * m13 + m21 * m23 + m31 * m33, T(0)) &&
	       nearly_equal(m02 * m03 + m12 * m13 + m22 * m23 + m32 * m33, T(0)) &&
	       nearly_equal(m00 * m00 + m10 * m10 + m20 * m20 + m30 * m30, T(1)) &&
	       nearly_equal(m01 * m01 + m11 * m11 + m21 * m21 + m31 * m31, T(1)) &&
	       nearly_equal(m02 * m02 + m12 * m12 + m22 * m22 + m32 * m32, T(1)) &&
	       nearly_equal(m03 * m03 + m13 * m13 + m23 * m23 + m33 * m33, T(1));
}

template <typename T>
constexpr bool matrix4_T<T>::is_homogenous() const
{
	return nearly_equal(m03, T(0)) &&  //
	       nearly_equal(m13, T(0)) &&  //
	       nearly_equal(m23, T(0)) &&  //
	       nearly_equal(m30, T(0)) &&  //
	       nearly_equal(m31, T(0)) &&  //
	       nearly_equal(m32, T(0)) &&  //
	       nearly_equal(m33, T(1));
}

template <typename T>
constexpr T matrix4_T<T>::determinant() const
{
	if (is_homogenous())
	{
		return m00 * m11 * m22 + m01 * m12 * m20 + m02 * m10 * m21 -
		       m20 * m11 * m02 - m21 * m12 * m00 - m22 * m10 * m01;
	}

	T det1 = m11 * (m22 * m33 - m32 * m23) -  //
	         m21 * (m12 * m33 - m32 * m13) +  //
	         m31 * (m12 * m23 - m22 * m13);   //
	T det2 = m01 * (m22 * m33 - m32 * m23) -  //
	         m21 * (m02 * m33 - m32 * m03) +  //
	         m31 * (m02 * m23 - m22 * m03);   //
	T det3 = m01 * (m12 * m33 - m32 * m13) -  //
	         m11 * (m02 * m33 - m32 * m03) +  //
	         m31 * (m02 * m13 - m12 * m03);   //
	T det4 = m01 * (m12 * m23 - m22 * m13) -  //
	         m11 * (m02 * m23 - m22 * m03) +  //
	         m21 * (m02 * m13 - m12 * m03);   //

	return m00 * det1 - m10 * det2 + m20 * det3 - m30 * det4;
}

template <typename T>
inline matrix3_T<T> matrix4_T<T>::extract_rotation_matrix() const
{
	const T sx = norm(column(0).xyz());
	const T sy = norm(column(1).xyz());
	const T sz = norm(column(2).xyz());

	return matrix3_T<T>::rows(vector3_T<T>(row(0).column(0) / sx,    //
	                                       row(0).column(1) / sy,    //
	                                       row(0).column(2) / sz),   //
	                          vector3_T<T>(row(1).column(0) / sx,    //
	                                       row(1).column(1) / sy,    //
	                                       row(1).column(2) / sz),   //
	                          vector3_T<T>(row(2).column(0) / sx,    //
	                                       row(2).column(1) / sy,    //
	                                       row(2).column(2) / sz));  //
}

template <typename T>
constexpr vector3_T<T> matrix4_T<T>::transform_position(vector3_T<T> pos) const
{
	return (*this * vector4_T<T>(pos, T(1))).xyz();
}

template <typename T>
constexpr vector3_T<T> matrix4_T<T>::transform_direction(
    vector3_T<T> dir) const
{
	return (*this * vector4_T<T>(dir, T(0))).xyz();
}

template <typename T>
constexpr direction3_T<T> matrix4_T<T>::transform_direction(
    direction3_T<T> dir) const
{
	return direction3_T<T>((*this * vector4_T<T>(*dir, T(0))).xyz());
}

template <typename T>
constexpr vector3_T<T> matrix4_T<T>::transform_position_perspective(
    vector3_T<T> pos) const
{
	const vector4_T<T> tmp = *this * vector4_T<T>(pos, T(1));
	return {
	    tmp.x / tmp.w,
	    tmp.y / tmp.w,
	    tmp.z / tmp.w,
	};
}

template <typename T>
constexpr point3_T<T> matrix4_T<T>::transform(const point3_T<T>& point) const
{
	return (*this * vector4_T<T>(point, T(1))).xyz();
}

template <typename T>
constexpr direction3_T<T> matrix4_T<T>::transform(
    const direction3_T<T>& dir) const
{
	return (*this * vector4_T<T>(dir, T(0))).xyz();
}

template <typename T>
constexpr vector4_column_proxy<T> matrix4_T<T>::column(int i)
{
	return std::array{
	    vector4_column_proxy<T>{m00, m01, m02, m03},
	    vector4_column_proxy<T>{m10, m11, m12, m13},
	    vector4_column_proxy<T>{m20, m21, m22, m23},
	    vector4_column_proxy<T>{m30, m31, m32, m33},
	}[i];
}

template <typename T>
constexpr vector4_column_proxy<const T> matrix4_T<T>::column(int i) const
{
	return std::array{
	    vector4_column_proxy<const T>{m00, m01, m02, m03},
	    vector4_column_proxy<const T>{m10, m11, m12, m13},
	    vector4_column_proxy<const T>{m20, m21, m22, m23},
	    vector4_column_proxy<const T>{m30, m31, m32, m33},
	}[i];
}

template <typename T>
constexpr vector4_row_proxy<T> matrix4_T<T>::row(int i)
{
	return std::array{
	    vector4_row_proxy<T>{m00, m10, m20, m30},
	    vector4_row_proxy<T>{m01, m11, m21, m31},
	    vector4_row_proxy<T>{m02, m12, m22, m32},
	    vector4_row_proxy<T>{m03, m13, m23, m33},
	}[i];
}

template <typename T>
constexpr vector4_row_proxy<const T> matrix4_T<T>::row(int i) const
{
	return std::array{
	    vector4_row_proxy<const T>{m00, m10, m20, m30},
	    vector4_row_proxy<const T>{m01, m11, m21, m31},
	    vector4_row_proxy<const T>{m02, m12, m22, m32},
	    vector4_row_proxy<const T>{m03, m13, m23, m33},
	}[i];
}

template <typename T>
constexpr vector4_diag_proxy<T> matrix4_T<T>::diag()
{
	return vector4_diag_proxy<T>{m00, m11, m22, m33};
}

template <typename T>
constexpr vector4_diag_proxy<const T> matrix4_T<T>::diag() const
{
	return vector4_diag_proxy<const T>{m00, m11, m22, m33};
}

template <typename T>
constexpr matrix4_T<T> matrix4_T<T>::operator*(T f) const
{
	return {
	    m00 * f, m10 * f, m20 * f, m30 * f,  //
	    m00 * f, m10 * f, m20 * f, m30 * f,  //
	    m00 * f, m10 * f, m20 * f, m30 * f,  //
	    m00 * f, m10 * f, m20 * f, m30 * f   //
	};
}

template <typename T>
constexpr matrix4_T<T> matrix4_T<T>::operator/(T f) const
{
	return {
	    m00 / f, m10 / f, m20 / f, m30 / f,  //
	    m00 / f, m10 / f, m20 / f, m30 / f,  //
	    m00 / f, m10 / f, m20 / f, m30 / f,  //
	    m00 / f, m10 / f, m20 / f, m30 / f   //
	};
}

template <typename T>
constexpr vector4_T<T> matrix4_T<T>::operator*(vector4_T<T> v) const
{
	return {
	    m00 * v.x + m10 * v.y + m20 * v.z + m30 * v.w,  //
	    m01 * v.x + m11 * v.y + m21 * v.z + m31 * v.w,  //
	    m02 * v.x + m12 * v.y + m22 * v.z + m32 * v.w,  //
	    m03 * v.x + m13 * v.y + m23 * v.z + m33 * v.w   //
	};
}

template <typename T>
constexpr matrix4_T<T> matrix4_T<T>::operator*(const matrix4_T<T>& m) const
{
	return {m.m00 * m00 + m.m01 * m10 + m.m02 * m20 + m.m03 * m30,
	        m.m10 * m00 + m.m11 * m10 + m.m12 * m20 + m.m13 * m30,
	        m.m20 * m00 + m.m21 * m10 + m.m22 * m20 + m.m23 * m30,
	        m.m30 * m00 + m.m31 * m10 + m.m32 * m20 + m.m33 * m30,

	        m.m00 * m01 + m.m01 * m11 + m.m02 * m21 + m.m03 * m31,
	        m.m10 * m01 + m.m11 * m11 + m.m12 * m21 + m.m13 * m31,
	        m.m20 * m01 + m.m21 * m11 + m.m22 * m21 + m.m23 * m31,
	        m.m30 * m01 + m.m31 * m11 + m.m32 * m21 + m.m33 * m31,

	        m.m00 * m02 + m.m01 * m12 + m.m02 * m22 + m.m03 * m32,
	        m.m10 * m02 + m.m11 * m12 + m.m12 * m22 + m.m13 * m32,
	        m.m20 * m02 + m.m21 * m12 + m.m22 * m22 + m.m23 * m32,
	        m.m30 * m02 + m.m31 * m12 + m.m32 * m22 + m.m33 * m32,

	        m.m00 * m03 + m.m01 * m13 + m.m02 * m23 + m.m03 * m33,
	        m.m10 * m03 + m.m11 * m13 + m.m12 * m23 + m.m13 * m33,
	        m.m20 * m03 + m.m21 * m13 + m.m22 * m23 + m.m23 * m33,
	        m.m30 * m03 + m.m31 * m13 + m.m32 * m23 + m.m33 * m33};
}

template <typename T>
constexpr bool matrix4_T<T>::operator==(const matrix4_T<T>& m) const
{
	return m00 == m.m00 &&  //
	       m01 == m.m01 &&  //
	       m02 == m.m02 &&  //
	       m03 == m.m03 &&  //
	       m10 == m.m10 &&  //
	       m11 == m.m11 &&  //
	       m12 == m.m12 &&  //
	       m13 == m.m13 &&  //
	       m20 == m.m20 &&  //
	       m21 == m.m21 &&  //
	       m22 == m.m22 &&  //
	       m23 == m.m23 &&  //
	       m30 == m.m30 &&  //
	       m31 == m.m31 &&  //
	       m32 == m.m32 &&  //
	       m33 == m.m33;
}

template <typename T>
constexpr matrix4_T<T>& matrix4_T<T>::inverse()
{
	if (is_orthogonal())
	{
		return transpose();
	}

	T det = determinant();
	assert(std::abs(det) > std::numeric_limits<T>::epsilon());

	T recM00 = m00;
	T recM10 = m10;
	T recM20 = m20;
	T recM01 = m01;
	T recM11 = m11;
	T recM02 = m02;

	if (is_homogenous())
	{
		m00 = (recM11 * m22 - m21 * m12) / det;
		m10 = (m12 * recM20 - recM10 * m22) / det;
		m20 = (recM10 * m21 - recM20 * recM11) / det;
		m01 = (recM02 * m21 - recM01 * m22) / det;
		m11 = (recM00 * m22 - recM20 * recM02) / det;
		m21 = (recM01 * recM20 - recM00 * m21) / det;
		m02 = (recM01 * m12 - recM11 * recM02) / det;
		m12 = (recM02 * recM10 - recM00 * m12) / det;
		m22 = (recM00 * recM11 - recM10 * recM01) / det;
		return *this;
	}

	T recM30 = m30;
	T recM21 = m21;
	T recM31 = m31;
	T recM12 = m12;
	T recM22 = m22;
	T recM03 = m03;
	T recM13 = m13;

	m00 = (recM11 * recM22 * m33 - recM11 * m23 * m32 - recM21 * recM12 * m33 +
	       recM21 * recM13 * m32 + recM31 * recM12 * m23 -
	       recM31 * recM13 * recM22) /
	      det;

	m10 = (-recM10 * recM22 * m33 + recM10 * m23 * m32 +
	       recM20 * recM12 * m33 - recM20 * recM13 * m32 -
	       recM30 * recM12 * m23 + recM30 * recM13 * recM22) /
	      det;

	m20 = (recM10 * recM21 * m33 - recM10 * m23 * recM31 -
	       recM20 * recM11 * m33 + recM20 * recM13 * recM31 +
	       recM30 * recM11 * m23 - recM30 * recM13 * recM21) /
	      det;

	m30 = (-recM10 * recM21 * m32 + recM10 * recM22 * recM31 +
	       recM20 * recM11 * m32 - recM20 * recM12 * recM31 -
	       recM30 * recM11 * recM22 + recM30 * recM12 * recM21) /
	      det;

	m01 = (-recM01 * recM22 * m33 + recM01 * m23 * m32 +
	       recM21 * recM02 * m33 - recM21 * recM03 * m32 -
	       recM31 * recM02 * m23 + recM31 * recM03 * recM22) /
	      det;

	m11 = (recM00 * recM22 * m33 - recM00 * m23 * m32 - recM20 * recM02 * m33 +
	       recM20 * recM03 * m32 + recM30 * recM02 * m23 -
	       recM30 * recM03 * recM22) /
	      det;

	m21 = (-recM00 * recM21 * m33 + recM00 * m23 * recM31 +
	       recM20 * recM01 * m33 - recM20 * recM03 * recM31 -
	       recM30 * recM01 * m23 + recM30 * recM03 * recM21) /
	      det;

	m31 = (recM00 * recM21 * m32 - recM00 * recM22 * recM31 -
	       recM20 * recM01 * m32 + recM20 * recM02 * recM31 +
	       recM30 * recM01 * recM22 - recM30 * recM02 * recM21) /
	      det;

	m02 = (recM01 * recM12 * m33 - recM01 * recM13 * m32 -
	       recM11 * recM02 * m33 + recM11 * recM03 * m32 +
	       recM31 * recM02 * recM13 - recM31 * recM03 * recM12) /
	      det;

	m12 = (-recM00 * recM12 * m33 + recM00 * recM13 * m32 +
	       recM10 * recM02 * m33 - recM10 * recM03 * m32 -
	       recM30 * recM02 * recM13 + recM30 * recM03 * recM12) /
	      det;

	m22 = (recM00 * recM11 * m33 - recM00 * recM13 * recM31 -
	       recM10 * recM01 * m33 + recM10 * recM03 * recM31 +
	       recM30 * recM01 * recM13 - recM30 * recM03 * recM11) /
	      det;

	m32 = (-recM00 * recM11 * m32 + recM00 * recM12 * recM31 +
	       recM10 * recM01 * m32 - recM10 * recM02 * recM31 -
	       recM30 * recM01 * recM12 + recM30 * recM02 * recM11) /
	      det;

	m03 = (-recM01 * recM12 * m23 + recM01 * recM13 * recM22 +
	       recM11 * recM02 * m23 - recM11 * recM03 * recM22 -
	       recM21 * recM02 * recM13 + recM21 * recM03 * recM12) /
	      det;

	m13 = (recM00 * recM12 * m23 - recM00 * recM13 * recM22 -
	       recM10 * recM02 * m23 + recM10 * recM03 * recM22 +
	       recM20 * recM02 * recM13 - recM20 * recM03 * recM12) /
	      det;

	m23 = (-recM00 * recM11 * m23 + recM00 * recM13 * recM21 +
	       recM10 * recM01 * m23 - recM10 * recM03 * recM21 -
	       recM20 * recM01 * recM13 + recM20 * recM03 * recM11) /
	      det;

	m33 = (recM00 * recM11 * recM22 - recM00 * recM12 * recM21 -
	       recM10 * recM01 * recM22 + recM10 * recM02 * recM21 +
	       recM20 * recM01 * recM12 - recM20 * recM02 * recM11) /
	      det;

	return *this;
}

template <typename T>
constexpr matrix4_T<T> matrix4_T<T>::get_inversed() const
{
	matrix4_T<T> m{*this};
	m.inverse();
	return m;
}

template <typename T>
constexpr matrix4_T<T>& matrix4_T<T>::transpose()
{
	std::swap(m01, m10);
	std::swap(m02, m20);
	std::swap(m03, m30);
	std::swap(m12, m21);
	std::swap(m13, m31);
	std::swap(m23, m32);
	return *this;
}

template <typename T>
constexpr matrix4_T<T> matrix4_T<T>::get_transposed() const
{
	matrix4_T<T> m{*this};
	m.transpose();
	return m;
}

template <typename T>
constexpr matrix4_T<T> operator*(const transform3_T<T>& t,
                                 const matrix4_T<T>& m)
{
	return t.to_matrix4() * m;
}

template <typename T>
constexpr matrix4_T<T> operator*(const matrix4_T<T>& m,
                                 const transform3_T<T>& t)
{
	return m * t.to_matrix4();
}

template <typename T>
constexpr matrix4_T<T> operator*(const uniform_transform3_T<T>& t,
                                 const matrix4_T<T>& m)
{
	return t.to_matrix4() * m;
}

template <typename T>
constexpr matrix4_T<T> operator*(const matrix4_T<T>& m,
                                 const uniform_transform3_T<T>& t)
{
	return m * t.to_matrix4();
}

template <typename T>
constexpr matrix4_T<T> operator*(const unscaled_transform3_T<T>& t,
                                 const matrix4_T<T>& m)
{
	return t.to_matrix4() * m;
}

template <typename T>
constexpr matrix4_T<T> operator*(const matrix4_T<T>& m,
                                 const unscaled_transform3_T<T>& t)
{
	return m * t.to_matrix4();
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const cdm::matrix4_T<T>& m)
{
	const auto flags = os.flags();
	const auto w = std::setw(13);
	os << std::right;
	// clang-format off
	os << "matrix4_T(" << w << m.column(0).row(0) << " " << w << m.column(1).row(0) << " " << w << m.column(2).row(0) << " " << w << m.column(3).row(0) << "\n"
	      "          " << w << m.column(0).row(1) << " " << w << m.column(1).row(1) << " " << w << m.column(2).row(1) << " " << w << m.column(3).row(1) << "\n"
	      "          " << w << m.column(0).row(2) << " " << w << m.column(1).row(2) << " " << w << m.column(2).row(2) << " " << w << m.column(3).row(2) << "\n"
	      "          " << w << m.column(0).row(3) << " " << w << m.column(1).row(3) << " " << w << m.column(2).row(3) << " " << w << m.column(3).row(3) << ")";
	// clang-format on
	os.setf(flags);
	return os;
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_MATRIX4_HPP
