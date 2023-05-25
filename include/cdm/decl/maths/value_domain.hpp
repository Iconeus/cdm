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

#ifndef CDM_MATHS_DECL_VALUE_DOMAIN_HPP
#define CDM_MATHS_DECL_VALUE_DOMAIN_HPP 1

#include <cdm/concepts.hpp>
#include <cdm/decl/maths/forward_declarations.hpp>

namespace cdm
{
template <arithmetic T>
class value_domain_T
{
	T m_lim0;
	T m_lim1;

public:
	value_domain_T() = default;
	constexpr value_domain_T(T lim0, T lim1) noexcept;
	value_domain_T(const value_domain_T&) = default;
	value_domain_T(value_domain_T&&) = default;
	~value_domain_T() = default;

	constexpr T lim0() const noexcept;
	constexpr T lim1() const noexcept;
	T range() const noexcept;
	constexpr T min() const noexcept;
	constexpr T max() const noexcept;

	constexpr T clamp(T value) const noexcept;
	constexpr T lerp(normalized_value_T<T> value) const noexcept;

	value_domain_T& operator=(const value_domain_T&) = default;
	value_domain_T& operator=(value_domain_T&&) = default;

	using underlying_type = T;
};

template <arithmetic T>
constexpr T domain_transfer(cdm::value_domain_T<T> from,
                            cdm::value_domain_T<T> to,
                            T value) noexcept;

using value_domain = value_domain_T<float>;
using value_domaind = value_domain_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_VALUE_DOMAIN_HPP
