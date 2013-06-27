#include <iostream>
#include <stdio.h>
#include <Actions.h>

#include "TableDesSymboles.hpp"
#include "GestionTDS.hpp"
#include "MapIdent.h"
//#include <TableSymboles.hpp>// a modif______________________________________

#include "TypeEntier.h"

// fonction utile :
std::string toString(bool b) { if (b) return "true"; /*else*/return "false";}

extern int yyparse();
// _______________________________ VARIABLE GLOBALE ____________________________________________
MapIdent identTable;
//TableDesSymboles tableSymbole(std::string(""), (TableDesSymboles*)0); // a modifier avec un gestionnaire de TS

//table temporaire des differents contexte
//TableDesSymboles TDStmp(std::string(""), (TableDesSymboles*)0);

// Creation du gestion de la TDS
GestionTDS listTDS;

int main(int argc, char* argv[])
{
	yyparse();
	
	// affiche la table des identifiants.
	identTable.printToStd();
	
	//affiche les tables des symboles.

    listTDS.afficheGestionTDS();
    
    listTDS.afficheCode3ad();
	
	return 0;
}
