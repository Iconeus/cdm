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

#ifndef CDM_MATHS_DECL_MATRIX3_HPP
#define CDM_MATHS_DECL_MATRIX3_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>
#include <cdm/decl/maths/vector_proxy.hpp>

#include <array>
#include <iosfwd>

namespace cdm
{
template <typename T>
struct matrix3_T
{
	template <typename U>
	friend class matrix2_T;
	template <typename U>
	friend class matrix3_T;
	template <typename U>
	friend class matrix4_T;

private:
	T m00, m01, m02, m10, m11, m12, m20, m21, m22;

	constexpr matrix3_T(T m00,
	                    T m10,
	                    T m20,
	                    T m01,
	                    T m11,
	                    T m21,
	                    T m02,
	                    T m12,
	                    T m22);

public:
	matrix3_T() = default;
	explicit constexpr matrix3_T(matrix2_T<T> m);
	constexpr matrix3_T(const std::array<T, 9>& a);
	matrix3_T(const matrix3_T&) = default;
	matrix3_T(matrix3_T&&) = default;

	matrix3_T& operator=(const matrix3_T&) = default;
	matrix3_T& operator=(matrix3_T&&) = default;

	template <typename U>
	explicit constexpr operator matrix3_T<U>() const;

	constexpr operator std::array<T, 9>() const;

	template <typename U = T>
	constexpr std::array<U, 9> to_array() const;

	static constexpr matrix3_T zero();
	static constexpr matrix3_T identity();

	static constexpr matrix3_T rows(vector3_T<T> row0,
	                                vector3_T<T> row1,
	                                vector3_T<T> row2);
	static constexpr matrix3_T columns(vector3_T<T> column0,
	                                   vector3_T<T> column1,
	                                   vector3_T<T> column2);

private:
	static matrix3_T rotation(direction3_T<T> axis, T sinAngle, T cosAngle);

public:
	static matrix3_T rotation(direction3_T<T> axis, radian_T<T> angle);
	static matrix3_T rotation(direction3_T<T> axis,
	                          normalized<complex_T<T>> angle);
	template <std::signed_integral U, U NumeratorT, U DenominatorT>
	static matrix3_T rotation(
	    direction3_T<T> axis,
	    static_pi_fraction_T<U, NumeratorT, DenominatorT> angle);
	static matrix3_T rotation(euler_angles_T<T> r);
	static matrix3_T rotation(quaternion_T<T> q);

private:
	static matrix3_T rotation_around_x(T sinAngle, T cosAngle);
	static matrix3_T rotation_around_y(T sinAngle, T cosAngle);
	static matrix3_T rotation_around_z(T sinAngle, T cosAngle);

public:
	static matrix3_T rotation_around_x(radian_T<T> angle);
	static matrix3_T rotation_around_y(radian_T<T> angle);
	static matrix3_T rotation_around_z(radian_T<T> angle);

	static matrix3_T rotation_around_x(normalized<complex_T<T>> angle);
	static matrix3_T rotation_around_y(normalized<complex_T<T>> angle);
	static matrix3_T rotation_around_z(normalized<complex_T<T>> angle);

	template <std::signed_integral U, U NumeratorT, U DenominatorT>
	static matrix3_T rotation_around_x(
	    static_pi_fraction_T<U, NumeratorT, DenominatorT> angle);
	template <std::signed_integral U, U NumeratorT, U DenominatorT>
	static matrix3_T rotation_around_y(
	    static_pi_fraction_T<U, NumeratorT, DenominatorT> angle);
	template <std::signed_integral U, U NumeratorT, U DenominatorT>
	static matrix3_T rotation_around_z(
	    static_pi_fraction_T<U, NumeratorT, DenominatorT> angle);

	static constexpr matrix3_T scale(vector3_T<T> t);
	static constexpr matrix3_T scale(T x, T y, T z);
	static constexpr matrix3_T scale(T s);

	constexpr matrix3_T& inverse();
	constexpr matrix3_T get_inversed() const;
	constexpr matrix3_T& transpose();
	constexpr matrix3_T get_transposed() const;
	constexpr T determinant() const;
	constexpr bool is_orthogonal() const;

	constexpr vector3_column_proxy<T> column(int i);
	constexpr vector3_column_proxy<const T> column(int i) const;
	constexpr vector3_row_proxy<T> row(int i);
	constexpr vector3_row_proxy<const T> row(int i) const;
	constexpr vector3_diag_proxy<T> diag();
	constexpr vector3_diag_proxy<const T> diag() const;

	constexpr matrix3_T operator*(T f) const;
	constexpr vector3_T<T> operator*(vector3_T<T> v) const;
	constexpr matrix3_T operator*(const matrix3_T& m) const;

	constexpr bool operator==(const matrix3_T& m) const;

	using underlying_type = T;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const cdm::matrix3_T<T>& m);

namespace detail
{
template <typename T>
struct is_matrix<matrix3_T<T>> : std::true_type
{
};
}  // namespace detail

using matrix3 = matrix3_T<float>;
using matrix3d = matrix3_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_MATRIX3_HPP
