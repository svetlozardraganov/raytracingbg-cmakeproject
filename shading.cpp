#include "shading.h"

Vector lightPos;
Color lightColor;
float lightPower;

extern bool testVisibility(const Vector& from, const Vector& to);

Shader::Shader(const Color& color)
{
	this->color = color;
}

Color Checker::getTexColor(const Ray ray, double u, double v, Vector& normal)
{
	// example - u = 150, -230
	// -> 1, -3
	int x = floor(u / size);
	int y = floor(v / size);
	int white = (x + y) % 2;
	Color result = white ? color2 : color1;
	return result;
}


Color Lambert::shade(Ray ray, const IntersectionData& data)
{
	Color diffuseColor = this->color;
	
	Vector N = data.normal;
	if (texture) diffuseColor = texture->getTexColor(ray, data.u, data.v, N);

	Color lightContrib(0, 0, 0);

	if (testVisibility(data.p + data.normal * 1e-6, lightPos))
	{
		Vector lightDir = lightPos - data.p;
		lightDir.normalize();

		double cosTheta = dot(lightDir, data.normal);

		lightContrib += lightColor * lightPower / (data.p - lightPos).lengthSqr();
		lightContrib = lightContrib * cosTheta;
	}

	
	return diffuseColor *lightContrib;
}
