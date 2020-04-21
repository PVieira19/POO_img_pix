
#include <iostream>
#include "gestao.h"
#include "vertices.h"
#include<sstream>

using namespace std;

int main()
{
	while (true)
	{
		string a;
		a = "cubo.obj";
		gestao* pt = new gestao();
		vertices Pmin, Pmax;

		float a1 = 112, b1 =209, c1 = 319;
		float a2 = 121, b2 = 219, c2 = 311;
		// 8 E 11
		vertices* x = new vertices(a1, b1, c1);
		vertices* y = new vertices(a2, b2, c2);
		cout << "Funcao Load:" << endl;
		pt->Load(a);

		pt->AreaModelo(a);
		cout << "Envolvente:" << endl;
		pt->Envolvente(a, Pmin, Pmax);
		pt->Memoriaindividual(a);
		pt->FaceMaiorArea(a);
		pt->EscreverXML(a, "ficheiro.xml");
		pt->EscreverXML(a, "ola.xml");
		pt->NumInterseccoes(x, y);
		//pt->FaceMaiorCurvatura(a);
		cout << "\n" << endl;
		/*
		string b;
		b = "dog.obj";
		cout << "Funcao Load:" << endl;
		pt->Load(b);
		pt->AreaModelo(b);
		cout << "Envolvente:" << endl;
		pt->Envolvente(b, Pmin, Pmax);
		pt->Memoriaindividual(b);
		pt->FaceMaiorArea(b);

		cout << "\n" << endl;
		pt->NumInterseccoes(x, y);
		cout << "\n" << endl;
		*/

		//pt->mostrarF();
		pt->Contar(0);
		pt->Contar(1);
		pt->Contar(2);


		pt->MemoriaTotal();
		cout << "\n" << endl;

		pt->ModeloMaisMemoria();
		cout << "\n" << endl;

		pt->ModeloN();
		cout << "\n" << endl;

		free(x);
		free(y);
		delete(pt);
	}

}