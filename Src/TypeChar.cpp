#include <TypeChar.h>
#include <iostream>


TypeChar::TypeChar()
	: Type("char")
{
}

bool TypeChar::operator==(const Type& type) const
{
	const TypeChar * t = dynamic_cast<const TypeChar*>(&type);
	return t!=0;
}	 


void TypeChar::printToStd() const
{
	std::cout << "caractere";
}
