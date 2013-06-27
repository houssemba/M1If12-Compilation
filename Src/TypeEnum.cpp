#include <TypeEnum.h>
#include <iostream>
#include <MapIdent.h>

extern MapIdent identTable;



TypeEnum::TypeEnum(std::vector<int> & listIdent)
	: Type(""), valueList(listIdent)
{
}


bool TypeEnum::operator==(const Type & type) const
{
	TypeEnum const * t = dynamic_cast<const TypeEnum*>(&type);
	if (t==0)	return false;// n'est meme pas une enum
	
	if (valueList == t->getValueList())	return true;
	
	return false;
}


void TypeEnum::printToStd() const
{
	std::cout << "(";
	for (unsigned int i=0; i < valueList.size(); i++) {
		std::cout << identTable.getName(valueList.at(i));
		if (i!= valueList.size()-1)	std::cout << ",";
	}
	
	std::cout << ")";
}
