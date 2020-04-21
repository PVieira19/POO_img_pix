#include "modelo.h"
#include "gestao.h"
#include "arestas.h"
#include "vertices.h"
#include "faces.h"
#include <math.h>
#include <utility>


#include "XMLWriter.h"

using namespace std;

#define PI 3.14159265

modelo::modelo(string nome)
{
	nomeM = nome;
}

void modelo::MostrarM()
{
	cout << "Modelo:" << nomeM << endl;
}

string modelo::getmodelo()
{
	return nomeM;
}


void modelo::addvertice(vertices* a)
{
	LV.push_back(a);
}

void modelo::addface(faces* a)
{
	LF.push_back(a);
}
void modelo::addface(faces* a, int v1, int v2, int v3)
{
	a->Set_v1(GetVerticeN(v1));
	a->Set_v2(GetVerticeN(v2));
	a->Set_v3(GetVerticeN(v3));
	LF.push_back(a);
}


void modelo::addface(int v1, int v2, int v3)
{
	//cout << "\n adiciona face com vertices [ " << v1 << "  ;  " << v2 << "  ;  " << v3 << " ] " << endl;
	//cout << "coordenadas do 1º vertice [" << GetVerticeN(v1)->Getx() << "][" << GetVerticeN(v1)->Gety() << "][ " << GetVerticeN(v1)->Getz() << "] " << endl;

	LF.push_back(new faces(GetVerticeN(v1), GetVerticeN(v2), GetVerticeN(v3)));
}

void modelo::addaresta(arestas* a)
{

	LA.push_back(a);
}

vertices* modelo::GetVerticeN(int N)
{
	list<vertices*>::iterator it = LV.begin();
	advance(it, N-1);
	//cout << (*it)->Getx() << endl;
	return *it;
}

vertices modelo::ListaF(float a)
{

	float f1, f2, f3;
	//cout << "VALOR" << a<< endl;

	list<vertices*>::iterator it = LV.begin();
	advance(it, a);
	//cout << "AQUIIIII" << endl;
	//cout << (*it)->Getx() << endl;

	f1 = (*it)->Getx();
	f2 = (*it)->Gety();
	f3 = (*it)->Getz();



	vertices v(f1, f2, f3);

	return v;
}


void modelo::listaA()
{

	for (list<faces*>::iterator it = LF.begin(); it != LF.end(); it++)
	{
		vertices* v1 = (*it)->Getv1();
		vertices* v2 = (*it)->Getv2();
		vertices* v3 = (*it)->Getv3();
		if (v1 < v2)
			LA.push_back(new arestas(v1, v2));
		else
			LA.push_back(new arestas(v2, v1));
		if (v1 < v3)
			LA.push_back(new arestas(v1, v3));
		else
			LA.push_back(new arestas(v3, v1));
		if (v2 < v3)
			LA.push_back(new arestas(v2, v3));
		else
			LA.push_back(new arestas(v3, v2));

		//LA.push_back(new arestas((*it)->Getv1(), (*it)->Getv2()));
		//LA.push_back(new arestas((*it)->Getv1(), (*it)->Getv3()));
		//LA.push_back(new arestas((*it)->Getv2(), (*it)->Getv3()));
	}
	//LA.sort(arestas::compare);
}


int modelo::contarV()
{
	if (LV.size() == 0) return NULL;
	int x = 0;
	for (list<vertices*>::iterator it = LV.begin(); it != LV.end(); it++)
	{
		x++;
	}
	cout << "Numero de Vertices:" << x << endl;

	return x;
}

int modelo::contarF()
{
	if (LF.size() == 0) return NULL;
	int x = 0;
	for (list<faces*>::iterator it = LF.begin(); it != LF.end(); it++)
	{
		x++;

	}
	cout << "Numero de Faces:" << x << endl;

	return x;
}

int modelo::contarA()
{
	for (list<arestas*>::iterator it = LA.begin(); it != LA.end(); it++)
	{
		L.push_back(**it);
	}
	//L.sort(arestas::compare);
	L.sort();
	L.unique();
	cout << "restam arestas " << L.size() << endl;

	return L.size();
}

void modelo::mostrarV()
{
	if (LV.size() == 0) return;
	for (list<vertices*>::iterator it = LV.begin(); it != LV.end(); it++)
	{
		(*it)->Mostrar();
	}
}


void modelo::mostrarF()
{
	if (LF.size() == 0) return;
	for (list<faces*> ::iterator it = LF.begin(); it != LF.end(); it++)
	{
		(*it)->Mostrar();
	}
}

