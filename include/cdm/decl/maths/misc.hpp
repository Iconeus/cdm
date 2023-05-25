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

#ifndef CDM_MATHS_DECL_MISC_HPP
#define CDM_MATHS_DECL_MISC_HPP 1

#include <cdm/decl/maths/constants.hpp>
#include <cdm/decl/maths/forward_declarations.hpp>

#include <vector>

namespace cdm
{
// clang-format off
namespace detail
{
template <typename T> struct is_vector : std::false_type {};
template <typename T> constexpr bool is_vector_v = is_vector<T>::value;

template <typename T> struct is_matrix : std::false_type {};
template <typename T> constexpr bool is_matrix_v = is_matrix<T>::value;
}  // namespace detail

template <typename T> concept vector = detail::is_vector_v<T>;
template <typename T> concept matrix = detail::is_matrix_v<T>;
// clang-format on

namespace detail
{
template <int x, int y, typename T>
constexpr T get_quaternion_T_matrix_element(quaternion_T<T> q);
}  // namespace detail

template <typename Functor, typename T>
std::vector<vector3_T<T>> function2D_sampler(const Functor& functor,
                                             T min,
                                             T max,
                                             T step);

template <typename Functor, typename T>
std::vector<std::vector<vector3_T<T>>> function3D_sampler(
    const Functor& functor,
    vector2_T<T> min,
    vector2_T<T> max,
    vector2_T<T> step);

template <typename T>
bool nearly_equal(T f1, T f2, T e = T(epsilon));

template <typename T>
constexpr int sign(T val);

template <typename T>
constexpr int signnum(T val);

template <typename T>
constexpr T element_wise_min(T v0, T v1);

template <typename T>
constexpr T element_wise_max(T v0, T v1);

template <typename T>
T element_wise_abs(T v);

template <typename T>
constexpr T element_wise_lerp(T begin,
                              T end,
                              const normalized_value_T<T>& alpha);

template <typename T>
    requires arithmetic<T> || vector<T> || matrix<T>
constexpr T zero();

template <typename T>
    requires arithmetic<T> || vector<T> || matrix<T>
constexpr T one();

template <std::floating_point T>
constexpr T sqrt(T x);
}  // namespace cdm

#endif  // CDM_MATHS_DECL_MISC_HPP
