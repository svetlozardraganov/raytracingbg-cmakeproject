/***************************************************************************
 *   Copyright (C) 2009-2013 by Veselin Georgiev, Slavomir Kaslev et al    *
 *   admin@raytracing-bg.net                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "geometry.h"
#include "vector.h"
#include "constants.h"


bool Plane::intersect(Ray ray, IntersectionData& data)
{
	if (ray.dir.y >= 0) return false;
	else {
		double yDiff = ray.dir.y;
		double wantYDiff = ray.start.y - this->y;
		double mult = wantYDiff / -yDiff;
		data.p = ray.start + ray.dir * mult;

		if (mult > data.dist) return false; //check if plane intercection point is closer to any previously calculated intercetion points

		data.dist = mult;
		data.normal = Vector(0, 1, 0);
		data.u = data.p.x;
		data.v = data.p.z;
		return true;
	}
}

bool Sphere::intersect(Ray ray, IntersectionData& data)
{
	Vector H = ray.start - center;
	
	double a = ray.dir.lengthSqr(); 

	double b = 2 * ray.dir * H;
	double c = H.lengthSqr() - radius * radius;
	//quadratic equation a*x*x + b*x + c = 0
	double Discriminant = b * b - 4 * a * c;

	if (Discriminant < 0)
	{
		return false; // no solutions to the quadratic equation
	}

	double x1 = (-b - sqrt(Discriminant)) / 2 * a;
	double x2 = (-b + sqrt(Discriminant)) / 2 * a;

	double solution = x1; //get the closed of the two solutions
	if (solution < 0)
	{
		solution = x2; //get the other solution since the first one is < 0
	}
	if (solution < 0)
	{
		return false; // both solutions are < 0 hence the intersection point is behind the camera
	}

	if (solution > data.dist) return false; //check if the intersection point is closer to previous closest intersection point

	data.dist = solution;
	data.p = ray.start + ray.dir * solution;
	data.normal = data.p - center;
	data.normal.normalize();
	
	data.u = (PI + atan2(data.p.z - center.z, data.p.x - center.x)) / (2 * PI);
	data.v = 1.0 - (PI / 2 + asin((data.p.y - center.y) / radius)) / PI;
	return true;
}