void modelo::mostrarA()
{
	if (LA.size() == 0) return;
	for (list<arestas*> ::iterator it = LA.begin(); it != LA.end(); it++)
	{
		(*it)->Mostrar();
	}
}


float modelo::Area()
{

	float final = 0;

	vertices* a, * b, * c;
	float l1, l2, l3, s, l;
	for (list<faces*>::iterator it = LF.begin(); it != LF.end(); it++)
	{
		final += (*it)->Area();
	}
		/*
		float x1 = 0, x2 = 0, x3 = 0, y1 = 0, y2 = 0, y3 = 0, z1 = 0, z2 = 0, z3 = 0;


		a = (*it)->Getv1();
		b = (*it)->Getv2();
		c = (*it)->Getv3();

		//cout << "Numero de Arestas:" << (*it)->Getv1() << (*it)->Getv2()<< (*it)->Getv3()<<endl;
		//cout << "Numero de Arestas:" << a << b << c << endl;


		x1 = a->Getx();
		y1 = a->Gety();
		z1 = a->Getz();
		//cout << "Primeira Face:" << x1 << " " << y1 << " " << z1 << " " << endl;

		x2 = b->Getx();
		y2 = b->Gety();
		z2 = b->Getz();
		//cout << "Segunda Face:" << x2 << " " << y2 << " " << z2 << " " << endl;

		x3 = c->Getx();
		y3 = c->Gety();
		z3 = c->Getz();
		//cout << "Terceira Face:" << x3 << " " << y3 << " " << z3 << " " << endl;

		l1 = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2));
		l2 = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3) + (z1 - z3) * (z1 - z3));
		l3 = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2) + (z3 - z2) * (z3 - z2));

		//		s = (f2 + f4 + f6) / 2;
		s = (l1 + l2 + l3) / 2;

		//cout << "S:" << f2 << " " << f4 << " " << f6 << " " << endl;


		//cout << "L:" << s << endl;


		l = s * (s - l1) * s * (s - l2) * s * (s - l3);
		//cout << "Numero de Arestas:" << l << endl;
		final += l;

	}*/
	cout << "Area do modelo:" << final << endl;
	return final;
}




bool modelo::Envolvente(vertices& Pmin, vertices& Pmax)
{
	float x = 0, y = 0, z = 0;

	if (LA.size() == 0) return NULL;
	float min1, max1, min2, max2, min3, max3;

	min1 = max1 = (*LV.begin())->Getx();
	min2 = max2 = (*LV.begin())->Gety();
	min3 = max3 = (*LV.begin())->Getz();


	for (list<vertices*>::iterator it = LV.begin(); it != LV.end(); it++)
	{

		x = (*it)->Getx();

		if (x > max1)
		{
			max1 = x;
		}
		if (x < min1)
		{
			min1 = x;
		}

		y = (*it)->Gety();

		if (y > min2)
		{
			max2 = y;
		}
		if (y < min2)
		{
			min2 = y;
		}

		z = (*it)->Getz();
		if (z > max3)
		{
			max3 = z;
		}
		if (z < min3)
		{
			min3 = z;
		}
	}
	cout << "X max:" << max1 << endl;
	cout << "X min:" << min1 << endl;
	cout << "Y max:" << max2 << endl;
	cout << "Y min:" << min2 << endl;
	cout << "Z max:" << max3 << endl;
	cout << "Z min:" << min3 << endl;
	Pmin.Setx(min1);
	Pmin.Sety(min2);
	Pmin.Setz(min3);
	Pmax.Setx(max1);
	Pmax.Sety(max2);
	Pmax.Setz(max3);
	return 0;

}



int modelo::MemoriaTotal()
{
	int mem = 0;
	for (list<faces*>::iterator F = LF.begin(); F != LF.end(); F++) // Contabiliza a memória usada nas faces
	{
		mem += (*F)->Memoria();
	}

	for (list<vertices*>::iterator F = LV.begin(); F != LV.end(); F++) // Contabiliza a memória usada nos vertices
	{
		mem += (*F)->Memoria();
	}

	for (list<arestas*>::iterator F = LA.begin(); F != LA.end(); F++) // Contabiliza a memória usada nas arestas
	{
		mem += (*F)->Memoria();
	}
	return mem;
}

int modelo::Memoriaindividual()
{
	int mem = 0;
	for (list<faces*>::iterator F = LF.begin(); F != LF.end(); F++) // Contabiliza a memória usada nas faces
	{
		mem += (*F)->Memoria();
	}

	for (list<vertices*>::iterator F = LV.begin(); F != LV.end(); F++) // Contabiliza a memória usada nos vertices
	{
		mem += (*F)->Memoria();
	}

	for (list<arestas*>::iterator F = LA.begin(); F != LA.end(); F++) // Contabiliza a memória usada nas arestas
	{
		mem += (*F)->Memoria();
	}
	return mem;

}


