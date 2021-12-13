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


	Plane* plane = new Plane(2);
	////geometries.push_back(plane);

	Checker* checker = new Checker(Color(0.95, 0.95, 0.95), Color(0.35, 0.35, 0.35), 100);
	Checker* checker2 = new Checker(Color(0.95, 0.95, 0.95), Color(0.25, 0.25, 0.95), 100);
	//Lambert* lambert = new Lambert(Color(1, 1, 1), checker);

	//Node* floor = new Node(plane, lambert);
	
	//shaders.push_back(checker);
	//nodes.push_back(floor);


	//MyPlane* my_plane = new MyPlane(Vector(0, 0, 0), Vector(0.1, 1, 0));
	//Phong* phong_my_plane = new Phong(Color(0, 0, 1), 40, 1, checker);
	////Lambert* phong_my_plane = new Lambert(Color(0.8, 0.2, 0.2));
	//Node* node_my_plane = new Node(my_plane, phong_my_plane);
	//nodes.push_back(node_my_plane);

	//MyPlane* my_plane_2 = new MyPlane(Vector(0, 0, 8000), Vector(0, 0, -1));
	//Phong* phong_my_plane_2 = new Phong(Color(0, 0, 1), 40, 1, checker2);
	//Node* node_my_plane_2 = new Node(my_plane_2, phong_my_plane_2);
	//nodes.push_back(node_my_plane_2);


	//MyDisk* my_disk = new MyDisk(Vector(0, 0, 750), Vector(0, 1, 0), 550);
	//Checker* my_disk_checker = new Checker(Color(0.95, 0.15, 0.15), Color(0.15, 0.95, 0.15), 15);
	//Phong* phong_my_disk = new Phong(Color(0, 0, 1), 40, 1, my_disk_checker);
	//Node* node_my_disk = new Node(my_disk, phong_my_disk);
	//nodes.push_back(node_my_disk);

	//MyDisk* my_disk_2 = new MyDisk(Vector(0, 50, 550), Vector(0, 1, 0), 100);
	//Lambert* phong_my_disk_2 = new Lambert(Color(0.8, 0.2, 0.2));
	//Node* node_my_disk_2 = new Node(my_disk_2, phong_my_disk_2);
	//nodes.push_back(node_my_disk_2);


	//MySquare* my_square = new MySquare(Vector(0, 0, 400), Vector(0, 0, 1), 100);
	//Checker* my_square_checker = new Checker(Color(0.95, 0.15, 0.15), Color(0.15, 0.95, 0.15), 100);
	//Phong* phong_my_square = new Phong(Color(0, 0, 1), 40, 1, my_square_checker);
	//Node* node_my_square = new Node(my_square, phong_my_square);
	//nodes.push_back(node_my_square);

	//MySphere* my_sphere = new MySphere(Vector(0, 0, 400), 50);
	//Phong* phong_my_sphere = new Phong(Color(0, 0, 1), 40, 1);
	//Node* node_my_sphere = new Node(my_sphere, phong_my_sphere);
	//nodes.push_back(node_my_sphere);

	//MySphere* my_sphere_2 = new MySphere(Vector(50, 0, 400), 50);
	//Phong* phong_my_sphere_2 = new Phong(Color(1, 0, 0), 40, 1);
	//Node* node_my_sphere_2 = new Node(my_sphere_2, phong_my_sphere_2);
	//nodes.push_back(node_my_sphere_2);

	//MyCube* my_cube = new MyCube(Vector(0, 0, 400), 50);
	//Phong* phong_my_cube = new Phong(Color(1, 0, 0), 40, 1);
	//Node* node_my_cube = new Node(my_cube, phong_my_cube);
	//nodes.push_back(node_my_cube);

	MyElipse* my_elipse = new MyElipse(Vector(0, 0, 400), 50, 0.5, 1);
	Phong* phong_my_elipse = new Phong(Color(1, 0, 0), 40, 1);
	Node* node_my_elipse = new Node(my_elipse, phong_my_elipse);
	nodes.push_back(node_my_elipse);

	//Sphere* sphere = new Sphere(Vector(-100, 50, 500), 50);
	////geometries.push_back(sphere);

	//CheckerShader* checker_2 = new CheckerShader(Color(0, 0.75, 0), Color(0.75, 0, 0), 0.1);
	//Node* sphere_node = new Node(sphere, checker_2);

	////shaders.push_back(checker_2);
	//nodes.push_back(sphere_node);
	
	//Create sphere objects dynamically
	//for (int i = 1; i < 7; i++)
	//{
	//	float rand1 = (float)rand() / (float)(RAND_MAX);
	//	float rand2 = (float)rand() / (float)(RAND_MAX);
	//	float rand3 = (float)rand() / (float)(RAND_MAX);
	//	float rand4 = (float)rand() / (float)(RAND_MAX);
	//	float rand5 = (float)rand() / (float)(RAND_MAX);
	//	float rand6 = (float)rand() / (float)(RAND_MAX);

	//	//Checker* checker_spheres = new Checker(Color(rand1, rand2, rand3), Color(0.35, 0.35, 0.35), 0.05);

	//	createNode(new Sphere(Vector(-150, 50, 250*i), 50), new Lambert(Color(rand1, rand2, rand3)));
	//	createNode(new Sphere(Vector(150, 50, 250 * i), 50), new Phong(Color(rand4, rand5, rand6),40,1));
	//}

}


void renderScene(void)
{
	for (int y = 0; y < frameHeight(); y++)
		for (int x = 0; x < frameWidth(); x++) {
			//if ((y < 380 && y > 300 && x < 320 && x > 318))
			//if ((y < 320 && y > 318 && x < 640 && x > 0)) //horizontal line rendering
			//if ((y < 377 && y > 299 && x < 320 && x > 318)) //vertical line rendering
			//if ((y < 480 && y > 0 && x < 320 && x > 318)) //vertical line rendering
			//if ((y < 320 && y > 318 && x < 280 && x > 278)) //vertical line rendering

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
