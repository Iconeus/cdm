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

#ifndef CDM_MATHS_IMPL_MATRIX2_HPP
#define CDM_MATHS_IMPL_MATRIX2_HPP 1

#include <cdm/decl/maths/complex.hpp>
#include <cdm/decl/maths/matrix2.hpp>
#include <cdm/decl/maths/radian.hpp>
#include <cdm/decl/maths/vector2.hpp>
#include <cdm/decl/maths/vector_proxy.hpp>

#include <ostream>

namespace cdm
{
template <typename T>
constexpr matrix2_T<T>::matrix2_T(T e00, T e10, T e01, T e11)
    : m00{e00}, m10{e10}, m01{e01}, m11{e11}
{
}

template <typename T>
constexpr matrix2_T<T>::matrix2_T(const std::array<T, 4>& a)
    : matrix2_T(a[0], a[1], a[2], a[3])
{
}

template <typename T>
template <typename U>
constexpr std::array<U, 4> matrix2_T<T>::to_array() const
{
	return {static_cast<U>(m00), static_cast<U>(m10), static_cast<U>(m01),
	        static_cast<U>(m11)};
}

template <typename T>
template <typename U>
constexpr matrix2_T<T>::operator matrix2_T<U>() const
{
	return {U(m00), U(m10), U(m01), U(m11)};
}

template <typename T>
constexpr matrix2_T<T> matrix2_T<T>::zero()
{
	return {T(0), T(0), T(0), T(0)};
}

template <typename T>
constexpr matrix2_T<T> matrix2_T<T>::identity()
{
	return {T(1), T(0), T(0), T(1)};
}

template <typename T>
constexpr matrix2_T<T> matrix2_T<T>::rows(vector2_T<T> row0, vector2_T<T> row1)
{
	return {row0.x, row0.y, row1.x, row1.y};
}

template <typename T>
constexpr matrix2_T<T> matrix2_T<T>::columns(vector2_T<T> column0,
                                             vector2_T<T> column1)
{
	return {column0.x, column1.x, column0.y, column1.y};
}

template <typename T>
inline matrix2_T<T> matrix2_T<T>::rotation(radian_T<T> angle)
{
	const T c = cos(angle);
	const T s = sin(angle);
	return {c, -s, s, c};
}

template <typename T>
inline matrix2_T<T> matrix2_T<T>::rotation(normalized<complex_T<T>> angle)
{
	return {angle->r, -angle->i, angle->i, angle->r};
}

template <typename T>
constexpr matrix2_T<T>& matrix2_T<T>::transpose()
{
	std::swap(m01, m10);
	return *this;
}

template <typename T>
constexpr matrix2_T<T> matrix2_T<T>::get_transposed() const
{
	auto m = *this;
	m.transpose();
	return m;
}

template <typename T>
constexpr vector2_column_proxy<T> matrix2_T<T>::column(int i)
{
	return std::array{
	    vector2_column_proxy<T>{m00, m01},
	    vector2_column_proxy<T>{m10, m11},
	}[i];
}

template <typename T>
constexpr vector2_column_proxy<const T> matrix2_T<T>::column(int i) const
{
	return std::array{
	    vector2_column_proxy<const T>{m00, m01},
	    vector2_column_proxy<const T>{m10, m11},
	}[i];
}

template <typename T>
constexpr vector2_row_proxy<T> matrix2_T<T>::row(int i)
{
	return std::array{
	    vector2_row_proxy<T>{m00, m10},
	    vector2_row_proxy<T>{m01, m11},
	}[i];
}

template <typename T>
constexpr vector2_row_proxy<const T> matrix2_T<T>::row(int i) const
{
	return std::array{
	    vector2_row_proxy<const T>{m00, m10},
	    vector2_row_proxy<const T>{m01, m11},
	}[i];
}

template <typename T>
constexpr vector2_diag_proxy<T> matrix2_T<T>::diag()
{
	return vector2_diag_proxy<T>{m00, m11};
}

template <typename T>
constexpr vector2_diag_proxy<const T> matrix2_T<T>::diag() const
{
	return vector2_diag_proxy<const T>{m00, m11};
}

template <typename T>
constexpr vector2_T<T> matrix2_T<T>::operator*(vector2_T<T> v) const
{
	return {m00 * v.x + m01 * v.y, m10 * v.x + m11 * v.y};
}

template <typename T>
constexpr matrix2_T<T> matrix2_T<T>::operator*(matrix2_T<T> m) const
{
	return {m00 * m.m00 + m01 * m.m10, m00 * m.m01 + m01 * m.m11,

	        m10 * m.m00 + m11 * m.m10, m10 * m.m01 + m11 * m.m11};
}

template <typename T>
constexpr matrix2_T<T> transpose(matrix2_T<T> m)
{
	m.transpose();
	return m;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const cdm::matrix2_T<T>& m)
{
	const auto flags = os.flags();
	const auto w = std::setw(13);
	os << std::right;
	// clang-format off
	os << "matrix2_T(" << w << m.column(0).row(0) << " " << w << m.column(1).row(0) << "\n"
	      "          " << w << m.column(0).row(1) << " " << w << m.column(1).row(1) << ")";
	// clang-format on
	os.setf(flags);
	return os;
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_MATRIX2_HPP
