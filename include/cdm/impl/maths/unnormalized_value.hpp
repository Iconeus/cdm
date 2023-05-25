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

#ifndef CDM_MATHS_IMPL_UNNORMALIZED_VALUE_HPP
#define CDM_MATHS_IMPL_UNNORMALIZED_VALUE_HPP 1

#include <cdm/decl/maths/normalized_value.hpp>
#include <cdm/decl/maths/unnormalized_value.hpp>
#include <cdm/decl/maths/value_domain.hpp>

namespace cdm
{
template <arithmetic T>
constexpr unnormalized_value_T<T>::unnormalized_value_T(
    value_domain_T<T> domain,
    T value) noexcept
    : m_domain{domain}, m_value{m_domain.clamp(value)}
{
}

template <arithmetic T>
constexpr unnormalized_value_T<T>::unnormalized_value_T(
    value_domain_T<T> domain) noexcept
    : m_domain{domain}, m_value{m_domain.lim0()}
{
}

template <arithmetic T>
constexpr unnormalized_value_T<T>::unnormalized_value_T(
    value_domain_T<T> domain,
    normalized_value_T<T> value) noexcept
    : m_domain{domain}, m_value{m_domain.lerp(value)}
{
}

template <arithmetic T>
constexpr const value_domain_T<T>& unnormalized_value_T<T>::domain()
    const noexcept
{
	return m_domain;
}

template <arithmetic T>
constexpr const T& unnormalized_value_T<T>::value() const noexcept
{
	return m_value;
}

template <arithmetic T>
constexpr void unnormalized_value_T<T>::setValue(T value) noexcept
{
	m_value = m_domain.clamp(value);
}

template <arithmetic T>
constexpr normalized_value_T<T> unnormalized_value_T<T>::to_normalized()
    const noexcept
{
	return {*this};
}

template <arithmetic T>
constexpr unnormalized_value_T<T>& unnormalized_value_T<T>::operator=(
    normalized_value_T<T> value) noexcept
{
	m_value = m_domain.lerp(value);
	return *this;
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_UNNORMALIZED_VALUE_HPP
