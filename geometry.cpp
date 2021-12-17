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
		//data.u = data.p.x; //texture coordinates are not correct for planes not perpendicular to z-axis
		//data.v = data.p.z;

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


bool MyDisk::intersect(Ray ray, IntersectionData& data)
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

		if ((p0_plane_point - data.p).length() > radius) return false; //if intersectin point is greater than disk-radius


		float dist = (l_0_point_on_line - data.p).length(); //distance from ray.start to intersection point

		if (dist > data.dist || dist <= 0)//check if plane intercection point is closer to any previously calculated intercetion points
		{
			return false;
		}

		data.dist = dist;


		//UV coordinate calcualtion
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


bool MySquare::intersect(Ray ray, IntersectionData& data)
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


		float d = dot(p0_plane_point - l_0_point_on_line, n_plane_normal) / dot(l_line_direction, n_plane_normal); //value to multiple ray.dir to reach intersection point with the plane
		if (d < 0) return false;

		//cout << "d=" << d << endl;
		data.p = l_0_point_on_line + d * l_line_direction; //intersection point on plane found
		data.normal = n_plane_normal; //intersection point normal


		float dist = (l_0_point_on_line - data.p).length(); //distance from camera to intersection point

		if (dist > data.dist || dist <= 0)//check if plane intercection point is closer to any previously calculated intersection points
		{
			return false;
		}

		data.dist = dist;

		//UV coordinates calculation
		//https://gamedev.stackexchange.com/questions/172352/finding-texture-coordinates-for-plane
		Vector N = normalizing(n_plane_normal);
		Vector vector_basis_e1 = normalizing(N ^ Vector(1, 0, 0));

		//If normal and (1,0,0) are parallel, change e1
		if (vector_basis_e1.x == 1 && vector_basis_e1.y == 0 && vector_basis_e1.z == 0)
		{
			vector_basis_e1 = normalizing(N ^ Vector(0, 0, 1));
		}

		Vector vector_basis_e2 = normalizing(N ^ vector_basis_e1);
		data.u = dot(vector_basis_e1, data.p); //p0_plane_point.z added because the plane is moved in z-direction
		data.v = dot(vector_basis_e2, data.p);

		//cout << "data.u=" << data.u << endl;
		//cout << "data.v=" << data.v << endl; //horizontal coordinata
		//cout << "this.x=" << this->p0_plane_point.x << endl;
		//cout << "this.y=" << this->p0_plane_point.y << endl;
		//cout << "this.z=" << this->p0_plane_point.z << endl;


		//check if data.p is in the square
		//if (data.p.x > p0_plane_point.x + side) return false; //if intersectin point is greater than disk-radius
		//if (data.p.x < p0_plane_point.x - side) return false;
		//if (data.p.z > p0_plane_point.z + side) return false; //if intersectin point is greater than disk-radius
		//if (data.p.z < p0_plane_point.z - side) return false;
		//if (data.p.z > side) return false; //if intersectin point is greater than disk-radius

		if (abs(data.u) > side) return false;//if intersectin point is greater than square side
		if (abs(data.v) > side) return false;

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

bool MyElipse::intersect(Ray ray, IntersectionData& data) {
	//Page 144 Mathematics for 3D game programming and computer graphics

	Vector H = ray.start - center;

	double a = ray.dir.x * ray.dir.x + m * m * ray.dir.y * ray.dir.y + n * n * ray.dir.z * ray.dir.z;

	double b = 2 * (ray.dir.x * H.x + m * m * ray.dir.y * H.y + n * n * ray.dir.z * H.z);
	double c = H.x * H.x + m * m * H.y * H.y + n * n * H.z * H.z - radius * radius;
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


bool MyCylinder::intersect(Ray ray, IntersectionData& data) {
	//Page 145 Mathematics for 3D game programming and computer graphics

	Vector S = ray.start-center;
	Vector V = ray.dir;

	double a = V.x * V.x + V.z * V.z;
	double b = 2*(S.x * V.x + S.z * V.z);
	double c = S.x * S.x + S.z * S.z - radius * radius;

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

	if (data.p.y > height || data.p.y < 0) return false; //check cylinder height 

	data.normal = Vector(data.p.x - center.x, 0, data.p.z - center.z);
	data.normal.normalize();

	return true;




}

bool MySphere::intersect(Ray ray, IntersectionData& data)
{
	//https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection

	double L_lenght = (this->center - ray.start).length(); //distance to spheres center
	Vector L_vector = this->center - ray.start; //vector from camera to spheres center

	double Tca = dot(L_vector, ray.dir); //lenght of projection of L_vector to ray.dir
	if (Tca < 0) return false; //if Tca < 0 the intersection is behind the camera

	double d = sqrt(L_lenght * L_lenght - Tca * Tca); //distance(perpendicular) from spheres center to ray.dir
	if (d < 0) return false;
	if (d > this->radius) return false; //if distance to ray.dir is greater than radius, sphere is not hit

	double Thc = sqrt(radius * radius - d * d); //distance from intersection point of ray.dir and perpendicular to sphere center
	double T0 = Tca - Thc; //distance from ray.start to spheres front intersection point
	double T1 = Tca + Thc; //distance from ray.start to spheres back intersection point (not used)

	data.p = ray.start + T0 * ray.dir; //vector to front intersection point
	data.normal = data.p - center;//intersection point normal
	data.normal.normalize();
	double dist = data.p.length(); //distance from camera to spheres front intersection point

	if (dist > data.dist) return false; //check if the intersection point is closer to previous closest intersection point

	data.dist = dist;

	return true;

	



}

bool MyCube::intersect(Ray ray, IntersectionData& data) {

	//https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
	// 
	//define cube bouding box
	double x_min = center.x - side; //bounding box minimum x-value
	double x_max = center.x + side; //bounding box maximum x-value

	double tmin = (x_min - ray.start.x) / ray.dir.x; //cube x-minimum intersection point
	double tmax = (x_max - ray.start.x) / ray.dir.x; //cube x-maximum intersection point
	

	if (tmin > tmax) {
		swap(tmin, tmax);
	}

	
	///////////////////////////////////////////////////////////////////////////////////////

	double y_min = center.y - side; //bounding box minimum y-value
	double y_max = center.y + side; //bounding box maximum y-value

	double tymin = (y_min - ray.start.y) / ray.dir.y; //cube y-minimum intersection point
	double tymax = (y_max - ray.start.y) / ray.dir.y; //cube y-maximum intersection point

	if (tymin > tymax) swap(tymin, tymax);

	if ((tmin > tymax) || (tymin > tmax))
		return false;

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	////////////////////////////////////////////////////////////////////////////////////////
	
	double z_min = center.z - side; //bounding box minimum z-value
	double z_max = center.z + side; //bounding box maximum z-value

	
	double tzmin = (z_min - ray.start.z) / ray.dir.z;	//cube z-minimum intersection point
	double tzmax = (z_max - ray.start.z) / ray.dir.z;	//cube z-maximum intersection point

	
	if (tzmin > tzmax) swap(tzmin, tzmax);

	if ((tmin > tzmax) || (tzmin > tmax))
		return false;

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;
		

	return true;


}