#ifndef __TYPE_ENTIER__H
#define __TYPE_ENTIER__H

#include "Type.hpp"

#include <string>

class TypeEntier : public Type 
{

	public:
	TypeEntier();
	
	bool operator==(const Type & _type) const;

    bool estEntier() const {return true;}
    
    void printToStd() const;
};





#endif
