#ifndef __TYPE_ENUM_H
#define __TYPE_ENUM_H

#include "Type.hpp"
#include <vector>

class Type;

class TypeEnum : public Type
{
	private:
	std::vector<int> valueList;
	
	
	public:
	TypeEnum(std::vector<int> & listIdent); // cree une enum ayant pour valeur les identifiants listIdent qui seront une cste de ce type
	
	bool operator==(const Type & type) const;
	bool estEnum() const { return true; }
	
	std::vector<int> const & getValueList() const { return valueList; } 
	
	void printToStd() const;
};














#endif
