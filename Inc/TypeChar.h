#ifndef __TYPE_CHAR_H
#define __TYPE_CHAR_H


#include "Type.hpp"


class TypeChar : public Type
{
	public:
	TypeChar();
	bool operator==(const Type & type) const;

    bool estChar() const {return true;}
    
    void printToStd() const;
};












#endif
