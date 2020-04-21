#pragma once
#include <iostream>
#include <fstream>
using namespace std;
#include <list>
#include "objecto.h"
#include <string>

class vertices : public objecto
{
	float x, y, z;

public:
	vertices(float a, float b, float c);
	vertices();
	void Mostrar();
	float Getx();
	float Gety();
	float Getz();
	void Setx(float a);
	void Sety(float a);
	void Setz(float a);
	int Memoria();
	bool Removervertices();

	~vertices();
};

