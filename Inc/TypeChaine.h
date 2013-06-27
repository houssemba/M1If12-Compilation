#ifndef __TYPE_CHAINE_H
#define __TYPE_CHAINE_H


#include "Type.hpp"


class TypeChaine : public Type
{
	public:
	TypeChaine();
	bool operator==(const Type & type) const;

    bool estChaine() const {return true;}
    
    void printToStd() const;
};












#endif