int modelo::ModeloMaisMemoria()
{
	int mem = 0;
	for (list<faces*>::iterator P = LF.begin(); P != LF.end(); P++) // Contabiliza a memória usada nas faces
	{
		mem += (*P)->Memoria();
	}

	for (list<vertices*>::iterator F = LV.begin(); F != LV.end(); F++) // Contabiliza a memória usada nos vertices
	{
		mem += (*F)->Memoria();
	}

	for (list<arestas*>::iterator F = LA.begin(); F != LA.end(); F++) // Contabiliza a memória usada nas arestas
	{
		mem += (*F)->Memoria();
	}
	return mem;
}


int modelo::NumInterseccoes(vertices* A, vertices* B)
{
	int i = 0,j=0,k=0,l=0;
	for (list<faces*>::iterator it = LF.begin(); it != LF.end(); it++)
	{ 


		float vetor1x = 0, vetor1y = 0, vetor1z = 0, vetor2x = 0, vetor2y = 0, vetor2z = 0, vetor3x=0, vetor3y=0, vetor3z=0, vetor5x=0, vetor5y=0, vetor5z=0;
		
		float vetoracx = 0, vetoracy = 0, vetoracz = 0;

		float vetorcax = 0, vetorcay = 0, vetorcaz = 0, vetorcix = 0, vetorciy = 0, vetorciz = 0, vetoraix = 0, vetoraiy = 0, vetoraiz = 0, vetorbix = 0, vetorbiy = 0, vetorbiz = 0;

		float  ax = 0, ay = 0, az = 0, bx = 0, by = 0, bz = 0, cx = 0, cy = 0, cz = 0, n = 0, w1 = 0, w2 = 0, w3 = 0;

		float dx = 0, dy = 0, dz = 0, ex = 0, ey = 0, ez = 0, xi = 0, yi = 0, zi = 0, d;

		float cima = 0, baixo = 0, t = 0;

		float finalw1 = 0, finalw2 = 0, finalw3 = 0;

		float final = 0, final2 = 0;
		
		ax = (*it)->Getv1()->Getx();
		ay = (*it)->Getv1()->Gety();
		az = (*it)->Getv1()->Getz();

		bx = (*it)->Getv2()->Getx();
		by = (*it)->Getv2()->Gety();
		bz = (*it)->Getv2()->Getz();

		cx = (*it)->Getv3()->Getx();
		cy = (*it)->Getv3()->Gety();
		cz = (*it)->Getv3()->Getz();

		vetor1x = bx - ax;
		vetor1y = by - ay;
		vetor1z = bz - az;

		vetor2x = cx - ax;
		vetor2y = cy - ay;
		vetor2z = cz - az;

		vetor5x = cx - bx;
		vetor5y = cy - by;
		vetor5z = cz - bz;

		w1 = ((vetor1y * vetor2z) - (vetor1z * vetor2y));
		w2 = ((vetor1z * vetor2x) - (vetor1x * vetor2z));
		w3 = ((vetor1x * vetor2y) - (vetor1y * vetor2x));

		dx = A->Getx();
		dy = A->Gety();
		dz = A->Getz();

		ex = B->Getx();
		ey = B->Gety();
		ez = B->Getz();

		vetor3x = ex - dx;
		vetor3y = ey - dy;
		vetor3z = ez - dz;

		d = -w1 * cx - w2 * cy - w3 * cz;
		cima = -d - (w1 * dx) - (w2 * dy) - (w3 * dz);

		baixo = (w1 * vetor3x) + (w2 * vetor3y) + (w3 * vetor3z);
		
		float TOL = 0.0000001;
		if (fabs(baixo) <= TOL)  // Atenção!, a igualdade entrte reais ??? 0.000034 =? 0.00006754
		{
			k++;
			continue;
		}
		else
		{
			t = cima / baixo;
			xi = dx + (t * vetor3x);
			yi = dy + (t * vetor3y);
			zi = dz + (t * vetor3z);

			//cout << " V1x:" << xi << " V1y:" << yi << " V1z:" << zi << endl;

			// SE FAZ PARTE DO TRIANGULO

			vetorcix = xi - cx;
			vetorciy = yi - cy;
			vetorciz = zi - cz;

			vetoraix = xi - ax;
			vetoraiy = yi - ay;
			vetoraiz = zi - az;

			vetorbix = xi - bx;
			vetorbiy = yi - by;
			vetorbiz = zi - bz;

			vetorcax = ax - cx;
			vetorcay = ay - cy;
			vetorcaz = az - cz;

			vetoracx = cx - ax;
			vetoracy = cy - ay;
			vetoracz = cz - az;

			float finalw1x = 0, finalw1y = 0, finalw1z = 0, finalw2x = 0, finalw2y = 0, finalw2z = 0, finalw3x = 0, finalw3y = 0, finalw3z = 0;

			finalw1x = (vetor1y * vetoraiz) - (vetor1z * vetoraiy);
			finalw1y = (vetor1z * vetoraix) - (vetor1x * vetoraiz);
			finalw1z = (vetor1x * vetoraiy) - (vetor1y * vetoraix);

			finalw2x = (vetor5y * vetorbiz) - (vetor5z * vetorbiy);
			finalw2y = (vetor5z * vetorbix) - (vetor5x * vetorbiz);
			finalw2z = (vetor5x * vetorbiy) - (vetor5y * vetorbix);
			
			finalw3x = (vetorcay * vetorciz) - (vetorcaz * vetorciy);
			finalw3y = (vetorcaz * vetorcix) - (vetorcax * vetorciz);
			finalw3z = (vetorcax * vetorciy) - (vetorcay * vetorcix);

			final = ((finalw1x * finalw2x) + (finalw1y * finalw2y) + (finalw1z * finalw2z))* ((finalw3x * finalw2x) + (finalw3y * finalw2y) + (finalw3z * finalw2z));

			//finalw1 = (vetor1x * vetoraix) + (vetor1y * vetoraiy) + (vetor1z * vetoraiz);
			//finalw2 = (vetor5x * vetorbix) + (vetor5y * vetorbiy) + (vetor5z * vetorbiz);
			//finalw3 = (vetorcax * vetorcix) + (vetorcay * vetorciy) + (vetorcaz * vetorciz);

			//final = (finalw1 * finalw2);
			//final2 = (finalw2 * finalw3);
			l++;
			if (final > 0.00005 )
			{
				cout << " ESTEX:" << xi << " ESTEY:" << yi << " ESTEZ:" << zi << endl;
				i++;
			}
		}
	}
	cout << " i:" << i << " k:" << k << " l:" << l << endl;
	return i;

}

