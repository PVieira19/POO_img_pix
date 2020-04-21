#include "faces.h"
#include "gestao.h"
#include "arestas.h"
#include "vertices.h"




arestas::arestas(vertices *a, vertices *b)
{
	a1 = a;
	a2 = b;
	V = 0;
}

void arestas::Mostrar()
{
	cout << "Passei em:" << __FUNCTION__ << ">" << endl;
	cout << "A1:" << a1->Getx() << " " << a1->Gety() << " " << a1->Getz() << endl;
	cout << "A2:" << a2->Getx() << " " << a2->Gety() << " " << a2->Getz() << endl;

}

void arestas::SetV()
{
	V = 1;
}

void arestas::SetV2()
{
	V = 5;
}

int arestas::GetV()
{
	return V;
}



vertices *arestas::Geta1()
{
	return a1;
}

vertices *arestas::Geta2()
{
	return a2;
}

int arestas::Memoria()
{
	int mem = 0;
	mem =  sizeof(vertices*) + (sizeof(vertices*));
	return (mem);
}


arestas::~arestas()
{

}
