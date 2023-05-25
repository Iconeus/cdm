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

#ifndef CDM_MATHS_IMPL_MATRIX3_HPP
#define CDM_MATHS_IMPL_MATRIX3_HPP 1

#include <cdm/decl/maths/complex.hpp>
#include <cdm/decl/maths/matrix2.hpp>
#include <cdm/decl/maths/matrix3.hpp>
#include <cdm/decl/maths/radian.hpp>
#include <cdm/decl/maths/vector3.hpp>
#include <cdm/decl/maths/vector_proxy.hpp>

#include <ostream>

namespace cdm
{
template <typename T>
constexpr matrix3_T<T>::matrix3_T(T e00,
                                  T e10,
                                  T e20,
                                  T e01,
                                  T e11,
                                  T e21,
                                  T e02,
                                  T e12,
                                  T e22)
    : m00{e00},
      m10{e10},
      m20{e20},
      m01{e01},
      m11{e11},
      m21{e21},
      m02{e02},
      m12{e12},
      m22{e22}
{
}

template <typename T>
constexpr matrix3_T<T>::matrix3_T(matrix2_T<T> m)
    : matrix3_T(m.m00, m.m10, T(0), m.m10, m.m11, T(0), T(0), T(0), T(1))
{
}

template <typename T>
constexpr matrix3_T<T>::matrix3_T(const std::array<T, 9>& a)
    : matrix3_T(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8])
{
}

template <typename T>
template <typename U>
constexpr matrix3_T<T>::operator matrix3_T<U>() const
{
	return {
	    U(m00), U(m10), U(m20),  //
	    U(m01), U(m11), U(m21),  //
	    U(m02), U(m12), U(m22),  //
	};
}

template <typename T>
constexpr matrix3_T<T>::operator std::array<T, 9>() const
{
	return {
	    m00, m10, m20,  //
	    m01, m11, m21,  //
	    m02, m12, m22,  //
	};
}

template <typename T>
template <typename U>
constexpr std::array<U, 9> matrix3_T<T>::to_array() const
{
	return {static_cast<U>(m00), static_cast<U>(m10), static_cast<U>(m20),
	        static_cast<U>(m01), static_cast<U>(m11), static_cast<U>(m21),
	        static_cast<U>(m02), static_cast<U>(m12), static_cast<U>(m22)};
}

template <typename T>
constexpr matrix3_T<T> matrix3_T<T>::zero()
{
	return {T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0)};
}

template <typename T>
constexpr matrix3_T<T> matrix3_T<T>::identity()
{
	return {
	    T(1), T(0), T(0),  //
	    T(0), T(1), T(0),  //
	    T(0), T(0), T(1),  //
	};
}

template <typename T>
constexpr matrix3_T<T> matrix3_T<T>::rows(vector3_T<T> row0,
                                          vector3_T<T> row1,
                                          vector3_T<T> row2)
{
	return {
	    row0.x, row0.y, row0.z,  //
	    row1.x, row1.y, row1.z,  //
	    row2.x, row2.y, row2.z,  //
	};
}

template <typename T>
constexpr matrix3_T<T> matrix3_T<T>::columns(vector3_T<T> column0,
                                             vector3_T<T> column1,
                                             vector3_T<T> column2)
{
	return {
	    column0.x, column1.x, column2.x,  //
	    column0.y, column1.y, column2.y,  //
	    column0.z, column1.z, column2.z,  //
	};
}

template <typename T>
inline matrix3_T<T> matrix3_T<T>::rotation(direction3_T<T> axis,
                                           T sinAngle,
                                           T cosAngle)
{
	const T l = axis.x();
	const T m = axis.y();
	const T n = axis.z();
	const T s = sinAngle;
	const T c = cosAngle;
	const T d = T(1) - cosAngle;
	const T ls = l * s;
	const T ms = m * s;
	const T ns = n * s;
	const T ld = l * d;
	const T md = m * d;
	const T nd = n * d;
	return {
	    (l * ld) + c,  (m * ld) - ns, (n * ld) + ms,  //
	    (l * md) + ns, (m * md) + c,  (n * md) - ls,  //
	    (l * nd) - ms, (m * nd) + ls, (n * nd) + c,   //
	};
}

template <typename T>
matrix3_T<T> matrix3_T<T>::rotation(direction3_T<T> axis, radian_T<T> angle)
{
	return matrix3_T<T>::rotation(axis, sin(angle), cos(angle));
}

