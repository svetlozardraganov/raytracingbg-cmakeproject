#include "geometry.h"
#include "vector.h"
#include "constants.h"
#include <iostream>
using namespace std;


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

bool MyPlane::intersect(Ray ray, IntersectionData& data)
{

	Vector l_line_direction = ray.dir;
	Vector l_0_point_on_line = ray.start;


	if (dot(l_line_direction, n_plane_normal) == 0) //line perpendicular to plane
	{
		return false;
	}

	if (dot(p0_plane_point - l_0_point_on_line, n_plane_normal) == 0) //the plane contains the line
	{
		return false;
	}

	if (dot(l_line_direction, n_plane_normal) != 0) // line intersect the plane in point p
	{
		

		float d = dot(p0_plane_point - l_0_point_on_line, n_plane_normal) / dot(l_line_direction, n_plane_normal);
		if (d < 0) return false;

		//cout << "d=" << d << endl;
		data.p = l_0_point_on_line + d * l_line_direction;
		data.normal = n_plane_normal;

		float dist = (l_0_point_on_line - data.p).length();

		if (dist > data.dist || dist<=0)//check if plane intercection point is closer to any previously calculated intercetion points
		{
			return false;
		}

		data.dist = dist;

		//cout << "MyPlane::intersect=" << data.p.x << "," << data.p.y << "," << data.p.z << endl;

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