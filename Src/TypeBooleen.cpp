#include <TypeBooleen.h>
#include <iostream>


TypeBooleen::TypeBooleen()
	: Type("")
{
}

bool TypeBooleen::operator==(const Type& type) const
{
	const TypeBooleen * t = dynamic_cast<const TypeBooleen*>(&type);
	return t!=0;
}


void TypeBooleen::printToStd() const 
{
	std::cout << "booleen";
}	 
