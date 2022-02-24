#include "Obj3d.h"
#include <iostream>
using namespace std;

void Object3d::readfile(const char * filename)
{
	std::ifstream myfile(filename);
	if (myfile.is_open())
	{
		string line;
		while (getline(myfile, line)) {
			char lineHeader[128];

			if (line.find("v ") != std::string::npos) {
				string temp, x, y, z;

				stringstream ss(line);
				getline(ss, temp, ' ');
				getline(ss, x, ' ');
				getline(ss, y, ' ');
				getline(ss, z, ' ');

				vertex v;
				v.x = stof(x);
				v.y = stof(y);
				v.z = stof(z);

				vertices.push_back(v);
			}
			else if (line.find("vt ") != std::string::npos) {
				string temp, x, y;

				stringstream ss(line);
				getline(ss, temp, ' ');
				getline(ss, x, ' ');
				getline(ss, y, ' ');

				vt t;
				t.x = stof(x);
				t.y = stof(y);

				vts.push_back(t);

			}
			else if (line.find("vn ") != std::string::npos) {
				string temp, x, y, z;
				stringstream ss(line);
				getline(ss, temp, ' ');
				getline(ss, x, ' ');
				getline(ss, y, ' ');
				getline(ss, z, ' ');

				normal n;
				n.x = stof(x);
				n.y = stof(y);
				n.z = stof(z);

				normals.push_back(n);

			}
			else if (line.find("f ") != std::string::npos) {
				string temp, temp1, temp2, temp3,temp4, x1, y1, z1;
				string  x2, y2, z2;
				string  x3, y3, z3;

				stringstream ss3(line);


				getline(ss3, temp, ' ');
				getline(ss3, temp1, ' ');
				stringstream ss(temp1);

				getline(ss, x1, '/');
				getline(ss, y1, '/');
				getline(ss, z1, '/');

				getline(ss3, temp2, ' ');
				stringstream ss1(temp2);
				getline(ss1, x2, '/');
				getline(ss1, y2, '/');
				getline(ss1, z2, '/');

				getline(ss3, temp4, ' ');
				stringstream ss2(temp4);
				getline(ss2, x3, '/');
				getline(ss2, y3, '/');
				getline(ss2, z3, '/');

				face f;
				f.v1 = stof(x1);
				f.v2 = stof(x2);
				f.v3 = stof(x3);

				f.vt1 = stof(y1);
				f.vt2 = stof(y2);
				f.vt3 = stof(y3);

				f.n1 = stof(z1);
				f.n2 = stof(z2);
				f.n3 = stof(z3);


				faces.push_back(f);

			}
		}
	}
}

void Object3d::draw()
{
	glBegin(GL_TRIANGLES);
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	for (int i = 0; i < faces.size(); i++)
	{
		int fv1 = faces[i].v1 - 1;
		int fv2 = faces[i].v2 - 1;
		int fv3 = faces[i].v3 - 1;

		int fn1 = faces[i].n1 - 1;
		int fn2 = faces[i].n2 - 1;
		int fn3 = faces[i].n3 - 1;

		int fvt1 = faces[i].vt1 - 1;
		int fvt2 = faces[i].vt2 - 1;
		int fvt3 = faces[i].vt3 - 1;

		vertex v1 = vertices[fv1];
		vertex v2 = vertices[fv2];
		vertex v3 = vertices[fv3];

		normal n1 = normals[fn1];
		normal n2 = normals[fn2];
		normal n3 = normals[fn3];

		vt vt1 = vts[fvt1];
		vt vt2 = vts[fvt2];
		vt vt3 = vts[fvt3];

		//auf flugklasse speichern und dort drawen
		glNormal3f(n1.x, n1.y, n1.z);
		glTexCoord2f(vt1.x, vt1.y);
		glVertex3f(v1.x, v1.y, v1.z);

		glNormal3f(n2.x, n2.y, n2.z);
		glTexCoord2f(vt2.x, vt2.y);
		glVertex3f(v2.x, v2.y, v2.z);

		glNormal3f(n3.x, n3.y, n3.z);
		glTexCoord2f(vt3.x, vt3.y);
		glVertex3f(v3.x, v3.y, v3.z);
	}
	glEnd();


}
