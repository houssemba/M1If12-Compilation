#ifndef __SYMBOLE_CONSTANTE_H
#define __SYMBOLE_CONSTANTE_H

#include "Symbole.hpp"
#include "Attributs.h"

class Type;

class SymboleConstante : public Symbole
{
	private:
	
	Type * type;
	Valeur valeur;
	
	public:
	
	SymboleConstante(Type* type, int id, Valeur valeur);
	
	void printToStd();
	
	bool estConstante() { return true; }
	
	Type * getType() { return type; }
	Valeur getValeur() { return valeur; }
};
















#endif
