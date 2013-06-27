#ifndef __TYPE_REEL_H
#define __TYPE_REEL_H


#include "Type.hpp"


class TypeReel : public Type
{
	public:
	TypeReel();
	bool operator==(const Type & type) const;

    bool estReel() const {return true;}
    
    void printToStd() const;
};















#endif
