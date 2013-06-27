#include "SymboleVariable.h"
#include "Type.hpp"

#include <iostream>

SymboleVariable::SymboleVariable(Type* type, int id)
	: Symbole("variable", id), type(type)
{
}

void SymboleVariable::printToStd()
{
	std::cout<<"type:";
	type->printToStd();// affiche "entier ou reel ou ...
	std::cout<<std::endl;
}
