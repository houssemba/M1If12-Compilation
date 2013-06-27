#ifndef __GENERATEUR_TYPE_H
#define __GENERATEUR_TYPE_H

#include "Valeur.h"
#include <vector>
class Type;

class GenerateurType
{
	public:
	static Type* creerTypeEntier();
	static Type* creerTypeReel();
	static Type* creerTypeBooleen();
	static Type* creerTypeChar();
	static Type* creerTypeChaine();
	
	static Type* creerTypePointeur(Type* typePointed);
	
	static Type* creerTypeEnum(std::vector<int> & valueList);
	
	static Type* creerTypeInterval(Type* borneType, Valeur bInf, Valeur bSup);
	
	static Type* creerTypeTableau(Type * typeContained, std::vector<Type*> const & dimsList); 

	static Type* creerTypeStructure(std::vector<std::pair<int, Type*> > & lesChamps);
	
};














#endif