faces* modelo::Areaface()
{
	float final = 0;
	faces *ffinal = NULL;
	float area = 0;
	//vertices *a , *b , *c ;
	//float l1, l2, l3,s,l;
	for (list<faces*>::iterator it = LF.begin(); it != LF.end(); it++)
	{
		final = (*it)->Area();

		if (final > area)
		{
			area = final;
			ffinal = (*it);
		}
	}
	/*
	for (list<faces*>::iterator it = LF.begin(); it != LF.end(); it++)
	{

		float x1 = 0, x2 = 0, x3 = 0, y1 = 0, y2 = 0, y3 = 0, z1 = 0, z2 = 0, z3 = 0;


		a = (*it)->Getv1();
		b = (*it)->Getv2();
		c = (*it)->Getv3();

		//cout << "Numero de Arestas:" << (*it)->Getv1() << (*it)->Getv2()<< (*it)->Getv3()<<endl;
		//cout << "Numero de Arestas:" << a << b << c << endl;


		x1 = a->Getx();
		y1 = a->Gety();
		z1 = a->Getz();
		//cout << "Primeira Face:" << x1 << " " << y1 << " " << z1 << " " << endl;

		x2 = b->Getx();
		y2 = b->Gety();
		z2 = b->Getz();
		//cout << "Segunda Face:" << x2 << " " << y2 << " " << z2 << " " << endl;

		x3 = c->Getx();
		y3 = c->Gety();
		z3 = c->Getz();
		//cout << "Terceira Face:" << x3 << " " << y3 << " " << z3 << " " << endl;

		l1 = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2));
		l2 = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3) + (z1 - z3) * (z1 - z3));
		l3 = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2) + (z3 - z2) * (z3 - z2));

//		s = (f2 + f4 + f6) / 2;
		s = (l1 + l2 + l3) / 2;

		//cout << "S:" << f2 << " " << f4 << " " << f6 << " " << endl;


		//cout << "L:" << s << endl;


		l = s * (s - l1) * s * (s - l2) * s * (s - l3);
		//cout << "Numero de Arestas:" << l << endl;

		if (l > final)
		{
			final = l;
			ffinal = (*it);
		}
		*/

	
	cout << "Area da maior face do Modelo:" << area << endl;
	return ffinal;
}


