#include "Operande.hpp"
#include <iostream>

extern MapIdent identTable;
using std::cout;


Operande::Operande(Valeur pValeur) {	
    // Opérande est une valeur
    operandeIdentifiant = false;
    identifiant = -45;
    valeur = pValeur;
}

Operande::Operande(int pIdent) {
    // recupere 
    //int id = identTable.getId(pIdent);

//     if (pIdent != NULL) {
//         // Identifiant(Symbole) est VARIABLE ou TEMPORAIRE
//         if((pIdent->getCategorie() == "variable ") || (pIdent->getCategorie() == "temporaire")) {	
//             identifiant = pIdent;
//             valeur = pValeur;
//         } else { 
//             identifiant = pIdent; 
//             valeur = NULL; 
//         }
//         operandeIdentifiant = true;
//     } else {
//         operandeIdentifiant = false; 
//         valeur = pValeur; 
//         pIdent = NULL;
//     }
    // Opérande est un identifiant
    operandeIdentifiant = true;
    identifiant = pIdent;
}

void Operande::printToStd()
{
	if (isIdentifiant())	cout << identTable.getName(identifiant);
	else 					::printToStd(valeur);
}
// 
// Operande::Operande(int pValInt) {
//     operandeIdentifiant = false;
//     valeur.unionType = INT;
//     valeur.entier = pValInt;
// };
// 
// 		
// Operande::Operande(float pValFloat) {
//     operandeIdentifiant = false;
//     valeur.unionType = FLOAT;
//     valeur.reel = pValFloat;
// };
// 		
// Operande::Operande(string *pValString) {
//     operandeIdentifiant = false;
//     valeur.unionType = STRING;
//     valeur.chaine = pValString;
// };
// 		
// Operande::Operande(bool pValBool) {
//     operandeIdentifiant = false;
//     valeur.unionType = BOOLEAN;
//     valeur.booleen = pValBool;
// };

// ##### METHODE #####
bool Operande::compactibleType(Valeur *pVal1, Valeur *pVal2) {
    //pour l'instant ne gere que si les deux valeur sont iendtique
    return (pVal1 == pVal2);
};

Operande *operation(Symbole* pSymboleRetour, Operande *pExpr1, Operande *pExpr2, string pOperation) {
    
    int operation = 0;
    
    //Symbole *symboleRetour = pSymboleRetour;
    Operande *exprRetour;
    
    if      (pOperation == "+")	    operation = 1;
	else if (pOperation == "-") 	operation = 2;
	else if (pOperation == "*") 	operation = 3;	
	else if (pOperation == "/")	    operation = 4;
	else if (pOperation == "div") 	operation = 5;
	else if (pOperation == "mod") 	operation = 6;
	else if (pOperation == "-a") 	operation = 7; //chiffre negatif
	else if (pOperation == "+a") 	operation = 8; //chiffre posifit
	else if (pOperation == ":=")    operation = 9;
	else 				            operation = 0;
    
    // verification du typage
    if ((pExpr1->getValeur() == pExpr2->getValeur()) || ((pExpr1 != NULL ) && (pExpr2 == NULL))) {
        switch (pExpr1->getValeur().unionType) {
            case INT:
                switch (operation) {
                    case 1 : // + de deux entier
                        exprRetour = new Operande(pExpr1->getValeur().entier+pExpr2->getValeur().entier);
                        break;
                    case 2 : // - de deux entier
                        exprRetour = new Operande(pExpr1->getValeur().entier - pExpr2->getValeur().entier);
                        break;
                    default:
                        break;
                }
                break;
            case FLOAT:
                break;
            case STRING:
                break;
            case BOOLEAN:
                
                break;
            default:
                cerr << "Erreur : type inconnu \n";
        }
    } else {
    }
    
    return exprRetour;
};


Operande::~Operande() {
    //suppression du symbole
    // delete identifiant;
    // suppression de valeur ??
};
