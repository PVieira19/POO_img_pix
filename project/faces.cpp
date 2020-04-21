#include "faces.h"
#include "faces.h"

#include "gestao.h"



faces::faces()
{
	v1 = NULL;
	v2 = NULL;
	v3 = NULL;
}

faces::faces(vertices* a, vertices* b, vertices* c)
{
	v1 = a;
	v2 = b;
	v3 = c;
}


vertices* faces::Getv1()
{
	return v1;
}

vertices* faces::Getv2()
{
	return v2;
}

vertices* faces::Getv3()
{
	return v3;
}

void faces::Set_v1(vertices *v) {	v1 = v; }
void faces::Set_v2(vertices* v) { v2 = v; }
void faces::Set_v3(vertices* v) { v3 = v; }



void faces::Mostrar()
{
	cout << "Passei em:" << __FUNCTION__ << ">" << endl;
	cout << "A:" << v1->Getx() << " " << v1->Gety() << " " << v1->Getz() << endl;
	cout << "B:" << v2->Getx() << " " << v2->Gety() << " " << v2->Getz() << endl;
	cout << "C:" << v3->Getx() << " " << v3->Gety() << " " << v3->Getz() << endl;
}

int faces::Memoria()
{
	int mem = 0;
	mem = sizeof(vertices*) + sizeof(vertices*) + sizeof(vertices*);
	return (mem);
}

float faces::Area()
{
	float vetorABx = 0, vetorABy = 0, vetorABz = 0, vetorACx = 0, vetorACy = 0, vetorACz = 0;
	float ax = 0,ay=0, az = 0, bx = 0, by = 0, bz = 0, cx = 0, cy = 0, cz = 0;
	float quadrado=0, quadrado1=0,area1=0;

	ax = v1->Getx();
	ay = v1->Gety();
	az = v1->Getz();

	bx = v2->Getx();
	by = v2->Gety();
	bz = v2->Getz();

	cx = v3->Getx();
	cy = v3->Gety();
	cz = v3->Getz();

	vetorABx = bx - ax;
	vetorABy = by - ay;
	vetorABz = bz - az;

	vetorACx = cx - ax;
	vetorACy = cy - ay;
	vetorACz = cz - az;

	quadrado1 = sqrt(pow((vetorABy * vetorACz) - (vetorABz * vetorACy), 2) + pow(((vetorABz * vetorACx) - (vetorABx * vetorACz)), 2) + pow(((vetorABx * vetorACy) - (vetorABy * vetorACx)), 2));
	area1 = quadrado1 / 2;
	return area1;

	/*
	float l1, l2, l3, s, l, final;

	l1 = sqrt((v1->Getx() - v2->Getx()) * (v1->Getx() - v2->Getx()) + (v1->Gety() - v2->Gety()) * (v1->Gety() - v2->Gety()) + (v1->Getz() - v2->Getz()) * (v1->Getz() - v2->Getz()));
	l2 = sqrt((v1->Getx() - v3->Getx()) * (v1->Getx() - v3->Getx()) + (v1->Gety() - v3->Gety()) * (v1->Gety() - v3->Gety()) + (v1->Getz() - v3->Getz()) * (v1->Getz() - v3->Getz()));
	l3 = sqrt((v3->Getx() - v2->Getx()) * (v3->Getx() - v2->Getx()) + (v3->Gety() - v2->Gety()) * (v3->Gety() - v2->Gety()) + (v3->Getz() - v2->Getz()) * (v3->Getz() - v2->Getz()));
	s = (l1 + l2 + l3) / 2;
	l = s * (s - l1) * s * (s - l2) * s * (s - l3);
	//cout << "Numero de Arestas:" << l << endl;
	return l;

	*/
}



faces::~faces()
{
	//free(v1);
	//free(v2);
	//free(v3);
}