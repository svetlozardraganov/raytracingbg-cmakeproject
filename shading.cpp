#include "shading.h"

Vector lightPos;
Color lightColor;
float lightPower;

extern bool testVisibility(const Vector& from, const Vector& to);

Shader::Shader(const Color& color)
{
	this->color = color;
}

CheckerShader::CheckerShader(const Color& c1, const Color& c2, double size)
: Shader(c1)
{
	color2 = c2;
	this->size = size;
}


Color CheckerShader::shade(Ray ray, const IntersectionData& data)
{
	// example - u = 150, -230
	// -> 1, -3
	int x = floor(data.u / size);
	int y = floor(data.v / size);
	int white = (x + y) % 2;
	Color result = white ? color2 : color;
	
	Color lightContrib(0, 0, 0);

	if (testVisibility(data.p + data.normal * 1e-6, lightPos))
	{
		Vector lightDir = lightPos - data.p;
		lightDir.normalize();

		double cosTheta = dot(lightDir, data.normal);

		lightContrib += lightColor * lightPower / (data.p - lightPos).lengthSqr();
		lightContrib = lightContrib * cosTheta;
	}

	
	return result*lightContrib;
}
