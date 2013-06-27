#include <TypeTableau.h>
#include <iostream>



using std::cout;
using std::endl;


TypeTableau::TypeTableau(Type * typeContained, std::vector<Type*> const & dimsList)
	: Type(""), dims(dimsList), typeContained(typeContained)
{
	
}


bool TypeTableau::operator==(Type const & type) const
{
	TypeTableau const * t = dynamic_cast<TypeTableau const *>(&type);
	if (t==0)	return false;
	
	if (dims.size() != t->dims.size())	return false;
	
	for (unsigned int i=0; i<dims.size(); i++)
	{
		if (!((*dims.at(i))==(*t->dims.at(i))))	return false;
	}
	
	return true;
}


void TypeTableau::printToStd() const
{
	cout << "[";
	for (unsigned int i=0; i<dims.size(); i++) 
	{
		dims.at(i)->printToStd();
		cout << ",";
	}
	typeContained->printToStd();
	cout << "]";
}

