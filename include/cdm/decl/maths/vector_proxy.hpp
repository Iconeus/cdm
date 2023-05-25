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

#ifndef CDM_MATHS_DECL_VECTOR_PROXY_HPP
#define CDM_MATHS_DECL_VECTOR_PROXY_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>

namespace cdm
{
namespace detail
{
template <typename ProxyT>
struct column_proxy : ProxyT
{
	using ProxyT::ProxyT;
	using ProxyT::operator=;

	constexpr typename ProxyT::type& row(int i);
	constexpr const typename ProxyT::type& row(int i) const;
};
template <typename ProxyT>
struct row_proxy : ProxyT
{
	using ProxyT::ProxyT;
	using ProxyT::operator=;

	constexpr ProxyT::type& column(int i);
	constexpr const ProxyT::type& column(int i) const;
};

template <arithmetic T>
struct vector2_proxy
{
	using type = T;

protected:
	T& x;
	T& y;

	constexpr T& vector(int i);
	constexpr const T& vector(int i) const;

public:
	constexpr vector2_proxy(T& e0, T& e1);
	constexpr vector2_proxy(const vector2_proxy&) = default;
	constexpr vector2_proxy(vector2_proxy&&) = default;
	constexpr vector2_proxy& operator=(const vector2_proxy&) = default;
	constexpr vector2_proxy& operator=(vector2_proxy&&) = default;
	constexpr vector2_proxy& operator=(vector2_T<T> v);

	constexpr operator vector2_T<T>() const;
};

template <arithmetic T>
struct vector3_proxy
{
	using type = T;

protected:
	T& x;
	T& y;
	T& z;

	constexpr T& vector(int i);
	constexpr const T& vector(int i) const;

public:
	constexpr vector3_proxy(T& e0, T& e1, T& e2);
	constexpr vector3_proxy(const vector3_proxy&) = default;
	constexpr vector3_proxy(vector3_proxy&&) = default;
	constexpr vector3_proxy& operator=(const vector3_proxy&) = default;
	constexpr vector3_proxy& operator=(vector3_proxy&&) = default;
	constexpr vector3_proxy& operator=(vector3_T<T> v);

	constexpr vector2_T<T> xy() const;
	constexpr operator vector3_T<T>() const;
};

template <arithmetic T>
struct vector4_proxy
{
	using type = T;

protected:
	T& x;
	T& y;
	T& z;
	T& w;

	constexpr T& vector(int i);
	constexpr const T& vector(int i) const;

public:
	constexpr vector4_proxy(T& e0, T& e1, T& e2, T& e3);
	constexpr vector4_proxy(const vector4_proxy&) = default;
	constexpr vector4_proxy(vector4_proxy&&) = default;
	constexpr vector4_proxy& operator=(const vector4_proxy&) = default;
	constexpr vector4_proxy& operator=(vector4_proxy&&) = default;
	constexpr vector4_proxy& operator=(vector4_T<T> v);

	constexpr vector2_T<T> xy() const;
	constexpr vector3_T<T> xyz() const;
	constexpr operator vector4_T<T>() const;
};
}  // namespace detail

#pragma region vector2
template <arithmetic T>
struct vector2_column_proxy : detail::column_proxy<detail::vector2_proxy<T>>
{
	using detail::column_proxy<detail::vector2_proxy<T>>::column_proxy;
	using detail::vector2_proxy<T>::operator=;
	using detail::vector2_proxy<T>::x;
	using detail::vector2_proxy<T>::y;
};

template <arithmetic T>
struct vector2_row_proxy : detail::row_proxy<detail::vector2_proxy<T>>
{
	using detail::row_proxy<detail::vector2_proxy<T>>::row_proxy;
	using detail::vector2_proxy<T>::operator=;
	using detail::vector2_proxy<T>::x;
	using detail::vector2_proxy<T>::y;
};

template <arithmetic T>
struct vector2_diag_proxy : detail::vector2_proxy<T>
{
	using detail::vector2_proxy<T>::vector2_proxy;
	using detail::vector2_proxy<T>::operator=;
	using detail::vector2_proxy<T>::x;
	using detail::vector2_proxy<T>::y;
};
#pragma endregion

#pragma region vector3
template <arithmetic T>
struct vector3_column_proxy : detail::column_proxy<detail::vector3_proxy<T>>
{
	using detail::column_proxy<detail::vector3_proxy<T>>::column_proxy;
	using detail::vector3_proxy<T>::operator=;
	using detail::vector3_proxy<T>::x;
	using detail::vector3_proxy<T>::y;
	using detail::vector3_proxy<T>::z;
};

template <arithmetic T>
struct vector3_row_proxy : detail::row_proxy<detail::vector3_proxy<T>>
{
	using detail::row_proxy<detail::vector3_proxy<T>>::row_proxy;
	using detail::vector3_proxy<T>::operator=;
	using detail::vector3_proxy<T>::x;
	using detail::vector3_proxy<T>::y;
	using detail::vector3_proxy<T>::z;
};

template <arithmetic T>
struct vector3_diag_proxy : detail::vector3_proxy<T>
{
	using detail::vector3_proxy<T>::vector3_proxy;
	using detail::vector3_proxy<T>::operator=;
	using detail::vector3_proxy<T>::x;
	using detail::vector3_proxy<T>::y;
	using detail::vector3_proxy<T>::z;
};
#pragma endregion

#pragma region vector4
template <arithmetic T>
struct vector4_column_proxy : detail::column_proxy<detail::vector4_proxy<T>>
{
	using detail::column_proxy<detail::vector4_proxy<T>>::column_proxy;
	using detail::vector4_proxy<T>::operator=;
	using detail::vector4_proxy<T>::x;
	using detail::vector4_proxy<T>::y;
	using detail::vector4_proxy<T>::z;
	using detail::vector4_proxy<T>::w;
};

template <arithmetic T>
struct vector4_row_proxy : detail::row_proxy<detail::vector4_proxy<T>>
{
	using detail::row_proxy<detail::vector4_proxy<T>>::row_proxy;
	using detail::vector4_proxy<T>::operator=;
	using detail::vector4_proxy<T>::x;
	using detail::vector4_proxy<T>::y;
	using detail::vector4_proxy<T>::z;
	using detail::vector4_proxy<T>::w;
};

template <arithmetic T>
struct vector4_diag_proxy : detail::vector4_proxy<T>
{
	using detail::vector4_proxy<T>::vector4_proxy;
	using detail::vector4_proxy<T>::operator=;
	using detail::vector4_proxy<T>::x;
	using detail::vector4_proxy<T>::y;
	using detail::vector4_proxy<T>::z;
	using detail::vector4_proxy<T>::w;
};
#pragma endregion
}  // namespace cdm

#endif  // CDM_MATHS_DECL_VECTOR_PROXY_HPP
