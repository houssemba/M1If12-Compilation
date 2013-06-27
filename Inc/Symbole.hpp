#ifndef __SYMBOLE_HPP__
#define __SYMBOLE_HPP__

#include "Type.hpp"
#include <iostream>
/**
 * \file Symboles.hpp
 * \brief En-tete des symboles
 * \author JeanMichel LE
 * \version 0.1
 * \date 13 octobre 2012
 *
 * Gestion d'un symbole. Un symbole contient la partie "proprieté" de la table de symbole en plus de sa
   signification( const, var, prog...).
 *
 */
using namespace std;

/*! 
* \class Symbole
* \brief classe representant un symbole
*
*  La classe gere un symbole
*/
class Symbole {

    private:
        string categorie; /*!< variable, const, fonction, procedure ... */
        //Type* type; /*!< int, bool, char ... */
        int id;     /*!< ident du symbole */
        
    public:
        /*!
         * \brief Constructeur avec une catégorie
         * Constructeur de la classe Symbole
         * \param cat la catégorie du symbole
         * \param identifiant l'identifiant auquel le symbol est lié.
         */
        Symbole(string cat, int identifiant);
        
        virtual Type* getType() { return 0; }
        
        /*tous les symboles ecriront eux meme leur sorties(affichages).uniquement "proprieté" puis endl.*/
        virtual void printToStd() = 0;
        
        
		virtual bool estVariable() { return false; }
		virtual bool estConstante() { return false; }
		virtual bool estType() { return false; }
		virtual bool estProgram() { return false; }
		virtual bool estFonction() { return false; }
		virtual bool estProcedure() { return false; }
		virtual bool estChamp() { return false; }
		virtual bool estArgument() { return false; }
		virtual bool estTemporaire() { return false; }
		virtual bool estEtiquette() { return false; }
		
		bool estArgConstant();
         
        /*!
         *  \brief Destructeur
         *  Destructeur de la classe Symbole
         */
        ~Symbole();
        
        /**
         * \brief geteur catégorie
         * \return Retourne un string qui précise la catégorie du symbole
         */
        string getCategorie() {return categorie;}

        /**
         * \brief geteur type
         * \return Retourne l'adresse d'une instance de la classe Type
         */
        //virtual Type* getType() { return };

        /**
         * \brief geteur ident
         * \return Retourne l'id du symbole
         */
        int getId() {return this->id;}
};

#endif
