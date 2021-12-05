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
	//https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection
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
		data.u = data.p.x; //texture coordinates are not correct for planes not perpendicular to z-axis
		data.v = data.p.z;

		//cout << "MyPlane::intersect=" << data.p.x << "," << data.p.y << "," << data.p.z << endl;

		//https://computergraphics.stackexchange.com/questions/8382/how-do-i-convert-a-hit-on-an-infinite-plane-to-uv-coordinates-for-texturing-in-a

		//Vector a = n_plane_normal ^ Vector(1, 0, 0);
		//Vector b = n_plane_normal ^ Vector(0, 1, 0);

		//Vector max_ab = dot(a, a) < dot(b, b) ? b : a;

		//Vector c = n_plane_normal ^ Vector(0, 0, 1);
		//
		//Vector result = dot(max_ab, max_ab) < dot(c, c) ? c : max_ab;
		//data.u = result.normalize();
		//data.v = n_plane_normal ^ data.u;

		//https://gamedev.stackexchange.com/questions/172352/finding-texture-coordinates-for-plane
		Vector N = normalizing(n_plane_normal);
		Vector vector_basis_e1 = normalizing(N ^ Vector(1, 0, 0));

		//If normal and (1,0,0) are parallel, change e1
		if (vector_basis_e1.x == 1 && vector_basis_e1.y == 0 && vector_basis_e1.z == 0)
		{
			vector_basis_e1 = normalizing(N ^ Vector(0, 0, 1));
		}

		Vector vector_basis_e2 = normalizing(N ^ vector_basis_e1);
		data.u = dot(vector_basis_e1, data.p);
		data.v = dot(vector_basis_e2, data.p);


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