#ifndef __SYMBOLE_CHAMP_H
#define __SYMBOLE_CHAMP_H

#include "Symbole.hpp"

class SymboleChamp : public Symbole
{
	private:
	Type * type;
	int position;
	
	public:
	SymboleChamp(Type * type, int position, int id);
	
	void printToStd();
	
	bool estChamp() { return true; }
	
	void setPosition(int position) { this->position = position; }
	
	Type * getType() { return type; }

};













#endif
