#include "Symbole.hpp"
#include <SymboleArgument.h>
#include "GenerateurType.h"
#include <TypePointeur.h>
#include <TypeEnum.h>
#include <MapIdent.h>

extern MapIdent identTable;
/**
 * \file Symboles.cpp
 * \brief fonctions pour gérer les symboles
 * \author JeanMichel LE
 * \version 0.1
 * \date 13 octobre 2012
 *
 * Gestion d'un symbole
 *
 */
using namespace std;

Symbole::Symbole(string cat, int identifiant) 
	: categorie(cat), id(identifiant)
{
}



Symbole::~Symbole() {

}

bool Symbole::estArgConstant()
{
	if (! estArgument())	return false;
	SymboleArgument * sa = dynamic_cast<SymboleArgument*>(this);
	return sa->estConstant();
}

/*Symbole::Symbole(string cat, Type* type) {
    categorie = new string(cat);
    type = type;
}

Symbole::Symbole(string cat, Type* type, int id) {
	categorie = new string(cat);
    type = type;
	id = id;
}*/
