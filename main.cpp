/***************************************************************************
 *   Copyright (C) 2009-2013 by Veselin Georgiev, Slavomir Kaslev et al    *
 *   admin@raytracing-bg.net                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

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
	data.dist = 1e99;

	for (int i = 0; i < (int)nodes.size(); i++)
	{
		if (nodes[i]->geom->intersect(ray, data))
		{
			closestNode = nodes[i];
		}

	}

	if (!closestNode)
	{
		return Color(0.5, 0.5, 0.5);		//if there is no closestNode, we hit the background
	}
	else
	{
		return closestNode->shader->shade(ray, data);	//if there is closestNode, calculate it's material
	}

		//return Color(1, 1, 1);
	
	//
	//return Color(0, 0, 0);
}

//Color raytrace(Ray ray)
//{
//	IntersectionData data;
//	for (int i = 0; i < (int)nodes.size(); i++)
//		if (nodes[i]->geom->intersect(ray, data))
//			return nodes[i]->shader->shade(ray, data);
//
//	//
//	return Color(0, 0, 0);
//}

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

	lightPos = Vector(0, 1800, 0);
	lightColor = Color(1, 1, 1);
	lightPower = 5000000;


	Plane* plane = new Plane(2);
	//geometries.push_back(plane);
	
	CheckerShader* checker = new CheckerShader(Color(0.95, 0.95, 0.95), Color(0.35, 0.35, 0.35), 50);
	Node* floor = new Node(plane, checker);
	
	//shaders.push_back(checker);
	nodes.push_back(floor);


	//Sphere* sphere = new Sphere(Vector(-100, 50, 500), 50);
	////geometries.push_back(sphere);

	//CheckerShader* checker_2 = new CheckerShader(Color(0, 0.75, 0), Color(0.75, 0, 0), 0.1);
	//Node* sphere_node = new Node(sphere, checker_2);

	////shaders.push_back(checker_2);
	//nodes.push_back(sphere_node);
	
	for (int i = 1; i < 7; i++)
	{
		createNode(new Sphere(Vector(-150, 50, 250*i), 50), new CheckerShader(Color(0, 0.75, 0), Color(0.75, 0, 0), 0.1));
		createNode(new Sphere(Vector(150, 50, 250 * i), 50), new CheckerShader(Color(0, 0.75, 0), Color(0.75, 0, 0), 0.1));
	}

}


//void initializeScene(void)
//{
//	camera = new Camera;
//	camera->yaw = 0;
//	camera->pitch = -30;
//	camera->roll = 0;
//	camera->fov = 90;
//	camera->aspect = 4. / 3.0;
//	camera->pos = Vector(0, 165, 0);
//
//	camera->beginFrame();
//
//	lightPos = Vector(-30, 100, 250);
//	lightColor = Color(1, 1, 1);
//	lightPower = 50000;
//
//	Plane* plane = new Plane(2);
//	geometries.push_back(plane);
//
//	CheckerShader* checker = new CheckerShader(Color(0, 0, 0), Color(0, 0.5, 1), 5);
//	Node* floor = new Node(plane, checker);
//	shaders.push_back(checker);
//	nodes.push_back(floor);
//}

void renderScene(void)
{
	for (int y = 0; y < frameHeight(); y++)
		for (int x = 0; x < frameWidth(); x++) {
			Ray ray = camera->getScreenRay(x, y);
			vfb[y][x] = raytrace(ray);
		}
}

int main(int argc, char** argv)
{
	if (!initGraphics(RESX, RESY)) return -1;
	initializeScene();
	renderScene();
	displayVFB(vfb);
	//displayVFBB(vfb);
	waitForUserExit();
	closeGraphics();
	return 0;
}
