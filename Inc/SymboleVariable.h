#ifndef __SYMBOLE_VARIABLE_H
#define __SYMBOLE_VARIABLE_H

#include "Symbole.hpp"

class Type;

class SymboleVariable : public Symbole
{
	private:
	
	Type* type;
	
	public:
	
	SymboleVariable(Type* type, int id);
	
	void printToStd();
	
	Type * getType() { return type; }
	
	bool estVariable() { return true; }
};











#endif
