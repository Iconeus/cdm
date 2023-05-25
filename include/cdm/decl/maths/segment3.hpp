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

#ifndef CDM_MATHS_DECL_SEGMENT3_HPP
#define CDM_MATHS_DECL_SEGMENT3_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>

#include <iosfwd>

namespace cdm
{
template <typename T>
struct segment3_T
{
	vector3_T<T> origin;
	vector3_T<T> end;

	using underlying_type = T;
};

template <typename T>
constexpr bool collides(const segment3_T<T>& s,
                        const plane_T<T>& p,
                        T e = T(epsilon)) noexcept;
template <typename T>
constexpr bool collides(const segment3_T<T>& s,
                        const plane_T<T>& p,
                        vector3_T<T>& outPoint,
                        T e = T(epsilon)) noexcept;

template <typename T>
std::ostream& operator<<(std::ostream& os, segment3_T<T> t);

using segment3 = segment3_T<float>;
using segment3d = segment3_T<double>;
}  // namespace cdm

#endif  // CDM_MATHS_DECL_SEGMENT3_HPP
