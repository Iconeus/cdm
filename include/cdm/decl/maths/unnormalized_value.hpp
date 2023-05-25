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

#ifndef CDM_MATHS_DECL_UNNORMALIZED_VALUE_HPP
#define CDM_MATHS_DECL_UNNORMALIZED_VALUE_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>

namespace cdm
{
template <arithmetic T>
class unnormalized_value_T
{
	value_domain_T<T> m_domain;
	T m_value;

public:
	unnormalized_value_T() = default;
	explicit constexpr unnormalized_value_T(value_domain_T<T> domain,
	                                        T value) noexcept;
	explicit constexpr unnormalized_value_T(value_domain_T<T> domain) noexcept;
	explicit constexpr unnormalized_value_T(
	    value_domain_T<T> domain,
	    normalized_value_T<T> value) noexcept;
	unnormalized_value_T(const unnormalized_value_T&) = default;
	unnormalized_value_T(unnormalized_value_T&&) = default;
	~unnormalized_value_T() = default;

	constexpr const value_domain_T<T>& domain() const noexcept;
	constexpr const T& value() const noexcept;
	constexpr void setValue(T value) noexcept;

	constexpr normalized_value_T<T> to_normalized() const noexcept;

	constexpr unnormalized_value_T& operator=(
	    normalized_value_T<T> value) noexcept;
	unnormalized_value_T& operator=(const unnormalized_value_T&) = default;
	unnormalized_value_T& operator=(unnormalized_value_T&&) = default;

	using underlying_type = T;
};

using unnormalized_value = unnormalized_value_T<float>;
using unnormalized_valued = unnormalized_value_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_UNNORMALIZED_VALUE_HPP
