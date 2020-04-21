#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
#include <list>
#include <string>
#include <istream>
#include <utility>
#include "vertices.h"
#include "faces.h"
#include "arestas.h"
#include "XMLWriter.h"




class modelo
{
	list<vertices*> LV;
	list<faces*> LF;
	list<arestas*> LA;
	list<arestas> L;
	list <pair<faces*,faces*> >LFV;

	string nomeM;

public:

	modelo(string nome);
	void MostrarM();
	string getmodelo();
	void listaA();
	vertices* GetVerticeN(int N);

	vertices ListaF(float a);
	int contarV();
	int contarF();
	int contarA();
	void addvertice(vertices* a);
	void addface(faces* a);
	void addface(int v1, int v2, int v3);
	void addface(faces* a, int v1, int v2, int v3);

	void addaresta(arestas* a);
	void mostrarV();
	void mostrarF();
	void mostrarA();
	float Area();
	bool Envolvente(vertices& Pmin, vertices& Pmax);
	int MemoriaTotal();
	int Memoriaindividual();
	int ModeloMaisMemoria();
	faces* Areaface();
	void EscreverXML(XMLWriter& fich_xml);
	int NumInterseccoes(vertices* A, vertices* B);
	float FaceMaiorCurvatura();
	void vizinhos();
	void mostrarvizinhos();

	~modelo();






};