#include "SymboleFonction.hpp"

SymboleFonction::SymboleFonction(Type* t, int id, int arite, int numTDS) : Symbole("fonction", id), typeResultat(t) {
	this->numTDS = numTDS;
	this->arite = arite;
}

int SymboleFonction::getNomTDS() { 
    return numTDS;
}

int SymboleFonction::getArite() { 
    return arite;
}

void SymboleFonction::printToStd() {
	cout << "arite:" << arite << ",typeretour:";
	typeResultat->printToStd();
	//cout<< " est dans la TDS : " << numTDS 
	std::cout << std::endl;
}

SymboleFonction::~SymboleFonction() {

}

