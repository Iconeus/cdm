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

#ifndef CDM_MATHS_IMPL_VALUE_DOMAIN_HPP
#define CDM_MATHS_IMPL_VALUE_DOMAIN_HPP 1

#include <cdm/decl/maths/normalized_value.hpp>
#include <cdm/decl/maths/value_domain.hpp>

namespace cdm
{
template <arithmetic T>
constexpr value_domain_T<T>::value_domain_T(T lim0, T lim1) noexcept
    : m_lim0(lim0), m_lim1(lim1)
{
}

template <arithmetic T>
constexpr T value_domain_T<T>::lim0() const noexcept
{
	return m_lim0;
}

template <arithmetic T>
constexpr T value_domain_T<T>::lim1() const noexcept
{
	return m_lim1;
}

template <arithmetic T>
inline T value_domain_T<T>::range() const noexcept
{
	return std::abs(lim0() - lim1());
}

template <arithmetic T>
constexpr T value_domain_T<T>::min() const noexcept
{
	return std::min(lim0(), lim1());
}

template <arithmetic T>
constexpr T value_domain_T<T>::max() const noexcept
{
	return std::max(lim0(), lim1());
}

template <arithmetic T>
constexpr T value_domain_T<T>::clamp(T value) const noexcept
{
	return std::clamp(value, min(), max());
}

template <arithmetic T>
constexpr T value_domain_T<T>::lerp(normalized_value_T<T> value) const noexcept
{
	return std::lerp(lim0(), lim1(), value.value());
}

template <arithmetic T>
constexpr T domain_transfer(cdm::value_domain_T<T> from,
                            cdm::value_domain_T<T> to,
                            T value) noexcept
{
	cdm::unnormalized_value_T<T> valueFrom{from, value};
	cdm::normalized_value_T<T> norm{valueFrom};
	cdm::unnormalized_value_T<T> valueTo{to, norm};
	return valueTo.value();
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_VALUE_DOMAIN_HPP
