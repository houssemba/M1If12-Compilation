#ifndef __TableDesSymboles_HPP__
#define __TableDesSymboles_HPP__

#include <vector>
#include <map>
#include "Symbole.hpp"
using namespace std;
/**
 * \file TableSymboles.hpp
 * \brief En-tete de la table des symboles
 * \author JeanMichel LE
 * \version 0.1
 * \date 13 octobre 2012
 *
 * Table des symboles pour le compilateur
 *
 */

/*! 
 * \class TableDesSymboles
 * \brief classe representant le tableau des symboles
 *
 * La classe le tableau des symboles
 */
class TableDesSymboles {

    private:
        map<int, Symbole*> tableSymboles; /*!< la table des symboles, lie un identifiant à un symbole. */
        int numContexte; /*!< num du contexte où on se trouve !!! SERVIRA SUREMENT A RIEN*/
        std::string name;
        TableDesSymboles * tsParent; /*!< La table des symboles parente de la table courante. */
        
        TableDesSymboles();
        
    public:
        // ##### CONTRUCTEUR & DESCTRUCTEUR #####

        /*!
         * \brief Constructeur de la table des symboles avec son nom et son parent
         * Constructeur par défaut de la classe table des symboles
         */
        TableDesSymboles(std::string name, TableDesSymboles * parent);
        
        /*!
         * \brief Destructeur
         * Destructeur de la classe table des symboles
         */
        ~TableDesSymboles();
        
        // ##### GETTEUR #####
        
        /*!
         * \brief Recupere le numero du contexte de la TDS !!! DEPRECATED !!!
         */         
        int getNumContexte();
        
        int getNumContexteTSActuel(bool incrementation);
        
        // ##### SETTEUR #####
        
        /*!
         * \brief change le numero de context de la table
         * \param i le num de contexte de la TDS
         */  
        void setNumContexte(int i);
        
        /*!
         * \brief Recupere la TDS
         */         
        //vector<Symbole*> getTableSymboles();
        
        // ##### FONCTION #####

        /*!
         * \brief Ajoute un symbole en correspondance à son identifiant dans la table des symboles
         * \param symbole l'adresse du symbole
         */
        void ajouter(int identifiant, Symbole* symbole);
        
        /*!
         * \brief Affiche la table des symbole
         */         
        void afficher();
         
        /*!
         * \brief Affiche la table des symbole d'un contexte
         * \param numContexte la table du contexte
         */         
        void afficher(int num);
        // renvoi le parent de la table !!! ATENTION !!! est NULL pour le contexte du program.
        TableDesSymboles* getParent() { return tsParent;}
        // test si a un parent
        bool hasParent() { return tsParent != 0; }
        // le nom du contexte.
        std::string getName() { return name;}
        
		Symbole* getSymbole(int id);  // cherche et renvoi le sumbole ayant cette id , NULL sinon.        
        
        
        
    
};

#endif
