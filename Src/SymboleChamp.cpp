#include <SymboleChamp.h>
#include <iostream>

using std::cout;
using std::endl;

SymboleChamp::SymboleChamp(Type * type, int position, int id)
	: Symbole("champ",id), type(type), position(position)
{
}
	

void SymboleChamp::printToStd()
{
	cout << "type:";
	type->printToStd();
	cout << ",position:" << position << endl;
}
