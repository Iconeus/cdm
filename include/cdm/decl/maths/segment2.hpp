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

#ifndef CDM_MATHS_DECL_SEGMENT2_HPP
#define CDM_MATHS_DECL_SEGMENT2_HPP 1

#include <cdm/decl/maths/constants.hpp>
#include <cdm/decl/maths/forward_declarations.hpp>

#include <iosfwd>
#include <optional>

namespace cdm
{
template <typename T>
struct segment2_T
{
	vector2_T<T> origin;
	vector2_T<T> end;

	T length() const;
	constexpr T length_squared() const;

	constexpr segment2_T& invert();

	using underlying_type = T;
};

template <typename T>
int collides(const segment2_T<T>& s0,
             const segment2_T<T>& s1,
             vector2_T<T>& outPoint0,
             vector2_T<T>& outPoint1,
             T e = T(epsilon));

template <typename T>
constexpr std::optional<vector2_T<T>> intersects(segment2_T<T> s0,
                                                 segment2_T<T> s1,
                                                 T e = T(epsilon));

template <typename T>
std::ostream& operator<<(std::ostream& os, segment2_T<T> t);

using segment2 = segment2_T<float>;
using segment2d = segment2_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_SEGMENT2_HPP
