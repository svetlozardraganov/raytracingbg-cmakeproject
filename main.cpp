#include <SDL.h>
#include <vector>
#include "sdl.h"
#include "matrix.h"
#include "camera.h"
#include "geometry.h"
#include "shading.h"
#include "color.h"
#include <iostream>
using namespace std;

Color vfb[VFB_MAX_SIZE][VFB_MAX_SIZE]; //!< virtual framebuffer

Camera* camera;

//vector<Geometry*> geometries;
//vector<Shader*> shaders;
vector<Node*> nodes;



Color raytrace(Ray ray)
{
	IntersectionData data;
	Node* closestNode = NULL;
	data.dist = 1e99; //innitial value for infinity distance

	for (int i = 0; i < (int)nodes.size(); i++)
	{
		if (nodes[i]->geom->intersect(ray, data))
		{
			closestNode = nodes[i];
		}
	}

	if (!closestNode)
	{
		return Color(0.5, 0.5, 0.5);		//if there is no closestNode, hit the background
	}
	else
	{
		return closestNode->shader->shade(ray, data);	//if there is closestNode, calculate it's material
	}

}

bool testVisibility(const Vector& from, const Vector& to)
{
	Ray ray;
	ray.start = from;
	ray.dir = to - from;
	ray.dir.normalize();

	IntersectionData temp;
	temp.dist = (to - from).length();

	for (int i = 0; i < (int)nodes.size(); i++)
	{
		if (nodes[i]->geom->intersect(ray, temp))
		{
			return false;
		}
	}

	return true;
		
}

void createNode(Geometry* geometry, Shader* shader)
{
	/*geometries.push_back(geometry);
	shaders.push_back(shader);*/
	Node* newNode = new Node(geometry, shader);
	nodes.push_back(newNode);
}

void initializeScene(void)
{
	camera = new Camera;
	camera->yaw = 0;
	camera->pitch = -10;
	camera->roll = 0;
	camera->fov = 90;
	camera->aspect = 4. / 3.0;
	camera->pos = Vector(0,165,0);

	camera->beginFrame();

	lightPos = Vector(0, 4000, 2000);
	lightColor = Color(1, 1, 1);
	lightPower = 30000000;


	//Plane* plane = new Plane(2);
	////geometries.push_back(plane);

	//Checker* checker = new Checker(Color(0.95, 0.95, 0.95), Color(0.35, 0.35, 0.35), 50);
	//Lambert* lambert = new Lambert(Color(1, 1, 1), checker);

	//Node* floor = new Node(plane, lambert);
	//
	////shaders.push_back(checker);
	//nodes.push_back(floor);


	MyPlane* my_plane = new MyPlane(Vector(0, 0, 0), Vector(0, 1, 0));
	Phong* phong_my_plane = new Phong(Color(0, 0, 1), 40, 1);
	Node* node_my_plane = new Node(my_plane, phong_my_plane);
	nodes.push_back(node_my_plane);

	//Sphere* sphere = new Sphere(Vector(-100, 50, 500), 50);
	////geometries.push_back(sphere);

	//CheckerShader* checker_2 = new CheckerShader(Color(0, 0.75, 0), Color(0.75, 0, 0), 0.1);
	//Node* sphere_node = new Node(sphere, checker_2);

	////shaders.push_back(checker_2);
	//nodes.push_back(sphere_node);
	
	//Create sphere objects dynamically
	for (int i = 1; i < 7; i++)
	{
		float rand1 = (float)rand() / (float)(RAND_MAX);
		float rand2 = (float)rand() / (float)(RAND_MAX);
		float rand3 = (float)rand() / (float)(RAND_MAX);
		float rand4 = (float)rand() / (float)(RAND_MAX);
		float rand5 = (float)rand() / (float)(RAND_MAX);
		float rand6 = (float)rand() / (float)(RAND_MAX);

		//Checker* checker_spheres = new Checker(Color(rand1, rand2, rand3), Color(0.35, 0.35, 0.35), 0.05);

		createNode(new Sphere(Vector(-150, 50, 250*i), 50), new Lambert(Color(rand1, rand2, rand3)));
		createNode(new Sphere(Vector(150, 50, 250 * i), 50), new Phong(Color(rand4, rand5, rand6),40,1));
	}

}


void renderScene(void)
{
	for (int y = 0; y < frameHeight(); y++)
		for (int x = 0; x < frameWidth(); x++) {
			//if ((y == 10 && x == 320) || (y == 240 && x == 320) || (y == 470 && x == 320))
			{
				//cout << "[x]=" << x << "[y]=" << y << endl;
				Ray ray = camera->getScreenRay(x, y);
				vfb[y][x] = raytrace(ray);
			}
		}
}

int main(int argc, char** argv)
{
	if (!initGraphics(RESX, RESY)) return -1;
	initializeScene();
	renderScene();
	displayVFB(vfb);
	waitForUserExit();
	closeGraphics();
	return 0;
}
