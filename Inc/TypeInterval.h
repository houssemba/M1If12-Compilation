#ifndef __TYPE_INTERVAL_H
#define __TYPE_INTERVAL_H

#include "Type.hpp"
#include "Valeur.h"

class TypeInterval : public Type
{
	private:
	
	Type * type;// le type des valeur extremité
	Valeur inf;
	Valeur sup;
	
	public:
	
	TypeInterval(Type * typeOfBorne, Valeur borneInf, Valeur borneSup);
	
	bool operator==(Type const & type) const;
	
	bool estInterval() const { return true; }
	
	void printToStd() const;
	
	Type * getTypeBorne() const { return type; }
	
	
	Valeur getInf() const { return inf; }
	Valeur getSup() const { return sup; }
};




















#endif
