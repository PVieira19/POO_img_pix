#pragma once
#include "arestas.h"

#include <iostream>
#include <fstream>
using namespace std;
#include <list>
#include <string>
#include "vertices.h"


class arestas : public objecto
{

	vertices* a1;
	vertices* a2;

	int V;

public:
	arestas(vertices *a, vertices *b);
	void Mostrar();
	vertices *Geta1();
	vertices *Geta2();
	int GetV();
	int Memoria();
	void SetV();
	void SetV2();

	bool compare(const arestas& x, const arestas& y);
	//bool compare(const arestas* x, const arestas* y);

	bool operator == (arestas const& y) {
		if (a1 != y.a1)
			return false;

		return  a2 == y.a2;
	}

	bool operator < (arestas const& y) {

		//return  a1 < y.a1;

		if (a1 < y.a1)
			return true;
		if (a1 > y.a1)
			return false;
		if (a2 < y.a2)
			return true;
		return false;

	}

	~arestas();
};


