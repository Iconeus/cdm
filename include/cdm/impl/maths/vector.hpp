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

#ifndef CDM_MATHS_IMPL_VECTOR_HPP
#define CDM_MATHS_IMPL_VECTOR_HPP 1

#include <cdm/decl/maths/misc.hpp>
#include <cdm/decl/maths/vector.hpp>

#include <algorithm>
#include <cmath>
#include <ostream>

namespace cdm
{
template <typename T, template <typename> typename Vector>
constexpr T& get_x(Vector<T>& v)
{
	return v.x;
}

template <typename T, template <typename> typename Vector>
constexpr const T& get_x(const Vector<T>& v)
{
	return v.x;
}

template <typename T, template <typename> typename Vector>
constexpr T& get_y(Vector<T>& v)
{
	return v.y;
}

template <typename T, template <typename> typename Vector>
constexpr const T& get_y(const Vector<T>& v)
{
	return v.y;
}

template <typename T, template <typename> typename Vector>
constexpr T& get_z(Vector<T>& v)
{
	return v.z;
}

template <typename T, template <typename> typename Vector>
constexpr const T& get_z(const Vector<T>& v)
{
	return v.z;
}

template <typename T, template <typename> typename Vector>
constexpr T& get_w(Vector<T>& v)
{
	return v.w;
}

template <typename T, template <typename> typename Vector>
constexpr const T& get_w(const Vector<T>& v)
{
	return v.w;
}

template <typename T, template <typename> typename Vector>
constexpr T norm(const Vector<T>& v)
{
	if (std::is_constant_evaluated())
		return cdm::sqrt(norm_squared(v));
	else
		return std::sqrt(norm_squared(v));
}

template <typename T, template <typename> typename Vector>
constexpr T norm_squared(const Vector<T>& v)
{
	static_assert(Vector<T>::component_count == 2 ||
	              Vector<T>::component_count == 3 ||
	              Vector<T>::component_count == 4);

	if constexpr (Vector<T>::component_count == 2)
	{
		return get_x(v) * get_x(v) +  //
		       get_y(v) * get_y(v);   //
	}
	else if constexpr (Vector<T>::component_count == 3)
	{
		return get_x(v) * get_x(v) +  //
		       get_y(v) * get_y(v) +  //
		       get_z(v) * get_z(v);   //
	}
	else if constexpr (Vector<T>::component_count == 4)
	{
		return get_x(v) * get_x(v) +  //
		       get_y(v) * get_y(v) +  //
		       get_z(v) * get_z(v) +  //
		       get_w(v) * get_w(v);   //
	}
}

template <typename T, template <typename> typename Vector>
constexpr Vector<T>& normalize(Vector<T>& v)
{
	static_assert(Vector<T>::component_count == 2 ||
	              Vector<T>::component_count == 3 ||
	              Vector<T>::component_count == 4);

	T n = norm(v);

	if constexpr (Vector<T>::component_count == 2)
	{
		get_x(v) /= n;
		get_y(v) /= n;
	}
	else if constexpr (Vector<T>::component_count == 3)
	{
		get_x(v) /= n;
		get_y(v) /= n;
		get_z(v) /= n;
	}
	else if constexpr (Vector<T>::component_count == 4)
	{
		get_x(v) /= n;
		get_y(v) /= n;
		get_z(v) /= n;
		get_w(v) /= n;
	}

	return v;
}

template <typename T, template <typename> typename Vector>
constexpr Vector<T> get_normalized(const Vector<T>& v)
{
	Vector<T> res = v;
	normalize(res);
	return res;
}

template <typename T,
          template <typename>
          typename LVector,
          template <typename>
          typename RVector>
constexpr T dot(const LVector<T>& lhs, const RVector<T>& rhs)
{
	static_assert(LVector<T>::component_count == 2 ||
	              LVector<T>::component_count == 3 ||
	              LVector<T>::component_count == 4);
	static_assert(LVector<T>::component_count == RVector<T>::component_count ||
	              LVector<T>::component_count == RVector<T>::component_count ||
	              LVector<T>::component_count == RVector<T>::component_count);

	if constexpr (LVector<T>::component_count == 2)
	{
		return get_x(lhs) * get_x(rhs) +  //
		       get_y(lhs) * get_y(rhs);   //
	}
	else if constexpr (LVector<T>::component_count == 3)
	{
		return get_x(lhs) * get_x(rhs) +  //
		       get_y(lhs) * get_y(rhs) +  //
		       get_z(lhs) * get_z(rhs);   //
	}
	else if constexpr (LVector<T>::component_count == 4)
	{
		return get_x(lhs) * get_x(rhs) +  //
		       get_y(lhs) * get_y(rhs) +  //
		       get_z(lhs) * get_z(rhs) +  //
		       get_w(lhs) * get_w(rhs);   //
	}
}

template <typename T, template <typename> typename Vector>
constexpr Vector<T> cross(const Vector<T>& lhs, const Vector<T>& rhs)
{
	static_assert(Vector<T>::component_count == 3);

	return {
	    get_y(lhs) * get_z(rhs) - get_z(lhs) * get_y(rhs),
	    get_z(lhs) * get_x(rhs) - get_x(lhs) * get_z(rhs),
	    get_x(lhs) * get_y(rhs) - get_y(lhs) * get_x(rhs),
	};
}

template <typename T, template <typename> typename Vector>
constexpr Vector<T> lerp(const Vector<T>& begin,
                         const Vector<T>& end,
                         const normalized_value_T<T>& alpha)
{
	return (end - begin) * alpha.value() + begin;
}

template <typename T, template <typename> typename Vector>
constexpr Vector<T> nlerp(const Vector<T>& begin,
                          const Vector<T>& end,
                          const normalized_value_T<T>& alpha)
{
	return normalize(lerp(begin, end, alpha));
}

template <typename T, template <typename> typename Vector>
    requires vector<Vector<T>>
constexpr Vector<T>& element_wise_clamp(Vector<T>& v,
                                        const Vector<T>& min,
                                        const Vector<T>& max)
{
	static_assert(Vector<T>::component_count == 2 ||
	              Vector<T>::component_count == 3 ||
	              Vector<T>::component_count == 4);

	if constexpr (Vector<T>::component_count == 2)
	{
		get_x(v) = std::clamp(get_x(v), get_x(min), get_x(max));
		get_y(v) = std::clamp(get_y(v), get_y(min), get_y(max));
	}
	else if constexpr (Vector<T>::component_count == 3)
	{
		get_x(v) = std::clamp(get_x(v), get_x(min), get_x(max));
		get_y(v) = std::clamp(get_y(v), get_y(min), get_y(max));
		get_z(v) = std::clamp(get_z(v), get_z(min), get_z(max));
	}
	else if constexpr (Vector<T>::component_count == 4)
	{
		get_x(v) = std::clamp(get_x(v), get_x(min), get_x(max));
		get_y(v) = std::clamp(get_y(v), get_y(min), get_y(max));
		get_z(v) = std::clamp(get_z(v), get_z(min), get_z(max));
		get_w(v) = std::clamp(get_w(v), get_w(min), get_w(max));
	}

	return v;
}

template <typename T, template <typename> typename Vector>
    requires vector<Vector<T>>
constexpr Vector<T> get_element_wise_clamped(const Vector<T>& v,
                                             const Vector<T>& min,
                                             const Vector<T>& max)
{
	Vector<T> res = v;
	element_wise_clamp(res, min, max);
	return res;
}

template <typename T, template <typename> typename Vector>
constexpr T distance_between(const Vector<T>& v0, const Vector<T>& v1)
{
	return norm(v0 - v1);
}

template <typename T, template <typename> typename Vector>
constexpr T distance_squared_between(const Vector<T>& v0, const Vector<T>& v1)
{
	return norm_squared(v0 - v1);
}

template <typename T, template <typename> typename Vector>
constexpr Vector<T> from_to(const Vector<T>& from, const Vector<T>& to)
{
	return to - from;
}

template <typename T, template <typename> typename Vector>
inline radian_T<T> angle_between(const Vector<T>& v0, const Vector<T>& v1)
{
	const T divisor = std::sqrt(norm_squared(v0) * norm_squared(v1));
	const T alpha = dot(v0, v1) / divisor;
	return radian_T<T>(std::acos(std::clamp(alpha, T(-1), T(1))));
}

template <typename T, template <typename> typename Vector>
inline radian_T<T> angle_around_axis(const Vector<T>& v0,
                                     const Vector<T>& v1,
                                     const direction3_T<T>& axis)
{
	const Vector<T> c = cross(v0, v1);
	const auto angle = std::atan2(c.norm(), dot(v0, v1));
	return radian_T<T>{dot(c, Vector<T>(axis)) < T(0) ? T(-angle) : T(angle)};
}

template <typename T, template <typename> typename Vector>
constexpr bool nearly_equal(const Vector<T>& v0, const Vector<T>& v1, T e)
{
	static_assert(Vector<T>::component_count == 2 ||
	              Vector<T>::component_count == 3 ||
	              Vector<T>::component_count == 4);

	if constexpr (Vector<T>::component_count == 2)
	{
		return nearly_equal(get_x(v0), get_x(v1), e) &&  //
		       nearly_equal(get_y(v0), get_y(v1), e);
	}
	else if constexpr (Vector<T>::component_count == 3)
	{
		return nearly_equal(get_x(v0), get_x(v1), e) &&  //
		       nearly_equal(get_y(v0), get_y(v1), e) &&  //
		       nearly_equal(get_z(v0), get_z(v1), e);
	}
	else if constexpr (Vector<T>::component_count == 4)
	{
		return nearly_equal(get_x(v0), get_x(v1), e) &&  //
		       nearly_equal(get_y(v0), get_y(v1), e) &&  //
		       nearly_equal(get_z(v0), get_z(v1), e) &&  //
		       nearly_equal(get_w(v0), get_w(v1), e);
	}
}

template <typename T, template <typename> typename Vector>
constexpr Vector<T> element_wise_min(const Vector<T>& v0, const Vector<T>& v1)
{
	static_assert(Vector<T>::component_count == 2 ||
	              Vector<T>::component_count == 3 ||
	              Vector<T>::component_count == 4);

	if constexpr (Vector<T>::component_count == 2)
	{
		return {
		    std::min(get_x(v0), get_x(v1)),
		    std::min(get_y(v0), get_y(v1)),
		};
	}
	else if constexpr (Vector<T>::component_count == 3)
	{
		return {
		    std::min(get_x(v0), get_x(v1)),
		    std::min(get_y(v0), get_y(v1)),
		    std::min(get_z(v0), get_z(v1)),
		};
	}
	else if constexpr (Vector<T>::component_count == 4)
	{
		return {
		    std::min(get_x(v0), get_x(v1)),
		    std::min(get_y(v0), get_y(v1)),
		    std::min(get_z(v0), get_z(v1)),
		    std::min(get_w(v0), get_w(v1)),
		};
	}
}

template <typename T, template <typename> typename Vector>
constexpr Vector<T> element_wise_max(const Vector<T>& v0, const Vector<T>& v1)
{
	static_assert(Vector<T>::component_count == 2 ||
	              Vector<T>::component_count == 3 ||
	              Vector<T>::component_count == 4);

	if constexpr (Vector<T>::component_count == 2)
	{
		return {
		    std::max(get_x(v0), get_x(v1)),
		    std::max(get_y(v0), get_y(v1)),
		};
	}
	else if constexpr (Vector<T>::component_count == 3)
	{
		return {
		    std::max(get_x(v0), get_x(v1)),
		    std::max(get_y(v0), get_y(v1)),
		    std::max(get_z(v0), get_z(v1)),
		};
	}
	else if constexpr (Vector<T>::component_count == 4)
	{
		return {
		    std::max(get_x(v0), get_x(v1)),
		    std::max(get_y(v0), get_y(v1)),
		    std::max(get_z(v0), get_z(v1)),
		    std::max(get_w(v0), get_w(v1)),
		};
	}
}

template <typename T, template <typename> typename Vector>
inline Vector<T> element_wise_abs(const Vector<T>& v)
{
	static_assert(Vector<T>::component_count == 2 ||
	              Vector<T>::component_count == 3 ||
	              Vector<T>::component_count == 4);

	if constexpr (Vector<T>::component_count == 2)
	{
		return {
		    std::abs(get_x(v)),
		    std::abs(get_y(v)),
		};
	}
	else if constexpr (Vector<T>::component_count == 3)
	{
		return {
		    std::abs(get_x(v)),
		    std::abs(get_y(v)),
		    std::abs(get_z(v)),
		};
	}
	else if constexpr (Vector<T>::component_count == 4)
	{
		return {
		    std::abs(get_x(v)),
		    std::abs(get_y(v)),
		    std::abs(get_z(v)),
		    std::abs(get_w(v)),
		};
	}
}

template <typename T, template <typename> typename Vector>
constexpr Vector<T> element_wise_lerp(
    const Vector<T>& begin,
    const Vector<T>& end,
    const Vector<normalized_value_T<T>>& alpha)
{
	static_assert(Vector<T>::component_count == 2 ||
	              Vector<T>::component_count == 3 ||
	              Vector<T>::component_count == 4);

	if constexpr (Vector<T>::component_count == 2)
	{
		return {
		    std::lerp(get_x(begin), get_x(end), get_x(alpha).value()),
		    std::lerp(get_y(begin), get_y(end), get_y(alpha).value()),
		};
	}
	else if constexpr (Vector<T>::component_count == 3)
	{
		return {
		    std::lerp(get_x(begin), get_x(end), get_x(alpha).value()),
		    std::lerp(get_y(begin), get_y(end), get_y(alpha).value()),
		    std::lerp(get_z(begin), get_z(end), get_z(alpha).value()),
		};
	}
	else if constexpr (Vector<T>::component_count == 4)
	{
		return {
		    std::lerp(get_x(begin), get_x(end), get_x(alpha).value()),
		    std::lerp(get_y(begin), get_y(end), get_y(alpha).value()),
		    std::lerp(get_z(begin), get_z(end), get_z(alpha).value()),
		    std::lerp(get_w(begin), get_w(end), get_w(alpha).value()),
		};
	}
}

template <typename T, template <typename> typename Vector>
    requires vector<Vector<T>>
inline std::ostream& operator<<(std::ostream& os, Vector<T> v)
{
	static_assert(Vector<T>::component_count == 2 ||
	              Vector<T>::component_count == 3 ||
	              Vector<T>::component_count == 4);

	if constexpr (Vector<T>::component_count == 2)
		return os << "vector2(" << get_x(v) << ", " << get_y(v) << ")";
	else if constexpr (Vector<T>::component_count == 3)
		return os << "vector3(" << get_x(v) << ", " << get_y(v) << ", "
		          << get_z(v) << ")";
	else if constexpr (Vector<T>::component_count == 4)
		return os << "vector4(" << get_x(v) << ", " << get_y(v) << ", "
		          << get_z(v) << ", " << get_w(v) << ")";
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_VECTOR_HPP