template <typename T>
matrix3_T<T> matrix3_T<T>::rotation(direction3_T<T> axis,
                                    normalized<complex_T<T>> angle)
{
	return matrix3_T<T>::rotation(axis, sin(angle), cos(angle));
}

template <typename T>
template <std::signed_integral U, U NumeratorT, U DenominatorT>
matrix3_T<T> matrix3_T<T>::rotation(
    direction3_T<T> axis,
    static_pi_fraction_T<U, NumeratorT, DenominatorT> angle)
{
	return matrix3_T<T>::rotation(axis, sin<T>(angle), cos<T>(angle));
}

template <typename T>
matrix3_T<T> matrix3_T<T>::rotation(euler_angles_T<T> r)
{
	matrix3_T<T> RX = matrix3_T<T>::identity();
	RX.m11 = cos(-r.x);
	RX.m12 = -sin(-r.x);
	RX.m21 = sin(-r.x);
	RX.m22 = cos(-r.x);

	matrix3_T<T> RY = matrix3_T<T>::identity();
	RY.m00 = cos(-r.y);
	RY.m02 = sin(-r.y);
	RY.m20 = -sin(-r.y);
	RY.m22 = cos(-r.y);

	matrix3_T<T> RZ = matrix3_T<T>::identity();
	RZ.m00 = cos(-r.z);
	RZ.m01 = -sin(-r.z);
	RZ.m10 = sin(-r.z);
	RZ.m11 = cos(-r.z);

	return RY * RX * RZ;
}

template <typename T>
matrix3_T<T> matrix3_T<T>::rotation(quaternion_T<T> q)
{
	return {
	    detail::get_quaternion_T_matrix_element<0, 0>(q),
	    detail::get_quaternion_T_matrix_element<1, 0>(q),
	    detail::get_quaternion_T_matrix_element<2, 0>(q),
	    detail::get_quaternion_T_matrix_element<0, 1>(q),
	    detail::get_quaternion_T_matrix_element<1, 1>(q),
	    detail::get_quaternion_T_matrix_element<2, 1>(q),
	    detail::get_quaternion_T_matrix_element<0, 2>(q),
	    detail::get_quaternion_T_matrix_element<1, 2>(q),
	    detail::get_quaternion_T_matrix_element<2, 2>(q),
	};
}

template <typename T>
matrix3_T<T> matrix3_T<T>::rotation_around_x(T sinAngle, T cosAngle)
{
	return {
	    T(1), T(0),     T(0),       //
	    T(0), cosAngle, -sinAngle,  //
	    T(0), sinAngle, cosAngle    //
	};
}

template <typename T>
matrix3_T<T> matrix3_T<T>::rotation_around_y(T sinAngle, T cosAngle)
{
	return {
	    cosAngle,  T(0), sinAngle,  //
	    T(0),      T(1), T(0),      //
	    -sinAngle, T(0), cosAngle   //
	};
}

template <typename T>
matrix3_T<T> matrix3_T<T>::rotation_around_z(T sinAngle, T cosAngle)
{
	return {
	    cosAngle, -sinAngle, T(0),  //
	    sinAngle, cosAngle,  T(0),  //
	    T(0),     T(0),      T(1)   //
	};
}

template <typename T>
matrix3_T<T> matrix3_T<T>::rotation_around_x(radian_T<T> angle)
{
	return rotation_around_x(sin(angle), cos(angle));
}

template <typename T>
matrix3_T<T> matrix3_T<T>::rotation_around_y(radian_T<T> angle)
{
	return rotation_around_y(sin(angle), cos(angle));
}

template <typename T>
matrix3_T<T> matrix3_T<T>::rotation_around_z(radian_T<T> angle)
{
	return rotation_around_z(sin(angle), cos(angle));
}

template <typename T>
matrix3_T<T> matrix3_T<T>::rotation_around_x(normalized<complex_T<T>> angle)
{
	return rotation_around_x(angle->i, angle->r);
}

template <typename T>
matrix3_T<T> matrix3_T<T>::rotation_around_y(normalized<complex_T<T>> angle)
{
	return rotation_around_y(angle->i, angle->r);
}

template <typename T>
matrix3_T<T> matrix3_T<T>::rotation_around_z(normalized<complex_T<T>> angle)
{
	return rotation_around_z(angle->i, angle->r);
}

