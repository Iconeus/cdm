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

#ifndef CDM_MATHS_DECL_MATRIX2_HPP
#define CDM_MATHS_DECL_MATRIX2_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>
#include <cdm/decl/maths/vector_proxy.hpp>

#include <array>
#include <iosfwd>

namespace cdm
{
template <typename T>
struct matrix2_T
{
	template <typename U>
	friend class matrix2_T;
	template <typename U>
	friend class matrix3_T;
	template <typename U>
	friend class matrix4_T;

private:
	T m00, m01, m10, m11;

	constexpr matrix2_T(T m00, T m10, T m01, T m11);

public:
	matrix2_T() = default;
	explicit constexpr matrix2_T(const std::array<T, 4>& a);
	matrix2_T(const matrix2_T&) = default;
	matrix2_T(matrix2_T&&) = default;

	matrix2_T& operator=(const matrix2_T&) = default;
	matrix2_T& operator=(matrix2_T&&) = default;

	template <typename U = T>
	constexpr std::array<U, 4> to_array() const;

	template <typename U>
	explicit constexpr operator matrix2_T<U>() const;

	static constexpr matrix2_T zero();
	static constexpr matrix2_T identity();

	static constexpr matrix2_T rows(vector2_T<T> row0, vector2_T<T> row1);
	static constexpr matrix2_T columns(vector2_T<T> column0,
	                                   vector2_T<T> column1);

	static matrix2_T rotation(radian_T<T> angle);
	static matrix2_T rotation(normalized<complex_T<T>> angle);

	constexpr matrix2_T& transpose();
	constexpr matrix2_T get_transposed() const;

	constexpr vector2_column_proxy<T> column(int i);
	constexpr vector2_column_proxy<const T> column(int i) const;
	constexpr vector2_row_proxy<T> row(int i);
	constexpr vector2_row_proxy<const T> row(int i) const;
	constexpr vector2_diag_proxy<T> diag();
	constexpr vector2_diag_proxy<const T> diag() const;

	constexpr vector2_T<T> operator*(vector2_T<T> v) const;
	constexpr matrix2_T operator*(matrix2_T m) const;

	using underlying_type = T;
};

template <typename T>
constexpr matrix2_T<T> transpose(matrix2_T<T> m);

template <typename T>
std::ostream& operator<<(std::ostream& os, const cdm::matrix2_T<T>& m);

namespace detail
{
template <typename T>
struct is_matrix<matrix2_T<T>> : std::true_type
{
};
}  // namespace detail

using matrix2 = matrix2_T<float>;
using matrix2d = matrix2_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_MATRIX2_HPP
