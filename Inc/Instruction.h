#ifndef __INSTRUCTION_H
#define __INSTRUCTION_H

#include "Code3ad.hpp"
#include "Operande.hpp"


class Instruction
{
	private:
	int etiquetteIdent;
	bool _hasEtiquette;
	
	CodeInstruction operation;
	
	Operande oRes;
	Operande o1;
	Operande o2;
			
	public:
	Instruction(CodeInstruction operation, Operande oRes, Operande o1, Operande o2);// sans etiquette
	Instruction(CodeInstruction operation, Operande oRes, Operande o1, Operande o2, int etiquette); // avec etiquette
	
	void printToStd();
};

























#endif
