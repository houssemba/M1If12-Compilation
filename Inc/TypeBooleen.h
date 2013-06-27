#ifndef __TYPE_BOOLEEN_H
#define __TYPE_BOOLEEN_H


#include "Type.hpp"


class TypeBooleen : public Type
{
	public:
	TypeBooleen();
	bool operator==(const Type & type) const;
	
	bool estBooleen() const {return true;}
	
	void printToStd() const ;
};












#endif
