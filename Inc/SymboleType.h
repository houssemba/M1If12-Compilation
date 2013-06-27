#ifndef __SYMBOLE_TYPE_H
#define __SYMBOLE_TYPE_H


#include "Symbole.hpp"

class Type;

class SymboleType : public Symbole
{
	private:
	
	Type * type;	
	
	public:
	
	SymboleType(Type * type, int id);
	
	void printToStd();
	
	bool estType() { return true; }
	
	Type * getType() { return type; }
};




























#endif