template <typename T>
template <std::signed_integral U, U NumeratorT, U DenominatorT>
matrix3_T<T> matrix3_T<T>::rotation_around_x(
    static_pi_fraction_T<U, NumeratorT, DenominatorT> angle)
{
	return rotation_around_x(sin<T>(angle), cos<T>(angle));
}

template <typename T>
template <std::signed_integral U, U NumeratorT, U DenominatorT>
matrix3_T<T> matrix3_T<T>::rotation_around_y(
    static_pi_fraction_T<U, NumeratorT, DenominatorT> angle)
{
	return rotation_around_y(sin<T>(angle), cos<T>(angle));
}

template <typename T>
template <std::signed_integral U, U NumeratorT, U DenominatorT>
matrix3_T<T> matrix3_T<T>::rotation_around_z(
    static_pi_fraction_T<U, NumeratorT, DenominatorT> angle)
{
	return rotation_around_z(sin<T>(angle), cos<T>(angle));
}

template <typename T>
constexpr matrix3_T<T> matrix3_T<T>::scale(vector3_T<T> s)
{
	return scale(s.x, s.y, s.z);
}

template <typename T>
constexpr matrix3_T<T> matrix3_T<T>::scale(T x, T y, T z)
{
	return {
	    x,    T(0), T(0),  //
	    T(0), y,    T(0),  //
	    T(0), T(0), z,     //
	};
}

template <typename T>
constexpr matrix3_T<T> matrix3_T<T>::scale(T s)
{
	return scale(s, s, s);
}

template <typename T>
constexpr matrix3_T<T>& matrix3_T<T>::inverse()
{
	if (is_orthogonal())
	{
		return transpose();
	}

	T det = determinant();
	assert(std::abs(det) > std::numeric_limits<T>::epsilon());

	T invDet = T(1) / det;
	T recM00 = m00;
	T recM10 = m10;
	T recM20 = m20;
	T recM01 = m01;
	T recM11 = m11;
	T recM02 = m02;

	m00 = (recM11 * m22 - m21 * m12) * invDet;
	m10 = (m12 * recM20 - recM10 * m22) * invDet;
	m20 = (recM10 * m12 - recM20 * recM11) * invDet;
	m01 = (recM02 * m21 - recM01 * m22) * invDet;
	m11 = (recM00 * m22 - recM20 * recM02) * invDet;
	m21 = (recM01 * recM20 - recM00 * m21) * invDet;
	m02 = (recM01 * m12 - recM11 * recM02) * invDet;
	m12 = (recM02 * recM10 - recM00 * m12) * invDet;
	m22 = (recM00 * recM11 - recM10 * recM01) * invDet;

	return *this;
}

template <typename T>
constexpr matrix3_T<T> matrix3_T<T>::get_inversed() const
{
	matrix3_T<T> res = *this;
	res.inverse();
	return res;
}

template <typename T>
constexpr matrix3_T<T>& matrix3_T<T>::transpose()
{
	std::swap(m01, m10);
	std::swap(m02, m20);
	std::swap(m12, m21);
	return *this;
}

template <typename T>
constexpr matrix3_T<T> matrix3_T<T>::get_transposed() const
{
	return {
	    m00, m01, m02,  //
	    m10, m11, m12,  //
	    m20, m21, m22   //
	};
}

template <typename T>
constexpr T matrix3_T<T>::determinant() const
{
	return m00 * m11 * m22 +  //
	       m01 * m12 * m20 +  //
	       m02 * m10 * m21 -  //
	       m20 * m11 * m02 -  //
	       m21 * m12 * m00 -  //
	       m22 * m10 * m01;
}

template <typename T>
constexpr bool matrix3_T<T>::is_orthogonal() const
{
	return nearly_equal(m00 * m01 + m10 * m11 + m20 * m21, T(0)) &&
	       nearly_equal(m00 * m02 + m10 * m12 + m20 * m22, T(0)) &&
	       nearly_equal(m01 * m02 + m11 * m12 + m21 * m22, T(0)) &&
	       nearly_equal(m00 * m00 + m10 * m10 + m20 * m20, T(1)) &&
	       nearly_equal(m01 * m01 + m11 * m11 + m21 * m21, T(1)) &&
	       nearly_equal(m02 * m02 + m12 * m12 + m22 * m22, T(1));
}

