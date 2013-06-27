#ifndef __TYPE_POINTEUR_H
#define __TYPE_POINTEUR_H


#include "Type.hpp"


class TypePointeur : public Type
{
	
	public:
	TypePointeur(Type * TypePointed);
	bool operator==(const Type & type) const;

    bool estPointeur() const {return true;}
    
    void printToStd() const;

	//attributs mit en public pour gagner du tps --> NE PAS EN ABUSER
	Type * typePointed;// en public for convenience.
	//int idPointed; // l'identifiant pointer on cree une variable tempo pour stocker.
};























#endif
