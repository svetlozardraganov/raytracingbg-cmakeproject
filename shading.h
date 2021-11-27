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

class CheckerShader: public Shader {
	Color color2;
	double size;
public:
	CheckerShader(const Color& c1, const Color& c2, double size = 1);
	Color shade(Ray ray, const IntersectionData& data);
};

#endif // __SHADING_H__
