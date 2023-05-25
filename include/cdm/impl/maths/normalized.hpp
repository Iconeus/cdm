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

#ifndef CDM_MATHS_IMPL_NORMALIZED_HPP
#define CDM_MATHS_IMPL_NORMALIZED_HPP 1

#include <cdm/decl/maths/misc.hpp>
#include <cdm/decl/maths/vector.hpp>

#include <algorithm>
#include <cmath>
#include <ostream>

namespace cdm
{
template <normalizable T>
template <typename... Args>
normalized<T>::normalized(Args... args) : normalized(T{args...})
{
}

template <normalizable T>
normalized<T>::normalized(const T& t) : vector(normalize(t))
{
	assert(vector.norm_squared() != 0);
}

template <normalizable T>
normalized<T> normalized<T>::already_normalized(const T& t)
{
	assert(t.norm_squared() != 0);
	normalized<T> res;
	res.vector = t;
	return res;
}

template <normalizable T>
normalized<T> normalized<T>::already_normalized(T&& t) noexcept
{
	assert(t.norm_squared() != 0);
	normalized<T> res;
	res.vector = std::move(t);
	return res;
}

template <normalizable T>
const T& normalized<T>::operator*() const
{
	return vector;
}

template <normalizable T>
const T* normalized<T>::operator->() const
{
	return &vector;
}

template <normalizable T>
normalized<T>::operator const T&() const
{
	return vector;
}

template <normalizable T>
normalized<T> normalized<T>::operator-() const
{
	return -vector;
}

template <normalizable T>
bool normalized<T>::operator==(const normalized<T>& v) const
{
	return vector == v.vector;
}

template <normalizable T>
bool normalized<T>::operator!=(const normalized<T>& v) const
{
	return vector != v.vector;
}

template <normalizable T>
bool normalized<T>::operator==(const T& v) const
{
	return vector == v;
}

template <normalizable T>
bool normalized<T>::operator!=(const T& v) const
{
	return vector != v;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const cdm::normalized<T>& n)
{
	return os << "normalized " << *n;
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_NORMALIZED_HPP
