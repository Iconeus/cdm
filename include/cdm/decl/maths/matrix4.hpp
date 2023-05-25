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

#ifndef CDM_MATHS_DECL_MATRIX4_HPP
#define CDM_MATHS_DECL_MATRIX4_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>
#include <cdm/decl/maths/vector_proxy.hpp>

#include <array>
#include <iosfwd>

namespace cdm
{
template <typename T>
struct matrix4_T
{
	template <typename U>
	friend class matrix2_T;
	template <typename U>
	friend class matrix3_T;
	template <typename U>
	friend class matrix4_T;

private:
	T m00, m01, m02, m03,    //
	    m10, m11, m12, m13,  //
	    m20, m21, m22, m23,  //
	    m30, m31, m32, m33;

	constexpr matrix4_T(T m00,
	                    T m10,
	                    T m20,
	                    T m30,
	                    T m01,
	                    T m11,
	                    T m21,
	                    T m31,
	                    T m02,
	                    T m12,
	                    T m22,
	                    T m32,
	                    T m03,
	                    T m13,
	                    T m23,
	                    T m33);

public:
	constexpr matrix4_T() = default;
	explicit constexpr matrix4_T(matrix2_T<T> m);
	explicit constexpr matrix4_T(const matrix3_T<T>& m);
	explicit constexpr matrix4_T(const perspective_T<T>& p);
	explicit constexpr matrix4_T(const transform3_T<T>& t);
	explicit constexpr matrix4_T(const uniform_transform3_T<T>& t);
	explicit constexpr matrix4_T(const unscaled_transform3_T<T>& t);
	explicit constexpr matrix4_T(const std::array<T, 16>& a);
	constexpr matrix4_T(const matrix4_T&) = default;
	constexpr matrix4_T(matrix4_T&&) = default;

	constexpr matrix4_T& operator=(const matrix4_T&) = default;
	constexpr matrix4_T& operator=(matrix4_T&&) = default;

	template <typename U>
	explicit constexpr operator matrix4_T<U>() const;

	constexpr operator std::array<T, 16>() const;

	template <typename U = T>
	constexpr std::array<U, 16> to_array() const;

	static constexpr matrix4_T zero();
	static constexpr matrix4_T identity();

	static constexpr matrix4_T rows(vector4_T<T> row0,
	                                vector4_T<T> row1,
	                                vector4_T<T> row2,
	                                vector4_T<T> row3);
	static constexpr matrix4_T columns(vector4_T<T> column0,
	                                   vector4_T<T> column1,
	                                   vector4_T<T> column2,
	                                   vector4_T<T> column3);

	static matrix4_T rotation(direction3_T<T> axis, radian_T<T> angle);
	static matrix4_T rotation(direction3_T<T> axis,
	                          normalized<complex_T<T>> angle);
	template <std::signed_integral U, U NumeratorT, U DenominatorT>
	static matrix4_T rotation(
	    direction3_T<T> axis,
	    static_pi_fraction_T<U, NumeratorT, DenominatorT> angle);
	static matrix4_T rotation(euler_angles_T<T> r);
	static matrix4_T rotation(quaternion_T<T> q);

	static matrix4_T rotation_around_x(radian_T<T> angle);
	static matrix4_T rotation_around_y(radian_T<T> angle);
	static matrix4_T rotation_around_z(radian_T<T> angle);

	static matrix4_T rotation_around_x(normalized<complex_T<T>> angle);
	static matrix4_T rotation_around_y(normalized<complex_T<T>> angle);
	static matrix4_T rotation_around_z(normalized<complex_T<T>> angle);

	template <std::signed_integral T, T NumeratorT, T DenominatorT>
	static matrix4_T rotation_around_x(
	    static_pi_fraction_T<T, NumeratorT, DenominatorT> angle);
	template <std::signed_integral T, T NumeratorT, T DenominatorT>
	static matrix4_T rotation_around_y(
	    static_pi_fraction_T<T, NumeratorT, DenominatorT> angle);
	template <std::signed_integral T, T NumeratorT, T DenominatorT>
	static matrix4_T rotation_around_z(
	    static_pi_fraction_T<T, NumeratorT, DenominatorT> angle);

	static constexpr matrix4_T translation(vector3_T<T> t);
	static constexpr matrix4_T translation(T x, T y, T z);

	static constexpr matrix4_T scale(vector3_T<T> t);
	static constexpr matrix4_T scale(T x, T y, T z);
	static constexpr matrix4_T scale(T s);

	static constexpr matrix4_T look_at(
	    vector3_T<T> from,
	    vector3_T<T> to,
	    direction3_T<T> up = direction3_T<T>::posY());

	static constexpr matrix4_T orthographic(T left,
	                                        T right,
	                                        T top,
	                                        T bottom,
	                                        T near,
	                                        T far);

	constexpr bool is_orthogonal() const;
	constexpr bool is_homogenous() const;
	constexpr matrix4_T& inverse();
	constexpr matrix4_T get_inversed() const;
	constexpr matrix4_T& transpose();
	constexpr matrix4_T get_transposed() const;
	constexpr T determinant() const;

	matrix3_T<T> extract_rotation_matrix() const;

	constexpr vector3_T<T> transform_position(vector3_T<T> pos) const;
	constexpr vector3_T<T> transform_direction(vector3_T<T> dir) const;
	constexpr direction3_T<T> transform_direction(direction3_T<T> dir) const;
	constexpr vector3_T<T> transform_position_perspective(
	    vector3_T<T> pos) const;

	constexpr point3_T<T> transform(const point3_T<T>& point) const;
	constexpr direction3_T<T> transform(const direction3_T<T>& dir) const;

	constexpr vector4_column_proxy<T> column(int i);
	constexpr vector4_column_proxy<const T> column(int i) const;
	constexpr vector4_row_proxy<T> row(int i);
	constexpr vector4_row_proxy<const T> row(int i) const;
	constexpr vector4_diag_proxy<T> diag();
	constexpr vector4_diag_proxy<const T> diag() const;

	constexpr matrix4_T operator*(T f) const;
	constexpr matrix4_T operator/(T f) const;
	constexpr vector4_T<T> operator*(vector4_T<T> v) const;
	constexpr matrix4_T operator*(const matrix4_T& m) const;

	constexpr bool operator==(const matrix4_T& m) const;

	using underlying_type = T;
};

template <typename T>
constexpr matrix4_T<T> operator*(const transform3_T<T>& t,
                                 const matrix4_T<T>& m);
template <typename T>
constexpr matrix4_T<T> operator*(const matrix4_T<T>& m,
                                 const transform3_T<T>& t);
template <typename T>
constexpr matrix4_T<T> operator*(const uniform_transform3_T<T>& t,
                                 const matrix4_T<T>& m);
template <typename T>
constexpr matrix4_T<T> operator*(const matrix4_T<T>& m,
                                 const uniform_transform3_T<T>& t);
template <typename T>
constexpr matrix4_T<T> operator*(const unscaled_transform3_T<T>& t,
                                 const matrix4_T<T>& m);
template <typename T>
constexpr matrix4_T<T> operator*(const matrix4_T<T>& m,
                                 const unscaled_transform3_T<T>& t);

template <typename T>
std::ostream& operator<<(std::ostream& os, const cdm::matrix4_T<T>& m);

namespace detail
{
template <typename T>
struct is_matrix<matrix4_T<T>> : std::true_type
{
};
}  // namespace detail

using matrix4 = matrix4_T<float>;
using matrix4d = matrix4_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_MATRIX4_HPP
