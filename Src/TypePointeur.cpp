#include <TypePointeur.h>
#include <SymboleTemporaire.hpp>
#include <iostream>


TypePointeur::TypePointeur(Type * TypePointed)
	: Type(""), typePointed(TypePointed)
{
	//idPointed = SymboleTemporaire::creerTemporaire(typePointed);
}

bool TypePointeur::operator==(const Type & type) const	
{
	const TypePointeur * t = dynamic_cast<const TypePointeur*>(&type);
	return (t!=0 && *typePointed==*(t->typePointed));// si c'est un type pointeur on verifie qu'ils pointent sur le meme type.
}


void TypePointeur::printToStd() const
{
	std::cout << "^";
	typePointed->printToStd();
}
