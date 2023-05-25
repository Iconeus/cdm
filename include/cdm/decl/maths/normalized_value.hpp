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

#ifndef CDM_MATHS_DECL_NORMALIZED_VALUE_HPP
#define CDM_MATHS_DECL_NORMALIZED_VALUE_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>

namespace cdm
{
template <arithmetic T>
class normalized_value_T
{
	T m_value;

public:
	normalized_value_T() = default;
	explicit constexpr normalized_value_T(T value) noexcept;
	explicit constexpr normalized_value_T(
	    unnormalized_value_T<T> value) noexcept;
	normalized_value_T(const normalized_value_T&) = default;
	normalized_value_T(normalized_value_T&&) = default;
	~normalized_value_T() = default;

	template <arithmetic U>
	explicit constexpr operator normalized_value_T<U>() const;

	constexpr const T& value() const noexcept;

	constexpr normalized_value_T& inverse() noexcept;
	constexpr normalized_value_T get_inversed() const noexcept;

	constexpr normalized_value_T& operator=(T value) noexcept;
	normalized_value_T& operator=(const normalized_value_T&) = default;
	normalized_value_T& operator=(normalized_value_T&&) = default;

	using underlying_type = T;
};

template <arithmetic T>
constexpr bool operator==(const normalized_value_T<T>& lhs,
                          const normalized_value_T<T>& rhs);

using normalized_value = normalized_value_T<float>;
using normalized_valued = normalized_value_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_NORMALIZED_VALUE_HPP
