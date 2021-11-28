#ifndef __SHADING_H__
#define __SHADING_H__

#include "color.h"
#include "vector.h"
#include "geometry.h"

extern Vector lightPos;
extern Color lightColor;
extern float lightPower;


class Shader {
protected:
	Color color;
public:
	Shader(const Color& color);
	virtual ~Shader() {}

	virtual Color shade(Ray ray, const IntersectionData& data) = 0;
};

class Texture {
public:
	virtual ~Texture() {}

	virtual Color getTexColor(const Ray ray, double u, double v, Vector& normal)=0;
};

class Checker:public Texture {
	Color color1, color2;
	double size;
public:
	Checker(const Color& color1, const Color& color2, double size = 1) :
		color1(color1), color2(color2), size(size) {}
	Color getTexColor(const Ray ray, double u, double v, Vector& normal);
};



class Lambert: public Shader {
	Texture* texture;
public:
	Lambert(const Color& diffuseColor, Texture* texture = NULL) :
		Shader(diffuseColor), texture(texture) {}
	Color shade(Ray ray, const IntersectionData& data);
};

class Phong : public Shader {
	Texture* texture;
	double exponent;
	float strenght;
public:
	Phong(const Color& diffuseColor, double exponent, float strenght = 1, Texture* texture = NULL):
		Shader(diffuseColor), exponent(exponent), strenght(strenght), texture(texture) {}
	Color shade(Ray ray, const IntersectionData& data);
};

#endif // __SHADING_H__