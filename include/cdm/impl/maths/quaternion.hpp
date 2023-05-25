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

#ifndef CDM_MATHS_IMPL_QUATERNION_HPP
#define CDM_MATHS_IMPL_QUATERNION_HPP 1

#include <cdm/decl/maths/complex.hpp>
#include <cdm/decl/maths/quaternion.hpp>
#include <cdm/decl/maths/radian.hpp>

#include <ostream>

namespace cdm
{
template <typename T>
constexpr quaternion_T<T>::quaternion_T(T x_, T y_, T z_, T w_)
    : x{x_}, y{y_}, z{z_}, w{w_}
{
}

template <typename T>
constexpr quaternion_T<T>::quaternion_T(std::array<T, 4> a)
    : quaternion_T{a[0], a[1], a[2], a[3]}
{
}

template <typename T>
inline quaternion_T<T>::quaternion_T(direction3_T<T> axis, radian_T<T> angle)
{
	vector3_T<T> tmpAxis = axis * sin(angle / T(2.0));
	*this = {tmpAxis.x, tmpAxis.y, tmpAxis.z, cos(angle / T(2.0))};
}

template <typename T>
template <std::signed_integral U, U NumeratorT, U DenominatorT>
inline quaternion_T<T>::quaternion_T(
    direction3_T<T> axis,
    static_pi_fraction_T<U, NumeratorT, DenominatorT> angle)
{
	using HalfAngle = static_pi_fraction_T<U, NumeratorT, DenominatorT * U(2)>;

	vector3_T<T> tmpAxis = axis * sin<T>(HalfAngle{});
	*this = {tmpAxis.x, tmpAxis.y, tmpAxis.z, cos<T>(HalfAngle{})};
}

template <typename T>
template <typename U>
constexpr quaternion_T<T>::operator quaternion_T<U>() const
{
	return quaternion_T<U>{static_cast<U>(x), static_cast<U>(y),
	                       static_cast<U>(z), static_cast<U>(w)};
}

template <typename T>
constexpr quaternion_T<T>::operator std::array<T, 4>() const
{
	return {x, y, z, w};
}

template <typename T>
template <typename U>
constexpr std::array<U, 4> quaternion_T<T>::to_array() const
{
	return {
	    static_cast<U>(x),
	    static_cast<U>(y),
	    static_cast<U>(z),
	    static_cast<U>(w),
	};
}

template <typename T>
constexpr quaternion_T<T> quaternion_T<T>::identity()
{
	return {T(0), T(0), T(0), T(1)};
}

template <typename T>
inline quaternion_T<T> quaternion_T<T>::from_rotation_matrix(
    const matrix3_T<T>& m)
{
	const auto diag = m.diag();

	const T fourXSquaredMinus1 = diag.x - diag.y - diag.z;
	const T fourYSquaredMinus1 = diag.y - diag.x - diag.z;
	const T fourZSquaredMinus1 = diag.z - diag.x - diag.y;
	const T fourWSquaredMinus1 = diag.x + diag.y + diag.z;

	int biggestIndex = 0;
	T fourBiggestSquaredMinus1 = fourWSquaredMinus1;
	if (fourXSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourXSquaredMinus1;
		biggestIndex = 1;
	}
	if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourYSquaredMinus1;
		biggestIndex = 2;
	}
	if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourZSquaredMinus1;
		biggestIndex = 3;
	}

	const T biggestVal = std::sqrt(fourBiggestSquaredMinus1 + T(1)) * T(0.5);
	const T mult = T(0.25) / biggestVal;

	switch (biggestIndex)
	{
	case 0:
		return {
		    (m.column(1).row(2) - m.column(2).row(1)) * mult,
		    (m.column(2).row(0) - m.column(0).row(2)) * mult,
		    (m.column(0).row(1) - m.column(1).row(0)) * mult,
		    biggestVal,
		};
	case 1:
		return {
		    biggestVal,
		    (m.column(0).row(1) + m.column(1).row(0)) * mult,
		    (m.column(2).row(0) + m.column(0).row(2)) * mult,
		    (m.column(1).row(2) - m.column(2).row(1)) * mult,
		};
	case 2:
		return {
		    (m.column(0).row(1) + m.column(1).row(0)) * mult,
		    biggestVal,
		    (m.column(1).row(2) + m.column(2).row(1)) * mult,
		    (m.column(2).row(0) - m.column(0).row(2)) * mult,
		};
	case 3:
		return {
		    (m.column(2).row(0) + m.column(0).row(2)) * mult,
		    (m.column(1).row(2) + m.column(2).row(1)) * mult,
		    biggestVal,
		    (m.column(0).row(1) - m.column(1).row(0)) * mult,
		};

	default:
		assert(false);
		return {
		    T(0),
		    T(0),
		    T(0),
		    T(1),
		};
	}
}

