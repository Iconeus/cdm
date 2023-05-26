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

#ifndef CDM_IMPL_MATHS_HPP
#define CDM_IMPL_MATHS_HPP 1

#include <cdm/impl/maths/aabb2.hpp>
#include <cdm/impl/maths/aabb3.hpp>
#include <cdm/impl/maths/circle.hpp>
#include <cdm/impl/maths/complex.hpp>
#include <cdm/impl/maths/constants.hpp>
#include <cdm/impl/maths/degree.hpp>
#include <cdm/impl/maths/direction3.hpp>
#include <cdm/impl/maths/euler_angles.hpp>
#include <cdm/impl/maths/forward_declarations.hpp>
#include <cdm/impl/maths/line2.hpp>
#include <cdm/impl/maths/line3.hpp>
#include <cdm/impl/maths/literals.hpp>
#include <cdm/impl/maths/matrix2.hpp>
#include <cdm/impl/maths/matrix3.hpp>
#include <cdm/impl/maths/matrix4.hpp>
#include <cdm/impl/maths/misc.hpp>
#include <cdm/impl/maths/normalized.hpp>
#include <cdm/impl/maths/normalized_value.hpp>
#include <cdm/impl/maths/oriented_plane.hpp>
#include <cdm/impl/maths/perspective.hpp>
#include <cdm/impl/maths/pi_fraction.hpp>
#include <cdm/impl/maths/plane.hpp>
#include <cdm/impl/maths/point2.hpp>
#include <cdm/impl/maths/point3.hpp>
#include <cdm/impl/maths/quaternion.hpp>
#include <cdm/impl/maths/radian.hpp>
#include <cdm/impl/maths/ray2.hpp>
#include <cdm/impl/maths/ray3.hpp>
#include <cdm/impl/maths/segment2.hpp>
#include <cdm/impl/maths/segment3.hpp>
#include <cdm/impl/maths/static_pi_fraction.hpp>
#include <cdm/impl/maths/transform2.hpp>
#include <cdm/impl/maths/transform3.hpp>
#include <cdm/impl/maths/uniform_transform2.hpp>
#include <cdm/impl/maths/uniform_transform3.hpp>
#include <cdm/impl/maths/unnormalized_value.hpp>
#include <cdm/impl/maths/unscaled_transform2.hpp>
#include <cdm/impl/maths/unscaled_transform3.hpp>
#include <cdm/impl/maths/value_domain.hpp>
#include <cdm/impl/maths/vector.hpp>
#include <cdm/impl/maths/vector2.hpp>
#include <cdm/impl/maths/vector3.hpp>
#include <cdm/impl/maths/vector4.hpp>
#include <cdm/impl/maths/vector_proxy.hpp>

#endif  // CDM_IMPL_MATHS_HPP
