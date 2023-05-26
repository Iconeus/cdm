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

#ifndef CDM_MATHS_DECL_VECTOR_HPP
#define CDM_MATHS_DECL_VECTOR_HPP 1

#include <cdm/decl/maths/forward_declarations.hpp>
#include <cdm/decl/maths/misc.hpp>

#include <array>
#include <iosfwd>

namespace cdm
{
template <typename T, template <typename> typename Vector>
constexpr T& get_x(Vector<T>& v);
template <typename T, template <typename> typename Vector>
constexpr const T& get_x(const Vector<T>& v);
template <typename T, template <typename> typename Vector>
constexpr T& get_y(Vector<T>& v);
template <typename T, template <typename> typename Vector>
constexpr const T& get_y(const Vector<T>& v);
template <typename T, template <typename> typename Vector>
constexpr T& get_z(Vector<T>& v);
template <typename T, template <typename> typename Vector>
constexpr const T& get_z(const Vector<T>& v);
template <typename T, template <typename> typename Vector>
constexpr T& get_w(Vector<T>& v);
template <typename T, template <typename> typename Vector>
constexpr const T& get_w(const Vector<T>& v);

template <typename T, template <typename> typename Vector>
constexpr T norm(const Vector<T>& v);

template <typename T, template <typename> typename Vector>
constexpr T norm_squared(const Vector<T>& v);

template <typename T, template <typename> typename Vector>
constexpr Vector<T>& normalize(Vector<T>& v);

template <typename T, template <typename> typename Vector>
constexpr Vector<T> get_normalized(const Vector<T>& v);

template <typename T,
          template <typename>
          typename LVector,
          template <typename>
          typename RVector>
constexpr T dot(const LVector<T>& lhs, const RVector<T>& rhs);

template <typename T, template <typename> typename Vector>
constexpr Vector<T> cross(const Vector<T>& lhs, const Vector<T>& rhs);

template <typename T, template <typename> typename Vector>
constexpr Vector<T> lerp(const Vector<T>& begin,
                         const Vector<T>& end,
                         const normalized_value_T<T>& alpha);

template <typename T, template <typename> typename Vector>
constexpr Vector<T> nlerp(const Vector<T>& begin,
                          const Vector<T>& end,
                          const normalized_value_T<T>& alpha);

template <typename T, template <typename> typename Vector>
    requires vector<Vector<T>>
constexpr Vector<T>& element_wise_clamp(Vector<T>& v,
                                        const Vector<T>& min,
                                        const Vector<T>& max);

template <typename T, template <typename> typename Vector>
    requires vector<Vector<T>>
constexpr Vector<T> get_element_wise_clamped(const Vector<T>& v,
                                             const Vector<T>& min,
                                             const Vector<T>& max);

template <typename T, template <typename> typename Vector>
constexpr T distance_between(const Vector<T>& lhs, const Vector<T>& rhs);

template <typename T, template <typename> typename Vector>
constexpr T distance_squared_between(const Vector<T>& lhs,
                                     const Vector<T>& rhs);

template <typename T, template <typename> typename Vector>
constexpr Vector<T> from_to(const Vector<T>& from, const Vector<T>& to);

template <typename T, template <typename> typename Vector>
radian_T<T> angle_between(const Vector<T>& v0, const Vector<T>& v1);

template <typename T, template <typename> typename Vector>
radian_T<T> angle_around_axis(const Vector<T>& v0,
                              const Vector<T>& v1,
                              const direction3_T<T>& axis);

template <typename T, template <typename> typename Vector>
constexpr bool nearly_equal(const Vector<T>& v0,
                            const Vector<T>& v1,
                            T e = T(epsilon));

template <typename T, template <typename> typename Vector>
constexpr Vector<T> element_wise_min(const Vector<T>& v0, const Vector<T>& v1);

template <typename T, template <typename> typename Vector>
constexpr Vector<T> element_wise_max(const Vector<T>& v0, const Vector<T>& v1);

template <typename T, template <typename> typename Vector>
Vector<T> element_wise_abs(const Vector<T>& v);

template <typename T, template <typename> typename Vector>
constexpr Vector<T> element_wise_lerp(
    const Vector<T>& begin,
    const Vector<T>& end,
    const Vector<normalized_value_T<T>>& alpha);

template <typename T, template <typename> typename Vector>
    requires vector<Vector<T>>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v);
}  // namespace cdm

#endif  // CDM_MATHS_DECL_VECTOR_HPP
