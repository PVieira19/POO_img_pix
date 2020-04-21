#include <iostream>
#include <fstream>
#include <stdlib.h>  
#include <stdio.h>
#include <list>
#include <string>
#include <sstream>
#include <math.h> 

using namespace std;

#include "vertices.h"
#include "faces.h"
#include "gestao.h"
#include "modelo.h"
#include "XMLWriter.h"



bool gestao::Load(const string& fich)
{
	ifstream ifs;
	ifs.open(fich);
	string filename = fich;
	if (!ifs.is_open())
		return false;

	string line, line1;

	getline(ifs, line);
	getline(ifs, line1);

	modelo* p = new modelo(filename);
	addmodelo(p);

	string linha;
	while (getline(ifs, linha))
	{

		string tipo;
		string a, b, c;
		string::size_type sz;

		stringstream novaLinha(linha);
		getline(novaLinha, tipo, ' ');
		getline(novaLinha, a, ' ');
		getline(novaLinha, b, ' ');
		getline(novaLinha, c, '\n');
		float a1 = std::stof(a, &sz);
		float b1 = std::stof(b, &sz);
		float c1 = std::stof(c, &sz);
		//cout << "Tipo:" << tipo << endl;
		//cout << "A:" << a1 << endl;
		//cout << "B:" << b1 << endl;
		//cout << "C:" << c1 << endl;
		if (tipo == "v")
		{
			vertices* p1 = new vertices(a1, b1, c1);
			p->addvertice(p1);

			// 0.134010 0.910055 2.241230
		}
		if(tipo == "f") {
			vertices* a, * b, * c;
			a = p->GetVerticeN(a1);
			b = p->GetVerticeN(b1);
			c = p->GetVerticeN(c1);
			faces* f = new faces(a,b,c);
			//p->addface(a1-1, b1-1, c1-1);
			//p->addface(f, a1 - 1, b1 - 1, c1 - 1);
			p->addface(f);
			
		}
	}

	p->listaA();

	cout << "FECHOU O FICHEIRO" << endl;

	ifs.close();
}


int gestao::Contar(int Tipo)
{
	int x;
	if (Tipo == 0)
	{
		for (list<modelo*>::iterator it = LM.begin(); it != LM.end(); ++it)
		{
			x = (*it)->contarV();
		}
	}

	if (Tipo == 1)
	{
		for (list<modelo*>::iterator it = LM.begin(); it != LM.end(); ++it)
		{
			x = (*it)->contarF();

		}
	}

	if (Tipo == 2)
	{
		for (list<modelo*>::iterator it = LM.begin(); it != LM.end(); ++it)
		{
			x = (*it)->contarA();
		}
	}
	return 0;
}


void gestao::ModeloN()
{
	if (LM.size() == 0) return;
	for (list<modelo*>::iterator it = LM.begin(); it != LM.end(); ++it)
	{
		(*it)->MostrarM();
	}
}

void gestao::addmodelo(modelo* a)
{
	LM.push_back(a);
}

void gestao::mostrarV()
{
	if (LM.size() == 0) return;
	for (list<modelo*>::iterator it = LM.begin(); it != LM.end(); ++it)
	{
		(*it)->mostrarV();
	}
}

void gestao::mostrarF()
{
	if (LM.size() == 0) return;
	for (list<modelo*> ::iterator it = LM.begin(); it != LM.end(); it++)
	{
		(*it)->mostrarF();
	}
}

void gestao::mostrarA()
{
	if (LM.size() == 0) return;
	for (list<modelo*> ::iterator it = LM.begin(); it != LM.end(); it++)
	{
		(*it)->mostrarA();
	}
}

void gestao::mostrarM()
{
	if (LM.size() == 0) return;
	for (list<modelo*>::iterator it = LM.begin(); it != LM.end(); ++it)
	{
		(*it)->MostrarM();
	}
}



float gestao::AreaModelo(const string& fich)
{
	float soma = 0;
	for (list<modelo*>::iterator it = LM.begin(); it != LM.end(); it++)
	{
		if ((*it)->getmodelo() == fich)
		{
			soma = (*it)->Area();
		}
	}
	return soma;
}



bool gestao::Envolvente(const string& fich, vertices& Pmin, vertices& Pmax)
{
	for (list<modelo*>::iterator it = LM.begin(); it != LM.end(); it++)
	{
		if ((*it)->getmodelo() == fich)
		{
			(*it)->Envolvente(Pmin, Pmax);
			return true;
		}
	}
	return false;
}


