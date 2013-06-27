#include "TypeEntier.h"
#include <iostream>


TypeEntier::TypeEntier()
	: Type("entier")
{
	
}


bool TypeEntier::operator==(const Type & _type) const
{
	/*try {
		dynamic_cast<TypeEntier const &>(_type);
	}catch (const std::bad_cast & )
	{
		return false;
	}
	*/
	const TypeEntier * t = dynamic_cast<const TypeEntier*>(&_type);
	return t!=0;
}

void TypeEntier::printToStd() const
{
	std::cout << "entier";
}
