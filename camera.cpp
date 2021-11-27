#include "camera.h"
#include "matrix.h"
#include "util.h"
#include "sdl.h"
#include <iostream>
using namespace std;

void Camera::beginFrame(void)
{
    //initial camera-grid parameters
	double x = -aspect;
	cout << "x=" << x << "\n";
	double y = +1;
	cout << "y=" << y << "\n";

	Vector corner = Vector(x, y, 1); //the up-left corner of the camera-grid with depth=1
	cout << "corner(x,y,z)=" << corner.x << ","<< corner.y << "," << corner.z << "\n";

	Vector center = Vector(0, 0, 1); //the center point of the camera-grid with depth=1
    cout << "center(x,y,z)=" << center.x << ","<< center.y << "," << center.z << "\n";

	double lenXY = (corner - center).length(); //the distance between corner and the center of the grid
	cout << "lenXY=" << lenXY << "\n";

	double wantedLength = tan(toRadians(fov / 2));
    cout << "fov=" << fov << "\n";
    cout << "wantedLength=" << wantedLength << "\n";

	double scaling = wantedLength / lenXY;
	cout << "scaling=" << scaling << "\n";

    //rescale x,y vectors to get the desired grid-size
	x *= scaling;
	cout << "x(scaling)=" << x << "\n";
	y *= scaling;
	cout << "y(scaling)=" << y << "\n";

    //calculate camera-grid corners
	this->upLeft = Vector(x, y, 1);
	cout << "this->upLeft(x,y,z)=" << this->upLeft.x << ","<< this->upLeft.y << "," << this->upLeft.z << "\n";
	this->upRight = Vector(-x, y, 1);
	cout << "this->upRight(x,y,z)=" << this->upRight.x << ","<< this->upRight.y << "," << this->upRight.z << "\n";
	this->downLeft = Vector(x, -y, 1);
	cout << "this->downLeft(x,y,z)=" << this->downLeft.x << ","<< this->downLeft.y << "," << this->downLeft.z << "\n";


    //rotate camera-grid to the desired location
	Matrix rotation = rotationAroundZ(toRadians(roll))
	                * rotationAroundX(toRadians(pitch))
	                * rotationAroundY(toRadians(yaw));
	upLeft *= rotation;
	cout << "upLeft(rotation)(x,y,z)=" << upLeft.x << ","<< upLeft.y << "," << upLeft.z << "\n";
	upRight *= rotation;
	cout << "upRight(rotation)(x,y,z)=" << upRight.x << ","<< upRight.y << "," << upRight.z << "\n";
	downLeft *= rotation;
	cout << "downLeft(rotation)(x,y,z)=" << downLeft.x << ","<< downLeft.y << "," << downLeft.z << "\n";
}

Ray Camera::getScreenRay(double x, double y)
{
	Ray result; // A, B -     C = A + (B - A) * x
	result.start = this->pos;
	Vector target0 = upLeft +
		(upRight - upLeft) * (x / (double) frameWidth()) +
		(downLeft - upLeft) * (y / (double) frameHeight());
	Vector target = target0 + this->pos;


	// A - camera; B = target
	result.dir = target - result.start;

	result.dir.normalize();

	if ((int)x % 100 == 0 && (int)y % 100 == 0)
	{
		cout << "getScreenRay:target(x,y,z)=" << target.x << "," << target.y << "," << target.z << endl;
	}
	
	return result;
}
