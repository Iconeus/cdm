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

#ifndef CDM_MATHS_IMPL_COMPLEX_HPP
#define CDM_MATHS_IMPL_COMPLEX_HPP 1

#include <cdm/decl/maths/complex.hpp>
#include <cdm/decl/maths/radian.hpp>

namespace cdm
{
template <typename T>
constexpr complex_T<T>::complex_T(T r_, T i_) : r{r_}, i{i_}
{
}

template <typename T>
constexpr complex_T<T>::complex_T(radian_T<T> angle)
    : r{cos(angle)}, i{sin(angle)}
{
}

template <typename T>
inline radian_T<T> complex_T<T>::angle() const
{
	return radian_T<T>(atan2(i, r));
}

template <typename T>
inline T complex_T<T>::norm() const
{
	return std::sqrt(norm_squared());
}

template <typename T>
constexpr T complex_T<T>::norm_squared() const
{
	return r * r + i * i;
}

template <typename T>
inline complex_T<T>& complex_T<T>::normalize()
{
	const T n = norm();
	r /= n;
	i /= n;
	return *this;
}

template <typename T>
inline complex_T<T> complex_T<T>::get_normalized() const
{
	complex_T<T> res{*this};
	res.normalize();
	return *this;
}

template <typename T>
constexpr complex_T<T>& complex_T<T>::conjugate()
{
	i = -i;
	return *this;
}

template <typename T>
constexpr complex_T<T> complex_T<T>::get_conjugated() const
{
	complex_T<T> res{*this};
	res.conjugate();
	return *this;
}

template <typename T>
constexpr complex_T<T> complex_T<T>::operator+(complex_T<T> c) const
{
	return {
	    r + c.r,
	    i + c.i,
	};
}

template <typename T>
constexpr complex_T<T> complex_T<T>::operator-(complex_T<T> c) const
{
	return {
	    r - c.r,
	    i - c.i,
	};
}

template <typename T>
constexpr complex_T<T>& complex_T<T>::operator+=(complex_T<T> c)
{
	return *this = *this + c;
}

template <typename T>
constexpr complex_T<T>& complex_T<T>::operator-=(complex_T<T> c)
{
	return *this = *this - c;
}

template <typename T>
constexpr complex_T<T>& complex_T<T>::operator*=(complex_T<T> c)
{
	return *this = *this * c;
}

template <typename T>
constexpr complex_T<T> complex_T<T>::identity()
{
	return {
	    T(1),
	    T(0),
	};
}

template <typename T>
constexpr complex_T<T> operator*(complex_T<T> c1, complex_T<T> c2)
{
	return {
	    c1.r * c2.r - c1.i * c2.i,
	    c1.r * c2.i + c1.i * c2.r,
	};
}

template <typename T>
constexpr complex_T<T> operator*(complex_T<T> c, T f)
{
	return {
	    c.r * f,
	    c.i * f,
	};
}

template <typename T>
constexpr complex_T<T> operator*(normalized<complex_T<T>> c1, complex_T<T> c2)
{
	return *c1 * c2;
}

template <typename T>
constexpr complex_T<T> operator*(complex_T<T> c1, normalized<complex_T<T>> c2)
{
	return c1 * *c2;
}

template <typename T>
constexpr normalized<complex_T<T>> operator*(normalized<complex_T<T>> c1,
                                             normalized<complex_T<T>> c2)
{
	return normalized<complex_T<T>>::already_normalized(complex_T<T>{
	    c1->r * c2->r - c1->i * c2->i,
	    c1->r * c2->i + c1->i * c2->r,
	});
}

template <typename T>
constexpr vector2_T<T> operator*(complex_T<T> c, vector2_T<T> v)
{
	return {
	    c.r * v.x - c.i * v.y,
	    c.r * v.y + c.i * v.x,
	};
}

template <typename T>
constexpr vector2_T<T> operator*(normalized<complex_T<T>> c, vector2_T<T> v)
{
	return {
	    c->r * v.x - c->i * v.y,
	    c->r * v.y + c->i * v.x,
	};
}

template <typename T>
inline T norm(complex_T<T> c)
{
	return c.norm_squared();
}

template <typename T>
constexpr T norm_squared(complex_T<T> c)
{
	return c.norm();
}

template <typename T>
inline complex_T<T> normalize(complex_T<T> c)
{
	c.normalize();
	return c;
}

template <typename T>
constexpr complex_T<T> conjugate(complex_T<T> c)
{
	c.conjugate();
	return c;
}

template <typename T>
inline radian_T<T> angle_between(complex_T<T> c1, complex_T<T> c2)
{
	return radian_T{atan2(c2.i, c2.r) - atan2(c1.i, c1.r)};
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_COMPLEX_HPP
