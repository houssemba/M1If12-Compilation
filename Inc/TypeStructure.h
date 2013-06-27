#ifndef __TYPE_STRUCTURE_H
#define __TYPE_STRUCTURE_H

#include "Type.hpp"
#include "TypeTableau.h"
//#include <pair>
#include <vector>


class TypeStructure : public Type
{
	private:
	std::vector<std::pair<int, Type*> > champs;
	
	static int taille(Type * t);
	
	public:
	TypeStructure(std::vector<std::pair<int, Type*> > & lesChamps);
	
	bool operator==(Type const & type) const;
	
	bool estStructure() const { return true; }
	
	void printToStd() const;
	
	std::vector<std::pair<int, Type*> > getChamps() { return champs; }
	
	static int decalage(TypeStructure const & t, int id);
	
	bool isField(int id);
	
	Type* getTypeField(int id);

};































#endif
