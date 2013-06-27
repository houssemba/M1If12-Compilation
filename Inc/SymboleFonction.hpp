#ifndef _SYMBOLEFONCTION_HPP_
#define _SYMBOLEFONCTION_HPP_

#include <iostream>
#include "Symbole.hpp"
#include "Type.hpp"
#include "MapIdent.h"
#include <ConteneurCode.h>

#include <vector>

class TableDesSymboles;

extern MapIdent identTable;
/**
 * Gestion d'une fonction.
 */
class SymboleFonction : public Symbole {
    
	private:
    	int numTDS; /*!< num TDS de dans laquelle la fonction est déclarée */
	    int arite; /*!< nombre d'arguments de la fonction */
        Type *typeResultat;
        ConteneurCode code;
        std::vector<int> params;//list des param sous forme d'identifiant.
		std::vector<Type*> paramType;
		std::vector<bool> constant;
	
		TableDesSymboles * ts;
		
		int resultat;// un ident qui sera un temporaire
        
	public:
        /*!
         * \brief Constructeur
         * \param id id du symbole
         * \param arite nombre d'args
         * \param nomTDS TDS 
         */
        SymboleFonction(Type *t, int id, int arite, int TDS);
        /**
        * \brief Destructeur
        */
        ~SymboleFonction();	
        
        /**
         * \brief Getteur pour la TDS
         * \return num de la TDS ou la fct a ete declare
        */
        int getNomTDS();
    
        /**
         * \brief Getteur pour le nb de args 
         * \return retourne un entier contenant l'arité de la fonction
         */
        int getArite();
        
        /**
         * \brief affiche les infos de la fonction
         */
        void printToStd();
        
        bool estFonction() { return true; }
        
        Type* getType() { return typeResultat; }
        
        
	void printCode() { code.printToStd(); }
	
	void pushCode(ConteneurCode const& code) { this->code.push(code); }
	void pushCode(Instruction const& instr) { this->code.push(instr); }
	
	void setTS(TableDesSymboles * ts) { this->ts = ts; }
	
	TableDesSymboles * getTS() { return ts; }
	
	void ajouterParam(int id, Type * typeParam, bool modeConstant) { params.push_back(id); paramType.push_back(typeParam); constant.push_back(modeConstant); }
	
	void setTemporaireResultat(int id) { resultat = id; }
	int getResultat() { return resultat; }
	
	Type * getTypeParam(int position) { return paramType.at(position); }
	
	bool estParamConstant(int position) { return constant.at(position); }
	
	
};
#endif
