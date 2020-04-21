#include "gestao.h"
#include "vertices.h"


vertices::vertices()
{
	x = NULL;
	y = NULL;
	z = NULL;
}


vertices::vertices(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}

void vertices::Mostrar()
{

	cout << "Passei em:" << __FUNCTION__ << ">" << endl;
	cout << "A:" << x << endl;
	cout << "B:" << y << endl;
	cout << "C:" << z << endl;


}

float vertices::Getx()
{
	return x;
}

float vertices::Gety()
{
	return y;
}

float vertices::Getz()
{
	return z;
}

void vertices::Setx(float a)
{
	x = a;
}

void vertices::Sety(float a)
{
	y = a;
}

void vertices::Setz(float a)
{
	z = a;
}




int vertices::Memoria()
{
	int mem = 0;
	mem = sizeof(float) + sizeof(float) + sizeof(float);
	return (mem);
}

bool vertices::Removervertices()
{
	return true;
}

vertices::~vertices()
{
	
}