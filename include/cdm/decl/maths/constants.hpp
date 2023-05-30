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

#ifndef CDM_MATHS_CONSTANTS_HPP
#define CDM_MATHS_CONSTANTS_HPP 1

#include <numbers>

namespace cdm
{
// clang-format off
using std::numbers::pi;
using std::numbers::inv_pi;
using std::numbers::inv_sqrtpi;
constexpr double deg_to_rad = pi / 180.0;
constexpr double rad_to_deg = 180.0 / pi;
using std::numbers::sqrt2;
using std::numbers::sqrt3;
constexpr double inv_sqrt2 = 0.7071067811865475244008443621048490392848359376884740365883398689;
using std::numbers::inv_sqrt3;
constexpr double sqrt3_over_2 = 0.8660254037844386467637231707529361834714026269051903140279034897;
constexpr double epsilon = 1.0e-05;
// clang-format on
}  // namespace cdm

#endif  // CDM_MATHS_CONSTANTS_HPP
