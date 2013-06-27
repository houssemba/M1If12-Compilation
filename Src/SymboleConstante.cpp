#include <SymboleConstante.h>
#include <Type.hpp>
#include <iostream>
#include <MapIdent.h>
extern std::string toString(bool);
extern MapIdent identTable;



SymboleConstante::SymboleConstante(Type * type, int id, Valeur valeur)
	: Symbole("constante",id) , type(type), valeur(valeur)
{
}



void SymboleConstante::printToStd()
{
	std::cout << "type:";
	type->printToStd();
	std::cout << ",valeur:";
	if (type->estEntier())	std::cout << valeur.entier;
	else if (type->estReel())	std::cout << valeur.reel;
	else if (type->estBooleen())	std::cout << toString(valeur.booleen); 
	else if (type->estChaine())		std::cout << *(valeur.chaine);
	else if (type->estEnum())	std::cout << identTable.getName(valeur.enumValeur);
	std::cout << std::endl;
}


