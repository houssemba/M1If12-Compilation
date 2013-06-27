#ifndef __SYMBOLE_PROCEDURE_H
#define __SYMBOLE_PROCEDURE_H

#include "Symbole.hpp"
#include <ConteneurCode.h>

#include <vector>

class TableDesSymboles;

class SymboleProcedure : public Symbole
{
	private:
	int arite;
	ConteneurCode code;
	std::vector<int> params;//list des param sous forme d'identifiant.
	std::vector<Type*> paramType;
	std::vector<bool> constant;
	
	TableDesSymboles * ts;
	
	public:
	SymboleProcedure(int arite, int id);
	
	void printToStd();
	
	bool estProcedure() { return true; }
	
	
	void printCode() { code.printToStd(); }
	
	void pushCode(ConteneurCode const& code) { this->code.push(code); }
	void pushCode(Instruction const& instr) { this->code.push(instr); }
	
	void setTS(TableDesSymboles * ts) { this->ts = ts; }
	
	TableDesSymboles * getTS() { return ts; }
	
	void ajouterParam(int id, Type * typeParam, bool modeConstant) { params.push_back(id); paramType.push_back(typeParam); constant.push_back(modeConstant); }
	
	Type * getTypeParam(int position) { return paramType.at(position); }
	
	bool estParamConstant(int position) { return constant.at(position); }
	
	int getArite() { return arite; }

};























#endif
