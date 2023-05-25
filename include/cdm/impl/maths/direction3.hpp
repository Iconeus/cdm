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

#ifndef CDM_MATHS_IMPL_DIRECTION3_HPP
#define CDM_MATHS_IMPL_DIRECTION3_HPP 1

#include <cdm/decl/maths/direction3.hpp>

namespace cdm
{
template <typename T>
constexpr const T& get_x(const direction3_T<T>& v)
{
	return v.x();
}

template <typename T>
constexpr const T& get_y(const direction3_T<T>& v)
{
	return v.y();
}

template <typename T>
constexpr const T& get_z(const direction3_T<T>& v)
{
	return v.z();
}

template <typename T>
constexpr vector3_T<T> cross(const direction3_T<T>& lhs,
                             const direction3_T<T>& rhs)
{
	return {
	    get_y(lhs) * get_z(rhs) - get_z(lhs) * get_y(rhs),
	    get_z(lhs) * get_x(rhs) - get_x(lhs) * get_z(rhs),
	    get_x(lhs) * get_y(rhs) - get_y(lhs) * get_x(rhs),
	};
}

template <typename T>
constexpr direction3_T<T>::direction3_T(T x_, T y_, T z_)
    : direction3_T(vector3_T<T>(x_, y_, z_))
{
}

template <typename T>
constexpr direction3_T<T>::direction3_T(const vector3_T<T>& v)
{
	vector3_T<T> vn = cdm::get_normalized(v);
	m_x = vn.x;
	m_y = vn.y;
	m_z = vn.z;
}

template <typename T>
constexpr direction3_T<T> direction3_T<T>::operator-() const
{
	return already_normalized(-m_x, -m_y, -m_z);
}

template <typename T>
constexpr const T& direction3_T<T>::x() const
{
	return m_x;
}

template <typename T>
constexpr const T& direction3_T<T>::y() const
{
	return m_y;
}

template <typename T>
constexpr const T& direction3_T<T>::z() const
{
	return m_z;
}

template <typename T>
constexpr std::array<T, 3> direction3_T<T>::to_array() const
{
	return {
	    m_x,
	    m_y,
	    m_z,
	};
}

template <typename T>
template <typename U>
constexpr direction3_T<T>::operator direction3_T<U>() const
{
	return direction3_T<U>::already_normalized(
	    static_cast<U>(m_x), static_cast<U>(m_y), static_cast<U>(m_z));
}

template <typename T>
constexpr bool direction3_T<T>::operator==(const direction3_T<T>& v) const
{
	return m_x == v.m_x && m_y == v.m_y && m_z == v.m_z;
}

template <typename T>
constexpr bool direction3_T<T>::operator!=(const direction3_T<T>& v) const
{
	return !operator==(v);
}

template <typename T>
constexpr bool direction3_T<T>::nearly_equal(const direction3_T<T>& v,
                                             T e) const
{
	return cdm::nearly_equal(*this, v, e);
}

template <typename T>
template <typename Index>
constexpr const T& direction3_T<T>::operator[](Index index) const
{
	switch (index)
	{
	case 0:
		return m_x;
	case 1:
		return m_y;
	case 2:
		return m_z;
	}

#ifndef NDEBUG
	throw std::out_of_range("attempting to index element " +
	                        std::to_string(index));
#else
	return x;
#endif
}

template <typename T>
constexpr direction3_T<T> direction3_T<T>::already_normalized(T x_, T y_, T z_)
{
	direction3_T<T> res;
	res.m_x = x_;
	res.m_y = y_;
	res.m_z = z_;
	return res;
}

template <typename T>
constexpr direction3_T<T> direction3_T<T>::already_normalized(
    const vector3_T<T>& v)
{
	return already_normalized(v.x, v.y, v.z);
}

template <typename T>
constexpr direction3_T<T> direction3_T<T>::posX()
{
	return already_normalized(T(1), T(0), T(0));
}

template <typename T>
constexpr direction3_T<T> direction3_T<T>::posY()
{
	return already_normalized(T(0), T(1), T(0));
}

template <typename T>
constexpr direction3_T<T> direction3_T<T>::posZ()
{
	return already_normalized(T(0), T(0), T(1));
}

template <typename T>
constexpr direction3_T<T> direction3_T<T>::negX()
{
	return already_normalized(T(-1), T(0), T(0));
}

template <typename T>
constexpr direction3_T<T> direction3_T<T>::negY()
{
	return already_normalized(T(0), T(-1), T(0));
}

template <typename T>
constexpr direction3_T<T> direction3_T<T>::negZ()
{
	return already_normalized(T(0), T(0), T(-1));
}

template <typename T>
constexpr vector3_T<T> operator*(T t, const direction3_T<T>& d)
{
	return t * vector3_T<T>(d);
}

template <typename T>
constexpr vector3_T<T> operator*(const direction3_T<T>& d, T t)
{
	return vector3_T<T>(d) * t;
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_DIRECTION3_HPP