#include <SymboleArgument.h>
#include <iostream>


using std::cout;
using std::endl;




SymboleArgument::SymboleArgument(bool constant, Type * type, int position, int id)
	: Symbole("argument", id), constant(constant), type(type), position(position)
{
}	
	
void SymboleArgument::printToStd()
{
	cout << "mode:";
	if (constant)	cout << "constant";
	else 			cout << "variable";
	cout << ",type:";
	type->printToStd();
	cout << ",position:" << position << endl;
}
