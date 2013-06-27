#include <TypeStructure.h>
#include <MapIdent.h>
#include <iostream>

extern MapIdent identTable;

using std::cout;
using std::endl;
using std::pair;




TypeStructure::TypeStructure(std::vector<std::pair<int, Type*> > & lesChamps)
	: Type(""), champs(lesChamps)
{
}
	

bool TypeStructure::operator==(Type const & type) const
{
	TypeStructure const * t = dynamic_cast<TypeStructure const *>(&type);
	if (t==0) return false;
	
	if (champs.size() != t->champs.size())	return false;
	// sinon on teste : ts les champs sont les memes ?
	for (unsigned int i =0; i<champs.size(); i++)
	{
		pair<int, Type*> c1 = champs.at(i);
		pair<int, Type*> c2 = t->champs.at(i);
		if(c1.first != c2.first)	return false;
		if(!((*c1.second) == (*c2.second)))	return false;
	}
	
	return true;
	
}
	

void TypeStructure::printToStd() const
{
	cout << "{";
	for (unsigned int i=0; i<champs.size(); i++)
	{
		pair<int, Type*> c = champs.at(i);
		cout << identTable.getName(c.first) << ":";
		c.second->printToStd();
		if (i!= champs.size()-1)	cout << ",";
	}
	cout << "}";
}

int TypeStructure::decalage(TypeStructure const & t, int id)
{
	int ret = 0;
	for (unsigned int i=0; i<t.champs.size(); i++)
	{
		std::pair<int, Type*> c = t.champs.at(i);
		if (c.first == id)	break;		
		
		ret += taille(c.second);
	}
	
	return ret;
}

int TypeStructure::taille(Type * t)
{
	if (t->estEntier() || t->estReel() || t->estPointeur() || t->estChaine())	return 4;	
	if (t->estEnum() || t->estChar() || t->estBooleen())	return 1;
	return 2;
}

bool TypeStructure::isField(int id)
{
	for (unsigned int i=0; i<champs.size(); i++)
	{
		std::pair<int, Type*> c = champs.at(i);
		if (c.first == id)	return true;		
		
	}
	
	return false;
}

Type* TypeStructure::getTypeField(int id)
{
	for (unsigned int i=0; i<champs.size(); i++)
	{
		std::pair<int, Type*> c = champs.at(i);
		if (c.first == id)	return c.second;		
		
	}
	
	return 0;
}









