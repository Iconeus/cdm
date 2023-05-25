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

#ifndef CDM_MATHS_IMPL_LINE2_HPP
#define CDM_MATHS_IMPL_LINE2_HPP 1

#include <cdm/decl/maths/line2.hpp>
#include <cdm/decl/maths/vector2.hpp>

namespace cdm
{
template <typename T>
line2_T<T, line_representation::SlopeIntercept>::line2_T(T s, T yi)
    : slope(s), y_intercept(yi)
{
}
template <typename T>
line2_T<T, line_representation::SlopeIntercept>::line2_T(
    vector2_T<T> direction,
    T e)
    : y_intercept(T(0))
{
	direction.normalize();

	if (nearly_equal(direction.y, T(1), e) ||
	    nearly_equal(direction.y, T(-1), e))
		throw std::runtime_error(
		    "this line can not be represented with this structure");

	// project the direction on the X axis
	const T d = dot(direction, vector2_T<T>(T(1), T(0)));

	// clang-format off
	//                       
	//   |                   
	//   |             +     
	//   |             |     
	//   |           /       
	//   |             |     
	//   |         /         
	//   |             |     
	//   |       /           
	//   |             |     
	//   |   v /             
	//   |    +        |     
	//   |   /|              
	//   |  /          |     
	//   | /  |              
	//   |/            |     
	// --+----+--------+---- 
	//   |0    d        1    
	// / |                   
	//   |                   
	//
	// clang-format on

	// adjust the vector's length so that x == 1
	direction = direction / d;
	// y is now the coefficient

	slope = direction.y;
}
template <typename T>
line2_T<T, line_representation::SlopeIntercept>::line2_T(vector2_T<T> point1,
                                                         vector2_T<T> point2)
{
	slope = (point2.y - point1.y) / (point2.x - point1.x);
	y_intercept = slope * (-point1.x) + point1.y;
}

template <typename T>
vector2_T<T> line2_T<T, line_representation::SlopeIntercept>::resolve_for_x(
    T x) const
{
	return {x, slope * x + y_intercept};
}
template <typename T>
vector2_T<T> line2_T<T, line_representation::SlopeIntercept>::resolve_for_y(
    T y) const
{
	return {(y - y_intercept) / slope, y};
}

template <typename T>
bool are_parallel(line2_T<T, line_representation::SlopeIntercept> l1,
                  line2_T<T, line_representation::SlopeIntercept> l2,
                  T e)
{
	return nearly_equal(l1.coefficient, l2.coefficient, e);
}

template <typename T>
bool collides(line2_T<T, line_representation::SlopeIntercept> l1,
              line2_T<T, line_representation::SlopeIntercept> l2)
{
	return !are_parallel(l1, l2);
}

template <typename T>
bool collides(line2_T<T, line_representation::SlopeIntercept> l1,
              line2_T<T, line_representation::SlopeIntercept> l2,
              vector2_T<T>& intersection)
{
	bool collision = collides(l1, l2);

	if (collision)
	{
		T a = l1.coefficient - l2.coefficient;
		T b = l2.offset - l1.offset;
		intersection.x = b / a;
		intersection.y = l1.coefficient * intersection.x + l1.offset;

		assert(intersection.y ==
		       (l2.coefficient * intersection.x + l2.offset));
	}

	return collision;
}

template <typename T>
line2_T<T, line_representation::Points>::line2_T(vector2_T<T> point1,
                                                 vector2_T<T> point2)
    : p1(point1), p2(point2)
{
}

// template <typename T>
// vector2_T<T> line2_T<T, line_representation::Points>::resolve_for_x(T x)
// const
//{
//	const auto direction = from_to(p1, p2).get_normalized();
//
//
// }
// template <typename T>
// vector2_T<T> line2_T<T, line_representation::Points>::resolve_for_y(T y)
// const
//{
// }

template <typename T>
void collides(line2_T<T, line_representation::Points> l1,
              line2_T<T, line_representation::Points> l2,
              vector2_T<T>& intersection)
{
	const T x1 = l1.p1.x;
	const T x2 = l1.p2.x;
	const T x3 = l2.p1.x;
	const T x4 = l2.p2.x;
	const T y1 = l1.p1.y;
	const T y2 = l1.p2.y;
	const T y3 = l2.p1.y;
	const T y4 = l2.p2.y;

	return {
	    ((x1 * y1 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * x4 - y3 * x4)) /
	        ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)),
	    ((x1 * y1 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * x4 - y3 * x4)) /
	        ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4))};
}

template <typename T>
T distance_between(plane_T<T> p, vector3_T<T> point)
{
	// clang-format off
	return -point.x * p.normal->x
	       -point.y * p.normal->y
	       -point.z * p.normal->z;
	// clang-format on
}
template <typename T>
T distance_between(vector3_T<T> v, plane_T<T> p)
{
	return distance_between(p, v);
}
}  // namespace cdm

#endif  // CDM_MATHS_IMPL_LINE2_HPP
