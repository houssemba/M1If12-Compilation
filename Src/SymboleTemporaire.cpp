#include "SymboleTemporaire.hpp"
#include <MapIdent.h>
#include <GestionTDS.hpp>
#include <sstream>

extern MapIdent identTable;
extern GestionTDS listTDS;

int SymboleTemporaire::nb = 0;


SymboleTemporaire::SymboleTemporaire(Type *pType, int pId) : 
    Symbole("temporaire", pId), type(pType) {
}

// SymboleTemporaire::Temporaire(int pId, string pNomTemporaire, Type* pType) : Symbole("temporaire", pId) {
// 	//nomSymbole = new string(_nomTemporaire);
// 	//type = _type;
// }

void SymboleTemporaire::printToStd() {
	cout << "type:";
	type->printToStd();
    cout << endl;
}

SymboleTemporaire::~SymboleTemporaire() {
}



int SymboleTemporaire::creerTemporaire(Type * type)
{
	std::ostringstream ss;
	ss << nb;
	string nameTmp = "__%%__t" + ss.str();
	nb++;
	int ret = identTable.add(nameTmp);
	
	listTDS.ajouter( new SymboleTemporaire(type, ret) );
	
	return ret;
}

