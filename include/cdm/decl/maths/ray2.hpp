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

#ifndef CDM_MATHS_DECL_RAY2_HPP
#define CDM_MATHS_DECL_RAY2_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>

#include <optional>

namespace cdm
{
template <typename T>
struct ray2_T
{
	point2_T<T> origin;
	direction2_T<T> direction;

	using underlying_type = T;
};

template <typename T>
constexpr bool collides(const ray2_T<T>& r, const segment2_T<T>& s);

template <typename T>
constexpr std::optional<point2_T<T>> intersection(const ray2_T<T>& r,
                                                  const segment2_T<T>& s);

using ray2 = ray2_T<float>;
using ray2d = ray2_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_RAY2_HPP
