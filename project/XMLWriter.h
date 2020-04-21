#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include<list>
using namespace std;


class XMLWriter
{
private:
	ofstream ifs;
	list<string> mylist;
public:
	XMLWriter();
	~XMLWriter();
	void WriteStartDocument(string ficheiro);
	void WriteStartElement(string el);
	void WriteElementString(string tipo, float valor1);
	void WriteEndDocument();
	void WriteEndElement();
};

