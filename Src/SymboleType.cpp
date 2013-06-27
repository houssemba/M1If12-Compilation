#include <SymboleType.h>
#include <iostream>



SymboleType::SymboleType(Type * type, int id)
	: Symbole("type", id), type(type)
{
}


void SymboleType::printToStd()
{
	cout << "type:";
	type->printToStd();
	std::cout<<std::endl;
}
