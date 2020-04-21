#pragma once


#include <iostream>
#include <fstream>
using namespace std;
#include <list>
#include <string>

#include "vertices.h"
#include "faces.h"
#include "arestas.h"
#include "modelo.h"




class gestao
{
	list<modelo*> LM;

public:

	gestao();
	~gestao();
	bool Load(const string& fich);
	void mostrarV();
	void ModeloN();
	void mostrarF();
	void mostrarA();
	void mostrarM();
	int Contar(int Tipo);
	int MemoriaTotal();
	modelo* Memoriaindividual(const string& fich);
	modelo* ModeloMaisMemoria();
	bool RemoverModelo(const string& fich);
	void EscreverXML(const string& fich, const string& fich_xml);
	void addmodelo(modelo* a);
	faces* FaceMaiorArea(const string& fich);
	int NumInterseccoes(vertices* A, vertices* B);
	bool Envolvente(const string& fich, vertices& Pmin, vertices& Pmax);
	float* FaceMaiorCurvatura(const string& fich);
	void vizinhos(const string& fich);
	void mostrarvizinhos();
	float AreaModelo(const string& fich);

	




};