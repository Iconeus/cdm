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

#ifndef CDM_MATHS_IMPL_LITERALS_HPP
#define CDM_MATHS_IMPL_LITERALS_HPP 1

#include <cdm/decl/maths/constants.hpp>
#include <cdm/decl/maths/degree.hpp>
#include <cdm/decl/maths/literals.hpp>
#include <cdm/decl/maths/radian.hpp>

namespace cdm
{
namespace literals
{
constexpr cdm::radian_T<float> operator""_rad(long double d)
{
	return cdm::radian_T<float>(static_cast<float>(d));
}

constexpr cdm::radian_T<float> operator""_rad(unsigned long long int i)
{
	return cdm::radian_T<float>(static_cast<float>(i));
}

constexpr cdm::radian_T<float> operator""_pi(long double d)
{
	return cdm::radian_T<float>(static_cast<float>(d * cdm::pi));
}

constexpr cdm::radian_T<float> operator""_pi(unsigned long long int i)
{
	return cdm::radian_T<float>(static_cast<float>(i * cdm::pi));
}

constexpr cdm::degree_T<float> operator""_deg(long double d)
{
	return cdm::degree_T<float>(static_cast<float>(d));
}

constexpr cdm::degree_T<float> operator""_deg(unsigned long long int i)
{
	return cdm::degree_T<float>(static_cast<float>(i));
}

constexpr cdm::radian_T<double> operator""_radd(long double d)
{
	return cdm::radian_T<double>(static_cast<double>(d));
}

constexpr cdm::radian_T<double> operator""_radd(unsigned long long int i)
{
	return cdm::radian_T<double>(static_cast<double>(i));
}

constexpr cdm::radian_T<double> operator""_pid(long double d)
{
	return cdm::radian_T<double>(static_cast<double>(d * cdm::pi));
}

constexpr cdm::radian_T<double> operator""_pid(unsigned long long int i)
{
	return cdm::radian_T<double>(static_cast<double>(i * cdm::pi));
}

constexpr cdm::degree_T<double> operator""_degd(long double d)
{
	return cdm::degree_T<double>(static_cast<double>(d));
}

constexpr cdm::degree_T<double> operator""_degd(unsigned long long int i)
{
	return cdm::degree_T<double>(static_cast<double>(i));
}
}  // namespace literals
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_LITERALS_HPP