template <typename T>
inline quaternion_T<T> quaternion_T<T>::look_at(direction3_T<T> forward,
                                                direction3_T<T> upward)
{
	const direction3_T<T> backward = -forward;
	const direction3_T<T> rightward = direction3_T<T>(cross(upward, backward));
	upward = direction3_T<T>(cross(backward, rightward));

	const matrix3_T<T> rotMat =
	    matrix3_T<T>::columns(rightward, upward, backward);

	return from_rotation_matrix(rotMat);
}

template <typename T>
inline T quaternion_T<T>::norm() const
{
	return std::sqrt(norm_squared());
}

template <typename T>
constexpr T quaternion_T<T>::norm_squared() const
{
	return x * x + y * y + z * z + w * w;
}

template <typename T>
inline quaternion_T<T>& quaternion_T<T>::inverse()
{
	const T n = norm();
	if (nearly_equal(n, T(1)))
		return conjugate();

	x /= -n;
	y /= -n;
	z /= -n;
	w /= n;
	return *this;
}

template <typename T>
constexpr quaternion_T<T>& quaternion_T<T>::conjugate()
{
	x = -x;
	y = -y;
	z = -z;
	return *this;
}

template <typename T>
inline quaternion_T<T>& quaternion_T<T>::normalize()
{
	const T n = norm();
	x /= n;
	y /= n;
	z /= n;
	w /= n;
	return *this;
}

template <typename T>
constexpr quaternion_T<T>& quaternion_T<T>::clamp(quaternion_T<T> min,
                                                  quaternion_T<T> max)
{
	x = std::clamp(x, min.x, max.x);
	y = std::clamp(y, min.y, max.y);
	z = std::clamp(z, min.z, max.z);
	w = std::clamp(w, min.w, max.w);
	return *this;
}

template <typename T>
inline quaternion_T<T> quaternion_T<T>::get_inversed() const
{
	quaternion_T<T> res = *this;
	res.inverse();
	return res;
}

template <typename T>
constexpr quaternion_T<T> quaternion_T<T>::get_conjugated() const
{
	quaternion_T<T> res = *this;
	res.conjugate();
	return res;
}

template <typename T>
inline quaternion_T<T> quaternion_T<T>::get_normalized() const
{
	quaternion_T<T> res = *this;
	res.normalize();
	return res;
}

template <typename T>
constexpr quaternion_T<T> quaternion_T<T>::get_clamped(
    quaternion_T<T> min,
    quaternion_T<T> max) const
{
	quaternion_T<T> res = *this;
	res.clamp(min, max);
	return res;
}

template <typename T>
constexpr quaternion_T<T> quaternion_T<T>::operator+(quaternion_T<T> q) const
{
	return {
	    x + q.x,
	    y + q.y,
	    z + q.z,
	    w + q.w,
	};
}

template <typename T>
constexpr quaternion_T<T> quaternion_T<T>::operator-(quaternion_T<T> q) const
{
	return {
	    x - q.x,
	    y - q.y,
	    z - q.z,
	    w - q.w,
	};
}

template <typename T>
constexpr vector3_T<T> quaternion_T<T>::operator*(vector3_T<T> v) const
{
	const vector3_T<T> qvec{x, y, z};
	vector3_T<T> uv{cross(qvec, v)};
	vector3_T<T> uuv{cross(qvec, uv)};
	uv = uv * (T(2) * w);
	uuv = uuv * T(2);
	return v + uv + uuv;
}

template <typename T>
constexpr quaternion_T<T> quaternion_T<T>::operator*(quaternion_T<T> q) const
{
	return {
	    x * q.w + y * q.z - z * q.y + w * q.x,
	    -x * q.z + y * q.w + z * q.x + w * q.y,
	    x * q.y - y * q.x + z * q.w + w * q.z,
	    -x * q.x - y * q.y - z * q.z + w * q.w,
	};
}

