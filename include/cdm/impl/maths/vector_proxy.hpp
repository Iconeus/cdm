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

#ifndef CDM_MATHS_IMPL_VECTOR_PROXY_HPP
#define CDM_MATHS_IMPL_VECTOR_PROXY_HPP 1

#include <cdm/decl/maths/vector2.hpp>
#include <cdm/decl/maths/vector3.hpp>
#include <cdm/decl/maths/vector4.hpp>
#include <cdm/decl/maths/vector_proxy.hpp>

namespace cdm
{
namespace detail
{
template <typename ProxyT>
constexpr typename ProxyT::type& column_proxy<ProxyT>::row(int i)
{
	return ProxyT::vector(i);
}

template <typename ProxyT>
constexpr const typename ProxyT::type& column_proxy<ProxyT>::row(int i) const
{
	return ProxyT::vector(i);
}

template <typename ProxyT>
constexpr typename ProxyT::type& row_proxy<ProxyT>::column(int i)
{
	return ProxyT::vector(i);
}

template <typename ProxyT>
constexpr const typename ProxyT::type& row_proxy<ProxyT>::column(int i) const
{
	return ProxyT::vector(i);
}

#pragma region vector2
template <arithmetic T>
constexpr T& vector2_proxy<T>::vector(int i)
{
	return std::array<std::reference_wrapper<T>, 2>{x, y}[i];
}

template <arithmetic T>
constexpr const T& vector2_proxy<T>::vector(int i) const
{
	return std::array<std::reference_wrapper<const T>, 2>{x, y}[i];
}

template <arithmetic T>
constexpr vector2_proxy<T>::vector2_proxy(T& e0, T& e1) : x{e0}, y{e1}
{
}

template <arithmetic T>
constexpr vector2_proxy<T>& vector2_proxy<T>::operator=(vector2_T<T> v)
{
	x = v.x;
	y = v.y;
	return *this;
}

template <arithmetic T>
constexpr vector2_proxy<T>::operator vector2_T<T>() const
{
	return vector2_T<T>{x, y};
}
#pragma endregion

#pragma region vector3
template <arithmetic T>
constexpr T& vector3_proxy<T>::vector(int i)
{
	return std::array<std::reference_wrapper<T>, 3>{x, y, z}[i];
}

template <arithmetic T>
constexpr const T& vector3_proxy<T>::vector(int i) const
{
	return std::array<std::reference_wrapper<const T>, 3>{x, y, z}[i];
}

template <arithmetic T>
constexpr vector3_proxy<T>::vector3_proxy(T& e0, T& e1, T& e2)
    : x{e0}, y{e1}, z{e2}
{
}

template <arithmetic T>
constexpr vector3_proxy<T>& vector3_proxy<T>::operator=(vector3_T<T> v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

template <arithmetic T>
constexpr vector2_T<T> vector3_proxy<T>::xy() const
{
	return {x, y};
}

template <arithmetic T>
constexpr vector3_proxy<T>::operator vector3_T<T>() const
{
	return {x, y, z};
}
#pragma endregion

#pragma region vector4
template <arithmetic T>
constexpr T& vector4_proxy<T>::vector(int i)
{
	return std::array<std::reference_wrapper<T>, 4>{x, y, z, w}[i];
}

template <arithmetic T>
constexpr const T& vector4_proxy<T>::vector(int i) const
{
	return std::array<std::reference_wrapper<const T>, 4>{x, y, z, w}[i];
}

template <arithmetic T>
constexpr vector4_proxy<T>::vector4_proxy(T& e0, T& e1, T& e2, T& e3)
    : x{e0}, y{e1}, z{e2}, w{e3}
{
}

template <arithmetic T>
constexpr vector4_proxy<T>& vector4_proxy<T>::operator=(vector4_T<T> v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}

template <arithmetic T>
constexpr vector2_T<T> vector4_proxy<T>::xy() const
{
	return {x, y};
}

template <arithmetic T>
constexpr vector3_T<T> vector4_proxy<T>::xyz() const
{
	return {x, y, z};
}

template <arithmetic T>
constexpr vector4_proxy<T>::operator vector4_T<T>() const
{
	return {x, y, z, w};
}
#pragma endregion
}  // namespace detail
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_VECTOR_PROXY_HPP
