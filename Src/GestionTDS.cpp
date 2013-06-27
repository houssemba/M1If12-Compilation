#include "Symbole.hpp"
#include "GestionTDS.hpp"
#include <MapIdent.h>
#include <SymboleProgram.h>
#include <SymboleFonction.hpp>
#include <SymboleProcedure.h>

extern MapIdent identTable;

/**
 * \file GestionTDS.cpp
 * \brief Gestionnaire de la table des symboles
 * \author JeanMichel LE
 * \version 0.1
 * \date 27 octobre 2012
 *
 * Gestion de l'ensemble de la table des symboles
 *
 */
 
GestionTDS::GestionTDS() 
{
    numeroContexteTDS = 0;
    precedanteTDS = 0;
}

GestionTDS::~GestionTDS() {
}

void GestionTDS::startContext(TableDesSymboles *t) {
    ajouterTDS(t);
}

void GestionTDS::ajouterTDS(TableDesSymboles *tds) {
    tds->setNumContexte(lstTDS.size()+1);
    numeroContexteTDS = lstTDS.size()+1;
    lstTDS.push_back(tds);
	if (!tds->hasParent())	precedanteTDS = couranteTDS;
    couranteTDS = tds;
}

void GestionTDS::endContext() {
    if(couranteTDS->hasParent()) {
    	couranteTDS = couranteTDS->getParent();
    }else {
    	couranteTDS = precedanteTDS; // ne passe plus par le pere de la courante peut etre null (record)
    }
    
    //precedanteTDS = precedanteTDS->getParent();
}


void GestionTDS::ajouter(Symbole *s) {
    couranteTDS->ajouter(s->getId(), s);
}

int GestionTDS::getNumContexte() {
    return numeroContexteTDS;
}

void GestionTDS::afficheGestionTDS() {
	cout << "###################### ENSEMBLE DES TDS" << endl;
    for (unsigned int i=0; i < lstTDS.size(); i++) {
        
		cout << "Table Des Symboles TS num=" << lstTDS[i]->getNumContexte() << endl;
		lstTDS[i]-> afficher();
		cout << "--------------------" << endl;
	}
	cout << "###################### FIN DES TDS" << endl;
}


Symbole * GestionTDS::getSymbole(int identSymbole)
{
	TableDesSymboles * tds = couranteTDS;
	Symbole * ret = 0;
	
	while(true) // pas infin car on sort si on a trouver le symbole ou si on a fai tte les tds -> plus de parent
	{
		ret = tds->getSymbole(identSymbole);
		if (ret != 0 || !tds->hasParent())	break;// trouver --> on sort ou c'est la tds du program --> on sort.
		tds = tds->getParent();
	}
	
	return ret;
}


void GestionTDS::afficheCode3ad()
{
	for (unsigned int i=0; i<lstTDS.size(); i++)
	{
		if (!lstTDS.at(i)->hasParent() && i!=0)	continue;
		if (i==0) {
			Symbole * s = getSymbole(identTable.getId(lstTDS.at(i)->getName()));
			SymboleProgram * sp = dynamic_cast<SymboleProgram*>(s);
			cout << "** Code (" << lstTDS.at(i)->getName() <<")" <<endl;
			sp->printCode();
			continue;
		}
		TableDesSymboles * TS = lstTDS.at(i)->getParent();
		Symbole * s = TS->getSymbole(identTable.getId(lstTDS.at(i)->getName()));
		if (s==0)	continue;// =0 quan c la TS d'un record l'ident du type record n'est pas ds sa TS et sa TS n'a pa de pere donc --> le trouve pas.
		
		if (s->estFonction()) {
			SymboleFonction * sf = dynamic_cast<SymboleFonction*>(s);
			cout << "** Code (" << lstTDS.at(i)->getName() <<")" <<endl;
			sf->printCode();
		}
		if (s->estProcedure()) {
			SymboleProcedure * sp = dynamic_cast<SymboleProcedure*>(s);
			cout << "** Code (" << lstTDS.at(i)->getName() <<")" <<endl;
			sp->printCode();
		}
	}
}






