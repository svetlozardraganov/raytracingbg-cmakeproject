#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "vector.h"

struct IntersectionData {
	Vector p;
	Vector normal;
	double dist;
	
	double u, v;
};


class Geometry {
public:
	virtual ~Geometry() {}
	
	virtual bool intersect(Ray ray, IntersectionData& data) = 0;
};

class Plane: public Geometry {
	double y;
public:
	Plane(double _y) { y = _y; }
	
	bool intersect(Ray ray, IntersectionData& data);
};


class MyPlane : public Geometry {
	Vector p0_plane_point;
	Vector n_plane_normal;
public:
	MyPlane(Vector _p0_plane_point, Vector _n_plane_normal)
	{
		p0_plane_point = _p0_plane_point;
		n_plane_normal = _n_plane_normal;
	}

	bool intersect(Ray ray, IntersectionData& data);
};


class Sphere : public Geometry {
	Vector center;
	double radius;
public:
	Sphere(Vector _center, double _radius)
	{
		center = _center;
		radius = _radius;
	}

	bool intersect(Ray ray, IntersectionData& data);
};


class Shader;

class Node {
public:
	Geometry* geom;
	Shader* shader;
	
	Node() {}
	Node(Geometry* g, Shader* s) { geom = g; shader = s; }
};

#endif // __GEOMETRY_H__