void modelo::EscreverXML(XMLWriter& fich_xml)
{

	vertices* vertice1;
	vertices* vertice2;
	vertices* vertice3;

	for (list<faces*>::iterator P = LF.begin(); P != LF.end(); P++) // Contabiliza a memória usada nas faces
	{
		string tipo1="x", tipo2 = "y", tipo3 = "z";
		float x1 = 0, y1 = 0, z1 = 0, x2 = 0, y2 = 0, z2 = 0, x3 = 0, y3 = 0, z3 = 0;

		vertice1 = (*P)->Getv1();
		vertice2 = (*P)->Getv2();
		vertice3 = (*P)->Getv3();

		x1 = vertice1->Getx();
		y1 = vertice1->Gety();
		z1 = vertice1->Getz();

		x2 = vertice1->Getx();
		y2 = vertice1->Gety();
		z2 = vertice1->Getz();

		x3 = vertice1->Getx();
		y3 = vertice1->Gety();
		z3 = vertice1->Getz();


		fich_xml.WriteStartElement("Faces");
		fich_xml.WriteStartElement("V");

		fich_xml.WriteElementString(tipo1, x1);
		fich_xml.WriteElementString(tipo2, y1);
		fich_xml.WriteElementString(tipo3, z1);

		fich_xml.WriteEndElement();

		fich_xml.WriteStartElement("V");

		fich_xml.WriteElementString(tipo1, x2);
		fich_xml.WriteElementString(tipo2, y2);
		fich_xml.WriteElementString(tipo3, z2);

		fich_xml.WriteEndElement();

		fich_xml.WriteStartElement("V");

		fich_xml.WriteElementString(tipo1, x3);
		fich_xml.WriteElementString(tipo2, y3);
		fich_xml.WriteElementString(tipo3, z3);

		fich_xml.WriteEndElement();

		fich_xml.WriteEndElement();

	}


	for (list<vertices*>::iterator F = LV.begin(); F != LV.end(); F++)
	{
		float a1 = 0, a2 = 0, a3 = 0;
		string tipo1 = "x", tipo2 = "y", tipo3 = "z";
		a1 = (*F)->Getx();
		a2 = (*F)->Gety();
		a3 = (*F)->Getz();
		fich_xml.WriteStartElement("Vertices");

		fich_xml.WriteElementString(tipo1, a1);
		fich_xml.WriteElementString(tipo2, a2);
		fich_xml.WriteElementString(tipo3, a3);

		fich_xml.WriteEndElement();

	}

}


