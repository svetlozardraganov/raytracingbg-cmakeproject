#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "vector.h"

class Camera {
	Vector upLeft, upRight, downLeft;
public:
	Vector pos; // position
	double yaw, pitch, roll; // in degrees
	double fov; // in degrees
	double aspect; // 1.3 or ?
	
	void beginFrame(void);
	
	Ray getScreenRay(double x, double y);
	
};

#endif // __CAMERA_H__
