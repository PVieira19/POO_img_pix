#include "XMLWriter.h"


XMLWriter::XMLWriter()
{

}


XMLWriter::~XMLWriter()
{
}

void XMLWriter::WriteStartDocument(string ficheiro)
{
	ifs.open(ficheiro);
}

void XMLWriter::WriteStartElement(string el)
{
	ifs << "<" << el << ">" << endl;
	mylist.push_back(el);

}

void XMLWriter::WriteElementString(string tipo, float valor1)
{
	ifs << "<" << tipo << ">" << valor1 << "</" << tipo << ">" << endl;
}

void XMLWriter::WriteEndDocument()
{
	ifs.close();
}

void XMLWriter::WriteEndElement()
{
	ifs << "</" << mylist.back() << ">" << endl;
	mylist.pop_back();

}

