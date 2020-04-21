#pragma once

#include <iostream>
#include <fstream>
using namespace std;
#include <list>
#include <string>
#include "vertices.h"


class faces : public objecto
{

	vertices* v1;
	vertices* v2;
	vertices* v3;

public:
	faces();
	faces(vertices *a, vertices *b, vertices *c);
	void Mostrar();
	vertices *Getv1();
	vertices *Getv2();
	vertices *Getv3();
	void Set_v1(vertices* v);
	void Set_v2(vertices* v);
	void Set_v3(vertices* v);
	vertices intreta(vertices *A,vertices *B);
	int Memoria();

	float Area();

	~faces();
};
