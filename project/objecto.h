#pragma once
#include <iostream>
#include <fstream>
using namespace std;
#include <list>
#include <string>

class objecto
{
public:
	objecto() {};

	virtual void Mostrar() { };
	virtual int Memoria() { return 0; };
	virtual float Area() { return 0; }
	~objecto() {};
};

