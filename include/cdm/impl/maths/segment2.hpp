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

#ifndef CDM_MATHS_IMPL_SEGMENT2_HPP
#define CDM_MATHS_IMPL_SEGMENT2_HPP 1

#include <cdm/decl/maths/plane.hpp>
#include <cdm/decl/maths/vector2.hpp>

#include <ostream>

namespace cdm
{
template <typename T>
inline T segment2_T<T>::length() const
{
	return distance_between(origin, end);
}

template <typename T>
constexpr T segment2_T<T>::length_squared() const
{
	return distance_squared_between(origin, end);
}

template <typename T>
constexpr segment2_T<T>& segment2_T<T>::invert()
{
	std::swap(origin, end);
	return *this;
}

template <typename T>
inline int collides(const segment2_T<T>& s0,
                    const segment2_T<T>& s1,
                    vector2_T<T>& outPoint0,
                    vector2_T<T>& outPoint1,
                    T e)
{
	auto det = [](T a, T b, T c, T d) -> T { return a * d - b * c; };

	auto betw = [&](T l, T r, T x) -> T
	{ return std::min(l, r) <= x + e && x <= std::max(l, r) + e; };

	auto intersect_1d = [&](T a, T b, T c, T d) -> bool
	{
		if (a > b)
			std::swap(a, b);
		if (c > d)
			std::swap(c, d);
		return std::max(a, c) <= std::min(b, d) + e;
	};

	auto compareP = [&](const cdm::vector2_T<T>& l,
	                    const cdm::vector2_T<T>& r) -> bool
	{ return l.x < r.x - e || (std::abs(l.x - r.x) < e && l.y < r.y - e); };

	vector2_T<T> a = s0.origin;
	vector2_T<T> b = s0.end;
	vector2_T<T> c = s1.origin;
	vector2_T<T> d = s1.end;
	if (!intersect_1d(a.x, b.x, c.x, d.x) || !intersect_1d(a.y, b.y, c.y, d.y))
		return 0;

	struct line
	{
		T a, b, c;

		line() = default;
		line(const cdm::vector2_T<T>& p, const cdm::vector2_T<T>& q)
		{
			a = p.y - q.y;
			b = q.x - p.x;
			c = -a * p.x - b * p.y;
			norm();
		}

		void norm()
		{
			T z = sqrt(a * a + b * b);
			if (nearly_equal(std::abs(z), T(0)))
			{
				a /= z;
				b /= z;
				c /= z;
			}
		}

		T dist(const cdm::vector2_T<T>& p) const
		{
			return a * p.x + b * p.y + c;
		}
	};

	line m(a, b);
	line n(c, d);
	T zn = det(m.a, m.b, n.a, n.b);
	if (abs(zn) < e)
	{
		if (abs(m.dist(c)) > e || abs(n.dist(a)) > e)
			return 0;
		if (compareP(b, a))
			std::swap(a, b);
		if (compareP(d, c))
			std::swap(c, d);

		if (compareP(a, c))
			outPoint0 = c;
		else
			outPoint0 = a;

		if (compareP(b, d))
			outPoint1 = b;
		else
			outPoint1 = d;

		return outPoint0 == outPoint1 ? 1 : 2;
	}
	else
	{
		outPoint0.x = outPoint1.x = -det(m.c, m.b, n.c, n.b) / zn;
		outPoint0.y = outPoint1.y = -det(m.a, m.c, n.a, n.c) / zn;
		return int(betw(a.x, b.x, outPoint0.x) &&
		           betw(a.y, b.y, outPoint0.y) &&
		           betw(c.x, d.x, outPoint0.x) && betw(c.y, d.y, outPoint0.y));
	}
}

// https://stackoverflow.com/a/565282
template <typename T>
constexpr std::optional<vector2_T<T>> intersects(segment2_T<T> s0,
                                                 segment2_T<T> s1,
                                                 T e)
{
	constexpr vector2_T<T> p = s0.origin;
	constexpr vector2_T<T> q = s1.origin;
	constexpr vector2_T<T> r = from_to(p, s0.end);
	constexpr vector2_T<T> s = from_to(q, s1.end);

	constexpr vector2_T<T> qmp = q - p;

	constexpr T rcs = cross(r, s);

	if constexpr (nearly_equal(rcs, T(0), e))  // coline_Tar
	{
		if constexpr (nearly_equal(cross(qmp, r), T(0),
		                           e))  // same line_T, different segments
		{
			constexpr T invrdr = T(1) / dot(r, r);
			constexpr T t0 = dot(qmp, r) * invrdr;
			constexpr T t1 = dot(qmp + s, r) * invrdr;

			if constexpr (dot(s, r) < T(0))
				std::swap(t0, t1);

			if constexpr (t0 <= T(1) && t0 >= T(0) || t1 <= T(1) && t1 >= T(0))
			{
				return s0.origin;  /// TODO: better than that
			}
			else
				return std::nullopt;
		}
		else  // parallel, non-intersecting
		{
			return std::nullopt;
		}
	}
	else
	{
		constexpr T invrcs = T(1) / rcs;

		constexpr T t = cross(qmp, s) * invrcs;
		constexpr T u = cross(qmp, r) * invrcs;

		if constexpr (t >= T(0) && t <= T(1) && u >= T(0) &&
		              u <= T(1))  // intersects
		{
			return p + r * t;
		}
		else
		{
			return std::nullopt;
		}
	}
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, segment2_T<T> t)
{
	// clang-format off
	return os << "segment2_T(origin = " << t.origin << ",\n"
	          << "           end =    " << t.end << ")";
	// clang-format on
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_SEGMENT2_HPP