float modelo::FaceMaiorCurvatura()
{
	int teste1 = 0, teste2 = 0, teste3 = 0, teste4 = 0, teste5 = 0;

	float a1x = 0, a1z = 0, a1y = 0, a2x = 0, a2z = 0, a2y = 0, a3x = 0, a3z = 0, a3y = 0;
	float b1x = 0, b1z = 0, b1y = 0, b2x = 0, b2z = 0, b2y = 0, b3x = 0, b3z = 0, b3y = 0;
	float vetor1x = 0, vetor1y = 0, vetor1z = 0, vetor2x = 0, vetor2y = 0, vetor2z = 0;
	float vetor3x = 0, vetor3y = 0, vetor3z = 0, vetor4x = 0, vetor4y = 0, vetor4z = 0;
	double angulo = 0, final = 0;
	float w1 = 0, w2 = 0, w3 = 0, w4 = 0, w5 = 0, w6 = 0;

	float maiorangulo = 0;

	float cima = 0, baixo = 0;

	faces* facedoangulo = NULL;
	teste4++;
	vertices* aresta1, * aresta2;
	for (list<arestas*> ::iterator it = LA.begin(); it != LA.end(); it++)
	{
		teste3++;
		aresta1 = (*it)->Geta1();
		aresta2 = (*it)->Geta1();

		for (list<arestas*>::iterator it2 = LA.begin(); it2 != LA.end(); it2++)
		{

			if (aresta1 == (*it2)->Geta1() && aresta2 == (*it2)->Geta2())
			{
				teste1++;
				a1x = aresta1->Getx();
				a1y = aresta1->Gety();
				a1z = aresta1->Getz();

				a2x = aresta1->Getx();
				a2y = aresta1->Gety();
				a2z = aresta1->Getz();

				a3x = aresta1->Getx();
				a3y = aresta1->Gety();
				a3z = aresta1->Getz();

				b1x = (*it2)->Geta1()->Getx();
				b1y = (*it2)->Geta1()->Gety();
				b1z = (*it2)->Geta1()->Getz();

				b2x = (*it2)->Geta1()->Getx();
				b2y = (*it2)->Geta1()->Gety();
				b2z = (*it2)->Geta1()->Getz();

				b3x = (*it2)->Geta1()->Getx();
				b3y = (*it2)->Geta1()->Gety();
				b3z = (*it2)->Geta1()->Getz();

				vetor1x = a2x - a1x;
				vetor1y = a2y - a1y;
				vetor1z = a2z - a1z;

				vetor2x = a3x - a2x;
				vetor2y = a3y - a2y;
				vetor2z = a3z - a2z;

				vetor3x = b2x - b1x;
				vetor3y = b2y - b1y;
				vetor3z = b2z - b1z;

				vetor4x = b3x - b2x;
				vetor4y = b3y - b2y;
				vetor4z = b3z - b2z;

				w1 = ((vetor1y * vetor2z) - (vetor1z * vetor2y));
				w2 = ((vetor1z * vetor2x) - (vetor1x * vetor2z));
				w3 = ((vetor1x * vetor2y) - (vetor2x * vetor1y));

				w4 = ((vetor3y * vetor4z) - (vetor3z * vetor4y));
				w5 = ((vetor3z * vetor4x) - (vetor3x * vetor4z));
				w6 = ((vetor3x * vetor4y) - (vetor4x * vetor3y));


				cima = fabs((w1 * w4) + (w2 * w5) + (w3 * w6));
				baixo = (sqrt(pow(w1, 2) + pow(w2, 2) + pow(w3, 2))) * (sqrt(pow(w4, 2) + pow(w5, 2) + pow(w6, 2)));

				float TOL = 0.0000001;
				if (fabs(baixo) <= TOL)  // Atenção!, a igualdade entrte reais ??? 0.000034 =? 0.00006754
				{
					continue;
				}
				else
				{
					final = cima / baixo;
					angulo = acos(final) * 180 / PI;
					if (angulo > maiorangulo)
					{
						maiorangulo = angulo;
					}

				}

				if (aresta1 == (*it)->Geta2() && aresta2 == (*it)->Geta1())
				{
					teste2++;
					a1x = aresta1->Getx();
					a1y = aresta1->Gety();
					a1z = aresta1->Getz();

					a2x = aresta1->Getx();
					a2y = aresta1->Gety();
					a2z = aresta1->Getz();

					a3x = aresta1->Getx();
					a3y = aresta1->Gety();
					a3z = aresta1->Getz();

					b1x = (*it)->Geta1()->Getx();
					b1y = (*it)->Geta1()->Gety();
					b1z = (*it)->Geta1()->Getz();

					b2x = (*it)->Geta1()->Getx();
					b2y = (*it)->Geta1()->Gety();
					b2z = (*it)->Geta1()->Getz();

					b3x = (*it)->Geta1()->Getx();
					b3y = (*it)->Geta1()->Gety();
					b3z = (*it)->Geta1()->Getz();

					vetor1x = a2x - a1x;
					vetor1y = a2y - a1y;
					vetor1z = a2z - a1z;

					vetor2x = a3x - a2x;
					vetor2y = a3y - a2y;
					vetor2z = a3z - a2z;

					vetor3x = b2x - b1x;
					vetor3y = b2y - b1y;
					vetor3z = b2z - b1z;

					vetor4x = b3x - b2x;
					vetor4y = b3y - b2y;
					vetor4z = b3z - b2z;

					w1 = ((vetor1y * vetor2z) - (vetor1z * vetor2y));
					w2 = ((vetor1z * vetor2x) - (vetor1x * vetor2z));
					w3 = ((vetor1x * vetor2y) - (vetor2x * vetor1y));

					w4 = ((vetor3y * vetor4z) - (vetor3z * vetor4y));
					w5 = ((vetor3z * vetor4x) - (vetor3x * vetor4z));
					w6 = ((vetor3x * vetor4y) - (vetor4x * vetor3y));


					cima = fabs((w1 * w4) + (w2 * w5) + (w3 * w6));
					baixo = (sqrt(pow(w1, 2) + pow(w2, 2) + pow(w3, 2))) * (sqrt(pow(w4, 2) + pow(w5, 2) + pow(w6, 2)));

					float TOL = 0.0000001;
					if (fabs(baixo) <= TOL)  // Atenção!, a igualdade entrte reais ??? 0.000034 =? 0.00006754
					{
						continue;
					}
					else
					{
						final = cima / baixo;
						angulo = acos(final) * 180 / PI;
						if (angulo > maiorangulo)
						{
							maiorangulo = angulo;
						}

					}


					if (aresta1 == (*it)->Geta2() && aresta2 == (*it)->Geta1())
					{
						teste2++;
						a1x = aresta1->Getx();
						a1y = aresta1->Gety();
						a1z = aresta1->Getz();

						a2x = aresta1->Getx();
						a2y = aresta1->Gety();
						a2z = aresta1->Getz();

						a3x = aresta1->Getx();
						a3y = aresta1->Gety();
						a3z = aresta1->Getz();

						b1x = (*it)->Geta1()->Getx();
						b1y = (*it)->Geta1()->Gety();
						b1z = (*it)->Geta1()->Getz();

						b2x = (*it)->Geta1()->Getx();
						b2y = (*it)->Geta1()->Gety();
						b2z = (*it)->Geta1()->Getz();

						b3x = (*it)->Geta1()->Getx();
						b3y = (*it)->Geta1()->Gety();
						b3z = (*it)->Geta1()->Getz();

						vetor1x = a2x - a1x;
						vetor1y = a2y - a1y;
						vetor1z = a2z - a1z;

						vetor2x = a3x - a2x;
						vetor2y = a3y - a2y;
						vetor2z = a3z - a2z;

						vetor3x = b2x - b1x;
						vetor3y = b2y - b1y;
						vetor3z = b2z - b1z;

						vetor4x = b3x - b2x;
						vetor4y = b3y - b2y;
						vetor4z = b3z - b2z;

						w1 = ((vetor1y * vetor2z) - (vetor1z * vetor2y));
						w2 = ((vetor1z * vetor2x) - (vetor1x * vetor2z));
						w3 = ((vetor1x * vetor2y) - (vetor2x * vetor1y));

						w4 = ((vetor3y * vetor4z) - (vetor3z * vetor4y));
						w5 = ((vetor3z * vetor4x) - (vetor3x * vetor4z));
						w6 = ((vetor3x * vetor4y) - (vetor4x * vetor3y));


						cima = fabs((w1 * w4) + (w2 * w5) + (w3 * w6));
						baixo = (sqrt(pow(w1, 2) + pow(w2, 2) + pow(w3, 2))) * (sqrt(pow(w4, 2) + pow(w5, 2) + pow(w6, 2)));

						float TOL = 0.0000001;
						if (fabs(baixo) <= TOL)  // Atenção!, a igualdade entrte reais ??? 0.000034 =? 0.00006754
						{
							continue;
						}
						else
						{
							final = cima / baixo;
							angulo = acos(final) * 180 / PI;
							if (angulo > maiorangulo)
							{
								maiorangulo = angulo;
							}

						}

					}

				}

			}
		}
		cout << "\n Maior Angulo:" << maiorangulo << endl;
		cout << "\n Teste 1:" << teste1 << "\nTeste 2:" << teste2 << "\nTeste 3:" << teste3 << "\nTeste 4:" << teste4 << endl;

		return maiorangulo;
	}
}
		/*
		float angulo = 0;
		faces* facefinal = new faces();


		for (list<faces*>::iterator F = LF.begin(); F != LF.end(); ++F)
		{
			float x1 = 0, y1 = 0, z1 = 0;
			float x2 = 0, y2 = 0, z2 = 0;
			float x3 = 0, y3 = 0, z3 = 0;

			vertices* vertice1 = new vertices();
			vertices* vertice2 = new vertices();
			vertices* vertice3 = new vertices();


			float raiz1 = 0, raiz2 = 0, raiz3 = 0;
			float raiz4 = 0, raiz5 = 0, raiz6 = 0;
			float raiz7 = 0, raiz8 = 0, raiz9 = 0;
			float f1 = 0, f2 = 0, f3 = 0, f4 = 0, f5 = 0, f6 = 0;

			float ang1 = 0, ang2 = 0, ang3 = 0, ang4 = 0, ang5 = 0, ang6 = 0, ang7 = 0, ang8 = 0, ang9 = 0;


			vertice1 = (*F)->Getv1();
			vertice2 = (*F)->Getv2();
			vertice3 = (*F)->Getv3();

			x1 = vertice1->Getx();
			y1 = vertice1->Gety();
			z1 = vertice1->Getz();

			x2 = vertice2->Getx();
			y2 = vertice2->Gety();
			z2 = vertice2->Getz();

			x3 = vertice3->Getx();
			y3 = vertice3->Gety();
			z3 = vertice3->Getz();


			raiz1 = (x1 - x2);
			raiz2 = (y1 - y2);
			raiz3 = (z1 - z2);
			raiz1 = pow(raiz1, 2);
			raiz2 = pow(raiz2, 2);
			raiz3 = pow(raiz3, 2);
			f1 = raiz1 + raiz2 + raiz3;
			f2 = sqrt(f1);
			//cout << "Numero de Arestas:" << raiz1<< " " << raiz2 << " " << raiz3 << " " << endl;

			raiz4 = (x2 - x3);
			raiz5 = (y2 - y3);
			raiz6 = (z2 - z3);
			raiz4 = pow(raiz1, 2);
			raiz5 = pow(raiz2, 2);
			raiz6 = pow(raiz3, 2);
			f3 = raiz1 + raiz2 + raiz3;
			f4 = sqrt(f1);
			//cout << "Numero de Arestas:" << raiz4 << " " << raiz5 << " " << raiz6 << " " << endl;

			raiz7 = (x1 - x3);
			raiz8 = (y1 - y3);
			raiz9 = (z1 - z3);
			raiz7 = pow(raiz1, 2);
			raiz8 = pow(raiz2, 2);
			raiz9 = pow(raiz3, 2);
			f5 = raiz1 + raiz2 + raiz3;
			f6 = sqrt(f1);

			ang1= pow(f2, 2) + pow(f4, 2);
			ang2= pow(f2, 2) + pow(f6, 2);
			ang3= pow(f4, 2) + pow(f6, 2);

			ang4 = ang1 / (2 * f2 * f4);
			ang5 = ang2 / (2 * f2 * f6);
			ang6 = ang3 / (2 * f4 * f6);

			ang7 = acos(ang4);
			ang8 = acos(ang5);
			ang9 = acos(ang6);

			if (ang7 > angulo)
			{
				facefinal = new faces((*F)->Getv1(), (*F)->Getv2(), (*F)->Getv3());
			}
			if (ang8 > angulo)
			{
				facefinal = new faces((*F)->Getv1(), (*F)->Getv2(), (*F)->Getv3());
			}
			if (ang9 > angulo)
			{
				facefinal = new faces((*F)->Getv1(), (*F)->Getv2(), (*F)->Getv3());
			}

		}


		cout << "Face de Maior angulo" << raiz1<< " " << raiz2 << " " << raiz3 << " " << endl;
		cout << "Numero de Arestas:" << raiz1<< " " << raiz2 << " " << raiz3 << " " << endl;
		cout << "Numero de Arestas:" << raiz1<< " " << raiz2 << " " << raiz3 << " " << endl;

		return *facefinal;
		*/


