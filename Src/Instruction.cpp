#include <Instruction.h>
#include <MapIdent.h>
#include <iostream>

extern MapIdent identTable;

using std::cout;
using std::endl;



Instruction::Instruction(CodeInstruction operation, Operande oRes, Operande o1, Operande o2)
	: etiquetteIdent(-45), _hasEtiquette(false), operation(operation), oRes(oRes), o1(o1), o2(o2)
{
}

Instruction::Instruction(CodeInstruction operation, Operande oRes, Operande o1, Operande o2, int etiquetteIdent)
	: etiquetteIdent(etiquetteIdent), _hasEtiquette(true), operation(operation), oRes(oRes), o1(o1), o2(o2)
{
}


void Instruction::printToStd()
{

	if(_hasEtiquette) { cout << identTable.getName(etiquetteIdent) << "	";}// afficher l'etiquette
	else 			  cout << "		";
	
	if (operation == OPCODE_NONE) 	return;
	if (operation == OPCODE_CPY ) {
		oRes.printToStd(); cout << " = "; o1.printToStd();	
		return;
	}
	if (operation == OPCODE_RRT) {
		oRes.printToStd(); cout << " = *"; o1.printToStd();
		return;
	}	
	if (operation == OPCODE_RLT) {
		cout << "*"; oRes.printToStd(); cout << " = "; o1.printToStd();
		return;
	}
	if (operation == OPCODE_PTR) {
		oRes.printToStd(); cout << " = &"; o1.printToStd();
		return;
	}
	if (operation == OPCODE_ART) {
		oRes.printToStd(); cout << " = "; o1.printToStd(); cout << " ["; o2.printToStd(); cout << "]";
		return;
	}
	if (operation == OPCODE_POP) {
		cout << "pop "; oRes.printToStd();
		return;
	}
	if (operation == OPCODE_RET) {
		cout << "return";
		return;
	}
	if (operation == OPCODE_RETV) {
		cout << "return "; oRes.printToStd();
		return;
	}
	if (operation == OPCODE_PSH) {
		cout << "push "; oRes.printToStd();
		return;
	}
	if (operation == OPCODE_PSP) {
		cout << "push &"; oRes.printToStd();
		return;
	}
	if (operation == OPCODE_CLL) {
		cout << "call "; oRes.printToStd();
		return;
	}
	if (operation == OPCODE_NOT) {
		oRes.printToStd(); cout << " = !"; o1.printToStd();
		return;
	}
	if (operation == OPCODE_NEG) {
		oRes.printToStd(); cout << " = -"; o1.printToStd();
		return;
	}
	if (operation == OPCODE_JMP) {
		cout << "Aller à "; oRes.printToStd();
		return;
	}
	if (operation == OPCODE_JMPC) {
		cout << "Si "; oRes.printToStd(); cout << " Aller à "; o1.printToStd(); 
		return;
	}
	oRes.printToStd();
	cout << " = "	;
	o1.printToStd();
	if (operation == OPCODE_ADD)	cout << " + ";
	if (operation == OPCODE_SUB)	cout << " - ";
	if (operation == OPCODE_MUL)	cout << " * ";
	if (operation == OPCODE_DIV)	cout << " / ";
	if (operation == OPCODE_AND)	cout << " && ";
	if (operation == OPCODE_OR)		cout << " || ";
	if (operation == OPCODE_EQ)		cout << " == ";
	if (operation == OPCODE_NEQ)	cout << " != ";
	if (operation == OPCODE_LT)		cout << " < ";
	if (operation == OPCODE_LE)		cout << " <= ";
	if (operation == OPCODE_GT)		cout << " > ";
	if (operation == OPCODE_GE)		cout << " >= ";
	o2.printToStd();
}
