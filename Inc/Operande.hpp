#ifndef __OPERANDE_HPP__
#define __OPERANDE_HPP__

#include "Valeur.h"
#include "Type.hpp"
#include "TypeEntier.h"
#include "Symbole.hpp"
#include "MapIdent.h"

/**
 * \file Operande.hpp
 * \brief En-tete d
 * \author JeanMichel LE
 * \version 0.1
 * \date 5 novembre 2012
 *
 * La classe Operande qui décrit une opérande d'une instruction 3 adresses. 
 * Cette opérande sera décrite soit par une valeur, soit par le numéro associé à un identificateur.
 */
 
//extern MapIdent identTable; si besoin de la table des idents
 
class Operande {

    private:
        bool operandeIdentifiant; /*!< indique si l'opérande est un ident ou une valeur, 
                                        vrai = ident ; faux = valeur */
        int identifiant; /*!< iden du symbole de l'opérande (valeur -> NULL) */
        Valeur valeur; /*!< valeur de l'opérande */
    
    public:
    //##### CONSTRUCTEUR & DESTRUCTEUR #####
        /**
         * \brief constructeur par valeur
         * \param pValeur de l'opérande
         */
        Operande(Valeur pValeur);
		
		/**
		 * \brief Constructeur d'un identifiant
		 * \param pType type de la valeur de l'opérande
		 * \param pIdent entier qui est l'identifiant dans la table des idents
		 */
		Operande(int pIdent);
		
		void printToStd();
        /**
         * \brief constructeur par ident et valeur
         * \param pValeur valeur de l'opérande
         * \param pIdent identifiant du symbole de l'opérande
         */
        //Operande(Valeur pValeur, int pIdent);
        
       	/**
		 * \brief Constructeur d'une opérande INTEGER
		 * \param pType type de la valeur de l'opérande
		 * \param pValInt entier intitialisant la valeur de l'opérande
		 */
		//Operande(int pValInt);
		
		

		/**
		* \brief Constructeur d'une opérande REEL
		* \param pType type de la valeur de l'opérande
		* \param pValFloat reel intitialisant la valeur de l'opérande
		*/
		//Operande(float pValFloat);
	
		/**
		 * \brief Constructeur d'une opérande STRING
		 * \param pType type de la valeur de l'opérande
		 * \param pValString string intitialisant la valeur de l'opérande
		 */
		//Operande(string *pValString);

		/**
		 * \brief Constructeur d'une opérande BOOLEAN
		 * \param pType type de la valeur de l'opérande
		 * \param pValBool booleen intitialisant la valeur de l'opérande
		 */
		//Operande(bool pValBool);
        		
		/**
 		 * \brief Destructeur
		 */
        ~Operande();
        
    //##### GETTEUR & SETTEUR #####
		/**
		 * \brief getteur valeur
		 * \return valeur
		 */
		Valeur getValeur() { return this->valeur; }

		/**
		 * \brief getteur du numero de symbole
		 * \return symbole
		 */
		int getSymbole() { return this->identifiant; }
		
		/**
		 * \brief getteur type
		 * \return UnionType enum dans la structure valeur
		 */
		UnionType getType() { return this->valeur.unionType; }
		
		/**
		 * \brief indique si l'opérande est un identifant
		 * \return bool
		 */
		bool isIdentifiant() { return this->operandeIdentifiant; }
	
	//##### METHODES #####
	    /**
	     * \brief Indique si les type sont compatible
         * \param pType1 type de la premiere operande
         * \param pType1 type de la premiere operande
	     * \return boolean
	     */
	    bool compactibleType(Valeur *pVal1, Valeur *pVal2);
	    
	    /**
	     * \brief Indique si les type sont les compatible
	     * \param pType1 type de la premiere operande
	     * \param pType2 chaine de la premiere operande (variable ???)
	     \return boolean
	     */
	    bool compactibleType(Type *pType1, string *pType2);
	    
	    /**
	     * \brief Va evaluer faire l'operation entre deux operandes
	     * \param pSymboleRetour le résultat
	     * \param pExpr1 premiere operande
	     * \param pExpr2 second operande
	     * \param pOperation l'operation
	     * \param pOperande avec bien init operandeIdentifiant et valeur correct
	     */
	    Operande *operation(Symbole* pSymboleRetour, Operande *pExpr1, Operande *pExpr2, string pOperation);
        
};
#endif