template <typename T>
constexpr quaternion_T<T> quaternion_T<T>::operator*(T f) const
{
	return {
	    x * f,
	    y * f,
	    z * f,
	    w * f,
	};
}

template <typename T>
constexpr quaternion_T<T> quaternion_T<T>::operator/(T f) const
{
	return {
	    x / f,
	    y / f,
	    z / f,
	    w / f,
	};
}

template <typename T>
constexpr quaternion_T<T>& quaternion_T<T>::operator+=(quaternion_T<T> q)
{
	*this = *this + q;
	return *this;
}

template <typename T>
constexpr quaternion_T<T>& quaternion_T<T>::operator-=(quaternion_T<T> q)
{
	*this = *this - q;
	return *this;
}

template <typename T>
constexpr quaternion_T<T>& quaternion_T<T>::operator*=(quaternion_T<T> q)
{
	*this = *this * q;
	return *this;
}

template <typename T>
constexpr quaternion_T<T>& quaternion_T<T>::operator*=(T f)
{
	*this = *this * f;
	return *this;
}

template <typename T>
constexpr quaternion_T<T>& quaternion_T<T>::operator/=(T f)
{
	*this = *this / f;
	return *this;
}

template <typename T>
constexpr quaternion_T<T> quaternion_T<T>::operator-() const
{
	return {
	    -x,
	    -y,
	    -z,
	    -w,
	};
}

template <typename T>
constexpr bool quaternion_T<T>::operator==(quaternion_T<T> q) const
{
	return x == q.x &&  //
	       y == q.y &&  //
	       z == q.z &&  //
	       w == q.w;    //
}

template <typename T>
constexpr bool quaternion_T<T>::operator!=(quaternion_T<T> q) const
{
	return !operator==(q);
}

template <typename T>
constexpr vector3_T<T> operator*(const normalized<quaternion_T<T>>& q,
                                 vector3_T<T> v)
{
	return *q * v;
}

template <typename T>
constexpr T dot(quaternion_T<T> lhs, quaternion_T<T> rhs)
{
	return lhs.x * rhs.x +  //
	       lhs.y * rhs.y +  //
	       lhs.z * rhs.z +  //
	       lhs.w * rhs.w;   //
}

template <typename T>
constexpr quaternion_T<T> cross(quaternion_T<T> lhs, quaternion_T<T> rhs)
{
	return {
	    lhs.y * rhs.z - lhs.z * rhs.y,  //
	    lhs.z * rhs.x - lhs.x * rhs.z,  //
	    lhs.x * rhs.y - lhs.y * rhs.x,  //
	    T(1)                            //
	};
}

template <typename T>
constexpr quaternion_T<T> lerp(quaternion_T<T> begin,
                               quaternion_T<T> end,
                               T percent)
{
	return (end - begin) * percent + begin;
}

template <typename T>
inline quaternion_T<T> nlerp(quaternion_T<T> begin,
                             quaternion_T<T> end,
                             T percent)
{
	return lerp(begin, end, percent).get_normalized();
}

template <typename T>
inline quaternion_T<T> slerp(quaternion_T<T> begin,
                             quaternion_T<T> end,
                             T percent)
{
	quaternion_T<T> _end;
	T d = dot(begin, end);

	if (d > 0.9995f)
		return lerp(begin, end, percent);
	if (d < T(0))
	{
		_end = -end;
		d = -d;
	}
	else
		_end = end;

	percent = cdm::element_wise_clamp(percent, T(0), T(1));
	d = cdm::element_wise_clamp(d, T(-1), T(1));
	T theta = acos(d) * percent;

	quaternion_T<T> res = begin * d;
	res = _end - res;

	res = begin * cos(theta) + res * sin(theta);

	return res;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, quaternion_T<T> q)
{
	const auto flags = os.flags();
	const auto w = std::setw(13);
	os << std::right;
	// clang-format off
	os << "quaternion_T({" << w << q.x << ", " << w << q.y << ", " << w << q.z << "}, " << w << q.w << ")";
	// clang-format on
	os.setf(flags);
	return os;
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_QUATERNION_HPP
