#include <SymboleProcedure.h>
#include <iostream>


using std::cout;
using std::endl;


SymboleProcedure::SymboleProcedure(int arite, int id)
	: Symbole("procedure", id), arite(arite)
{
}
	
void SymboleProcedure::printToStd()
{
	cout << "arite:" << arite << endl;	
}
