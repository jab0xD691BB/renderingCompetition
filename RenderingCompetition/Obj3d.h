#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <GL/freeglut.h> 
#include <sstream>

class Object3d
{

public:

	void readfile(const char* filename);
	void draw();

private:
	struct vertex {
		float x;
		float y;
		float z;
	};
	struct normal {
		float x;
		float y;
		float z;
	};
	struct vt {
		float x;
		float y;
	};

	struct face {
		unsigned int v1, v2, v3;
		unsigned int vt1, vt2, vt3;
		unsigned int n1, n2, n3;

	};

	std::vector<vertex> vertices;
	std::vector<normal> normals;
	std::vector<face> faces;
	std::vector<vt> vts;

};