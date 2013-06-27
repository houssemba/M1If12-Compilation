
#include "TableDesSymboles.hpp"

#include "MapIdent.h"

#include <stdio.h>
#include <algorithm>
#include <vector>

extern int yyerror( char * );
extern MapIdent identTable;


/**
 * \file TableDesSymboles.cpp
 * \brief fonctions pour gérer la table des symboles
 * \author JeanMichel LE
 * \version 0.1
 * \date 13 octobre 2012
 *
 * Gestion du tableau des symboles
 *
 */

// ###### CONSTRUCTEUR & DESTRUCTEUR ######


TableDesSymboles::TableDesSymboles(std::string name, TableDesSymboles * parent) 
	: tableSymboles(), numContexte(0), name(name), tsParent(parent)
{
}

TableDesSymboles::~TableDesSymboles() {
}

// ###### GETEUR ######
int TableDesSymboles::getNumContexte() {
    return this->numContexte;
}

// vector<Symbole*> TableDesSymboles::getTableSymboles() {
//     return this->tableSymboles;
// }

int TableDesSymboles::getNumContexteTSActuel(bool incrementation)
{	
	static int numContexte = 1;
	if (incrementation)
	    numContexte++;
	return numContexte;
}

// ###### SETEUR ######


void TableDesSymboles::setNumContexte(int i) {
    this->numContexte = i;
}

// ###### FONCTIONS ######

void TableDesSymboles::ajouter(int identifiant, Symbole* symbole) {
    if (tableSymboles.find(identifiant) != tableSymboles.end()) {
    	// !!! error identifiant deja declarer --> erreur
    	char msg[255];
    	sprintf(msg, "l'identifiant : \"%s\" a déja été declarer !!!", (identTable.getName(identifiant)).c_str());
    	yyerror(msg);
    }
    
    // sinon on l'ajoute à la table
    tableSymboles[identifiant] = symbole;
}

void TableDesSymboles::afficher() {
    unsigned int i;
    
    vector<int> idIndex;/*utiliser pr classer la table par identifiant.*/
    map<int, Symbole*>::iterator it = tableSymboles.begin();
    
    for (;it != tableSymboles.end(); it++)
    {	
    	idIndex.push_back(it->first);
    }
    sort(idIndex.begin(), idIndex.end());
    
    std::cout << "** Table Symbole (" << getName() << "," ;
    if (hasParent()) std::cout << getParent()->getName();
    std::cout << ")" << std::endl;
    
    for (i=0; i < idIndex.size(); i++) {
        Symbole* s = this->tableSymboles[idIndex[i]];
        cout << s->getId() << " ";
        cout << s->getCategorie() << " ";
        s->printToStd();
        //cout << s->getType()->getStringType() << endl;
    }
}

Symbole* TableDesSymboles::getSymbole(int id)
{
	if (tableSymboles.find(id) == tableSymboles.end())		
	    return 0; // pas trouver
	
	return tableSymboles[id]; // sinon on le renvoi.
}

void TableDesSymboles::afficher(int num) {
}