template <typename T>
constexpr vector3_column_proxy<T> matrix3_T<T>::column(int i)
{
	return std::array{
	    vector3_column_proxy<T>{m00, m01, m02},
	    vector3_column_proxy<T>{m10, m11, m12},
	    vector3_column_proxy<T>{m20, m21, m22},
	}[i];
}

template <typename T>
constexpr vector3_column_proxy<const T> matrix3_T<T>::column(int i) const
{
	return std::array{
	    vector3_column_proxy<const T>{m00, m01, m02},
	    vector3_column_proxy<const T>{m10, m11, m12},
	    vector3_column_proxy<const T>{m20, m21, m22},
	}[i];
}

template <typename T>
constexpr vector3_row_proxy<T> matrix3_T<T>::row(int i)
{
	return std::array{
	    vector3_row_proxy<T>{m00, m10, m20},
	    vector3_row_proxy<T>{m01, m11, m21},
	    vector3_row_proxy<T>{m02, m12, m22},
	}[i];
}

template <typename T>
constexpr vector3_row_proxy<const T> matrix3_T<T>::row(int i) const
{
	return std::array{
	    vector3_row_proxy<const T>{m00, m10, m20},
	    vector3_row_proxy<const T>{m01, m11, m21},
	    vector3_row_proxy<const T>{m02, m12, m22},
	}[i];
}

template <typename T>
constexpr vector3_diag_proxy<T> matrix3_T<T>::diag()
{
	return vector3_diag_proxy<T>{m00, m11, m22};
}

template <typename T>
constexpr vector3_diag_proxy<const T> matrix3_T<T>::diag() const
{
	return vector3_diag_proxy<const T>{m00, m11, m22};
}

template <typename T>
constexpr matrix3_T<T> matrix3_T<T>::operator*(T f) const
{
	return {
	    m00 * f, m10 * f, m20 * f,  //
	    m01 * f, m11 * f, m21 * f,  //
	    m02 * f, m12 * f, m22 * f   //
	};
}

template <typename T>
constexpr vector3_T<T> matrix3_T<T>::operator*(vector3_T<T> v) const
{
	return {
	    m00 * v.x + m10 * v.y + m20 * v.z,
	    m01 * v.x + m11 * v.y + m21 * v.z,
	    m02 * v.x + m12 * v.y + m22 * v.z,
	};
}

template <typename T>
constexpr matrix3_T<T> matrix3_T<T>::operator*(const matrix3_T<T>& m) const
{
	return {m00 * m.m00 + m10 * m.m01 + m20 * m.m02,
	        m00 * m.m10 + m10 * m.m11 + m20 * m.m12,
	        m00 * m.m20 + m10 * m.m21 + m20 * m.m22,

	        m01 * m.m00 + m11 * m.m01 + m21 * m.m02,
	        m01 * m.m10 + m11 * m.m11 + m21 * m.m12,
	        m01 * m.m20 + m11 * m.m21 + m21 * m.m22,

	        m02 * m.m00 + m12 * m.m01 + m22 * m.m02,
	        m02 * m.m10 + m12 * m.m11 + m22 * m.m12,
	        m02 * m.m20 + m12 * m.m21 + m22 * m.m22};
}

template <typename T>
constexpr bool matrix3_T<T>::operator==(const matrix3_T<T>& m) const
{
	return m00 == m.m00 &&  //
	       m01 == m.m01 &&  //
	       m02 == m.m02 &&  //
	       m10 == m.m10 &&  //
	       m11 == m.m11 &&  //
	       m12 == m.m12 &&  //
	       m20 == m.m20 &&  //
	       m21 == m.m21 &&  //
	       m22 == m.m22;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const cdm::matrix3_T<T>& m)
{
	const auto flags = os.flags();
	const auto w = std::setw(13);
	os << std::right;
	// clang-format off
	os << "matrix3_T(" << w << m.column(0).row(0) << " " << w << m.column(1).row(0) << " " << w << m.column(2).row(0) << "\n"
	      "          " << w << m.column(0).row(1) << " " << w << m.column(1).row(1) << " " << w << m.column(2).row(1) << "\n"
	      "          " << w << m.column(0).row(2) << " " << w << m.column(1).row(2) << " " << w << m.column(2).row(2) << ")";
	// clang-format on
	os.setf(flags);
	return os;
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_MATRIX3_HPP