int gestao::MemoriaTotal()
{
	int mem = 0;
	for (list<modelo*>::iterator P = LM.begin(); P != LM.end(); ++P) // Vai andar de modelo em modelo a comparar a string do modelo com o ficheiro recebido
	{
		mem += (*P)->MemoriaTotal();
	}

	cout << "Memoria Total:" << mem << endl;
	return mem;
}



modelo* gestao::Memoriaindividual(const string& fich)
{
	string nome = fich;
	string nome1;
	int mem = 0;
	for (list<modelo*>::iterator P = LM.begin(); P != LM.end(); ++P)
	{
		nome1 = (*P)->getmodelo();
		if (nome == nome1)
		{
			mem = (*P)->Memoriaindividual();
		}
	}
	cout << "Memoria Deste Modelo:" << mem << endl;

	return 0;
}

modelo* gestao::ModeloMaisMemoria()
{
	int mem = 0;
	int memfinal = 0;
	string modeloinicio, modelofinal;
	for (list<modelo*>::iterator P = LM.begin(); P != LM.end(); ++P) // Contabiliza a memória usada nas faces
	{
		modeloinicio = (*P)->getmodelo();
		mem = (*P)->ModeloMaisMemoria();

		if (mem > memfinal)
		{
			memfinal = mem;
			modelofinal = modeloinicio;
		}
	}
	cout << "Modelo com mais Memoria:" << modelofinal << " Com: " << memfinal << endl;

	return 0;
}



bool gestao::RemoverModelo(const string& fich)
{
	string nome = fich;

	cout << "Passei em " << __FUNCTION__ << endl;

	if (LM.size() == 0) return 0;

	for (list<modelo*>::iterator P = LM.begin(); P != LM.end(); ++P) // Contabiliza a memória usada nas faces
	{
		if (nome == (*P)->getmodelo())
		{
			delete(*P);
			LM.remove(*P);
			return true;
		}
		
	}
	return false;
}



void gestao::EscreverXML(const string& fich, const string& fich_xml)
{
	string x = fich;
	string nome = fich_xml;
	string a;
	XMLWriter xx;

	for (list<modelo*>::iterator P = LM.begin(); P != LM.end(); ++P) // Vai andar de modelo em modelo a comparar a string do modelo com o ficheiro recebido
	{
		if (x == (*P)->getmodelo())
		{
			a = (*P)->getmodelo();
			xx.WriteStartDocument(nome);
			xx.WriteStartElement(a);
			(*P)->EscreverXML(xx);
			xx.WriteEndElement();
		}

	}
	xx.WriteEndDocument();

}

int gestao::NumInterseccoes(vertices* A, vertices* B)
{
	int x=0;

	if (LM.size() == 0) return 0;
	for (list<modelo*>::iterator it = LM.begin(); it != LM.end(); ++it)
	{
		x = (*it)->NumInterseccoes(A, B);
	}

	cout << "Os Pontos passam por:" << x << " Faces " << endl;

}

faces* gestao::FaceMaiorArea(const string& fich)
{
	if (LM.size() == 0) return NULL;

	faces* x=0;

	for (list<modelo*>::iterator P = LM.begin(); P != LM.end(); ++P) // Contabiliza a memória usada nas faces
	{
		if (fich == (*P)->getmodelo())
		{
			x=(*P)->Areaface();
		}
	}
	return x;
}


float* gestao::FaceMaiorCurvatura(const string& fich)
{

	float a;
	if (LM.size() == 0) return 0;

	for (list<modelo*>::iterator P = LM.begin(); P != LM.end(); ++P) // Contabiliza a memória usada nas faces
	{
		if (fich == (*P)->getmodelo())
		{
			a = (*P)->FaceMaiorCurvatura();
		}
	}

	//cout << "A face com maiot curvatura e:" <<  << " " <<  << " " <<  << " " << endl;
}

void gestao::vizinhos(const string& fich)
{

	for (list<modelo*>::iterator P = LM.begin(); P != LM.end(); ++P) // Contabiliza a memória usada nas faces
	{
		if (fich == (*P)->getmodelo())
		{
			(*P)->vizinhos();
		}
	}

}

void gestao::mostrarvizinhos()
{

	for (list<modelo*>::iterator P = LM.begin(); P != LM.end(); ++P) // Contabiliza a memória usada nas faces
	{

		(*P)->mostrarvizinhos();

	}

}




gestao::gestao()
{

}



gestao::~gestao()
{
	cout << "Passei em " << __FUNCTION__ << endl;

	if (LM.size() == 0) return;

	for (list<modelo*>::iterator P = LM.begin(); P != LM.end();P++) // Contabiliza a memória usada nas faces
	{
		delete(*P);
	}
}