void modelo::vizinhos()
{
	for (list<faces*>::iterator it = LF.begin(); it != LF.end(); it++)
	{

		for (list<faces*>::iterator it2 = LF.begin(); it2 != LF.end(); it2++)
		{
			if ((*it)->Getv1() == (*it)->Getv1() || (*it)->Getv1() == (*it)->Getv2() || (*it)->Getv1() == (*it)->Getv3())
			{
				LFV.push_back(pair<faces*,faces*>(*(it), *(it2)));
			}
			if ((*it)->Getv2() == (*it)->Getv1() || (*it)->Getv2() == (*it)->Getv2() || (*it)->Getv2() == (*it)->Getv3())
			{
				LFV.push_back(pair<faces*, faces*>(*(it), *(it2)));
			}
			if ((*it)->Getv3() == (*it)->Getv1() || (*it)->Getv3() == (*it)->Getv2() || (*it)->Getv3() == (*it)->Getv3())
			{
				LFV.push_back(pair<faces*, faces*>(*(it), *(it2)));
			}
		}
	}


}

void modelo::mostrarvizinhos()
{

	for (list<pair<faces*,faces*>>::iterator it = LFV.begin(); it != LFV.end(); ++it) // Contabiliza a memória usada nas faces
	{
	}

}


modelo::~modelo()
{
	list<vertices*>::iterator F = LV.begin();
	while (F != LV.end())
	{
		delete(*F);
		//F = LV.erase(F);
		//LV.remove(*F);
		//F = LV.erase(F);
		++F;
	}
	
	list<arestas*>::iterator iA = LA.begin();
	while (iA != LA.end())
	{
		delete(*iA);
		//iA++;
		//iA = LA.erase(iA);
		++iA;
	}

	list<faces*>::iterator iF = LF.begin();
	while (iF != LF.end())
	{
		delete(*iF);
		++iF;
		//iF = LF.erase(iF);
	}
	LA.clear();
	LF.clear();
	LV.clear();
	L.clear();

	cout << "APAGUEI TUDO" << endl;
}