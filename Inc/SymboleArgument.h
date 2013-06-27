#ifndef __SYMBOLE_ARGUMENT_H
#define __SYMBOLE_ARGUMENT_H

#include "Symbole.hpp"

class Type;

class SymboleArgument : public Symbole
{
	
	private:
	bool constant;
	Type * type;
	int position;
	
	public:
	SymboleArgument(bool constant, Type * type, int position, int id);
	
	void printToStd();
	
	bool estArgument() { return true; }
	
	bool estConstant() { return constant; }
	
	void setPosition(int position) { this->position = position; }
	
	Type * getType() { return type; }
};



















#endif
