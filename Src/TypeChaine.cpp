#include <TypeChaine.h>
#include <iostream>


TypeChaine::TypeChaine()
	: Type("")
{
}

bool TypeChaine::operator==(const Type& type) const
{
	const TypeChaine * t = dynamic_cast<const TypeChaine*>(&type);
	return t!=0;
}	 


void TypeChaine::printToStd() const
{
	std::cout << "chaine";
}
