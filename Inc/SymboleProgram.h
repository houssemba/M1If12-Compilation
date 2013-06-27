#ifndef __SYMBOLE_PROGRAM_H
#define __SYMBOLE_PROGRAM_H

#include <iostream>
#include "Symbole.hpp"
#include <ConteneurCode.h>


class SymboleProgram : public Symbole
{
	private:
	ConteneurCode code;
	
	public:
	SymboleProgram(int identifiant) : Symbole("programme", identifiant), code() {}	
	
	void printToStd() { std::cout << std::endl;}// n'affiche rien pour un programme.
	
	void printCode() { code.printToStd(); }
	
	void pushCode(ConteneurCode const& code) { this->code.push(code); }
	
	bool estProgram() { return true; }
};








#endif
