#ifndef __CONTENEUR_CODE_H
#define __CONTENEUR_CODE_H

#include "Instruction.h"
#include <vector>


class ConteneurCode
{
	private:
	std::vector<Instruction> instructionList;
	
	public:
	ConteneurCode();
	
	void push(Instruction i);
	
	void push(std::vector<Instruction> const & list);
	
	void push(ConteneurCode const &c);
	
	void printToStd();

};























#endif
