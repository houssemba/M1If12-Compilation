#include "GenerateurType.h"
#include "TypeEntier.h"
#include "TypeReel.h"
#include "TypeBooleen.h"
#include "TypeChar.h"
#include "TypeChaine.h"
#include "TypePointeur.h"
#include "TypeEnum.h"
#include <TypeInterval.h>
#include <TypeTableau.h>
#include <TypeStructure.h>


Type* GenerateurType::creerTypeEntier() 
{
	return new TypeEntier();
}

Type* GenerateurType::creerTypeReel()
{
	return new TypeReel();
}

Type* GenerateurType::creerTypeBooleen()
{
	return new TypeBooleen();
}

Type* GenerateurType::creerTypeChar()
{
	return new TypeChar();
}

Type* GenerateurType::creerTypeChaine()
{
	return new TypeChaine();
}

Type* GenerateurType::creerTypePointeur(Type* typePointed)
{
	return new TypePointeur(typePointed);
}

Type* GenerateurType::creerTypeEnum(std::vector<int> & valueList)
{
	return new TypeEnum(valueList);
}

Type* GenerateurType::creerTypeInterval(Type* borneType, Valeur bInf, Valeur bSup)
{
	return new TypeInterval(borneType, bInf, bSup);
}

Type* GenerateurType::creerTypeTableau(Type * typeContained, std::vector<Type*> const & dimsList)
{
	return new TypeTableau(typeContained, dimsList);
}

Type* GenerateurType::creerTypeStructure(std::vector<std::pair<int, Type*> > & lesChamps)
{
	return new TypeStructure(lesChamps);
}







