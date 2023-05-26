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

#ifndef CDM_MATHS_IMPL_NORMALIZED_VALUE_HPP
#define CDM_MATHS_IMPL_NORMALIZED_VALUE_HPP 1

#include <cdm/decl/maths/normalized_value.hpp>
#include <cdm/decl/maths/unnormalized_value.hpp>
#include <cdm/decl/maths/value_domain.hpp>

#include <algorithm>

namespace cdm
{
template <arithmetic T>
constexpr normalized_value_T<T>::normalized_value_T(T value) noexcept
    : m_value(std::clamp<T>(value, zero<T>(), one<T>()))
{
}

template <arithmetic T>
constexpr normalized_value_T<T>::normalized_value_T(
    unnormalized_value_T<T> value) noexcept
    : m_value((value.value() - value.domain().min()) / value.domain().range())
{
	if (value.domain().min() != value.domain().lim0())
		inverse();
}

template <arithmetic T>
template <arithmetic U>
constexpr normalized_value_T<T>::operator normalized_value_T<U>() const
{
	return normalized_value_T<U>{U(m_value)};
}

template <arithmetic T>
constexpr const T& normalized_value_T<T>::value() const noexcept
{
	return m_value;
}

template <arithmetic T>
constexpr normalized_value_T<T>& normalized_value_T<T>::inverse() noexcept
{
	m_value = T(1) - m_value;
	return *this;
}

template <arithmetic T>
constexpr normalized_value_T<T> normalized_value_T<T>::get_inversed()
    const noexcept
{
	auto res{*this};
	res.inverse();
	return res;
}

template <arithmetic T>
constexpr normalized_value_T<T>& normalized_value_T<T>::operator=(
    T value) noexcept
{
	m_value = std::clamp(value, T(0), T(1));
	return *this;
}

template <arithmetic T>
constexpr bool operator==(const normalized_value_T<T>& lhs,
                          const normalized_value_T<T>& rhs)
{
	return lhs.value() == rhs.value();
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_NORMALIZED_VALUE_HPP
