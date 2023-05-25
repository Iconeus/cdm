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

#ifndef CDM_MATHS_DECL_NORMALIZED_HPP
#define CDM_MATHS_DECL_NORMALIZED_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>

namespace cdm
{
template <normalizable T>
class normalized
{
	T vector;

public:
	normalized() = default;
	normalized(const normalized&) = default;
	normalized(normalized&&) = default;
	explicit normalized(const T& t);
	template <typename... Args>
	explicit normalized(Args... args);

	static normalized already_normalized(const T& t);
	static normalized already_normalized(T&& t) noexcept;

	const T& operator*() const;
	const T* operator->() const;
	operator const T&() const;

	normalized operator-() const;

	bool operator==(const normalized& n) const;
	bool operator!=(const normalized& n) const;
	bool operator==(const T& v) const;
	bool operator!=(const T& v) const;

	normalized& operator=(const normalized&) = default;
	normalized& operator=(normalized&&) = default;

	using underlying_type = T;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const cdm::normalized<T>& n);
}  // namespace cdm

#endif  // CDM_MATHS_DECL_NORMALIZED_HPP
