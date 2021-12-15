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


class MyDisk : public Geometry {
	Vector p0_plane_point;
	Vector n_plane_normal;
	double radius;
public:
	MyDisk(Vector _p0_plane_point, Vector _n_plane_normal, double _radius)
	{
		p0_plane_point = _p0_plane_point;
		n_plane_normal = _n_plane_normal;
		radius = _radius;
	}

	bool intersect(Ray ray, IntersectionData& data);
};

class MySquare : public Geometry {
	Vector p0_plane_point;
	Vector n_plane_normal;
	double side;
public:
	MySquare(Vector _p0_plane_point, Vector _n_plane_normal, double _side)
	{
		p0_plane_point = _p0_plane_point;
		n_plane_normal = _n_plane_normal;
		side = _side;
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



class MySphere : public Geometry {
	Vector center;
	double radius;
public:
	MySphere(Vector _center, double _radius)
	{
		center = _center;
		radius = _radius;
	}

	bool intersect(Ray ray, IntersectionData& data);
};


class MyElipse : public Geometry {
	Vector center;
	double radius;
	double m; // ratio of x-semiaxis lenght to the y-semiaxist lenght
	double n; // ratio of x-semiaxis lenght to the z-semiaxist lenght
public:
	MyElipse(Vector _center, double _radius, double _m, double _n) {
		center = _center;
		radius = _radius;
		m = _m;
		n = _n;
	}

	bool intersect(Ray ray, IntersectionData& data);
};


class MyCylinder : public Geometry {
	Vector center;
	double radius;
	double height;
public:
	MyCylinder(Vector _center, double _radius, double _height) {
		center = _center;
		radius = _radius;
		height = _height;
	}

	bool intersect(Ray ray, IntersectionData& data);
};


class MyCube:public Geometry {
	Vector center;
	double side;
public:
	MyCube(Vector _center, double _side) {
		center = _center;
		side = _side;
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
