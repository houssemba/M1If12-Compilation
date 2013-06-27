#ifndef __GESTIONTDS_HPP__
#define __GESTIONTDS_HPP__

#include "TableDesSymboles.hpp"
#include <iostream>
/**
 * \file GestionTDS.hpp
 * \brief En-tete du gestionnaire de la table des symboles
 * \author JeanMichel LE
 * \version 0.1
 * \date 27 octobre 2012
 *
 * Gestion de l'ensemble des tables des symboles
 */
using namespace std;

/*! 
* \class GestionTDS
* \brief classe qui gere l'ensemble des tables des symboles
*
*  La classe gere les table des symboles
*  Conserve l'ordre des TDS
*/
class GestionTDS {
    
    private:
        vector<TableDesSymboles*> lstTDS;
        TableDesSymboles *couranteTDS;
        TableDesSymboles *precedanteTDS;//  pour conserver le context courant si ajout d'une TDS sans pere (record).
        int numeroContexteTDS;
        
        /*!
         * \brief Ajoute une TDS 
         */ 
        void ajouterTDS(TableDesSymboles *tds); // pour n'utiliser que startContext().
        
    public:
        /*!
         * \brief Constructeur par defaut
         * Constructeur du gestionnaire des TDS
         */
        GestionTDS();
        
        /*!
         * \brief Destructeur par defaut
         * Destructeur du gestionnaire des TDS
         */        
        ~GestionTDS();
        
        
        
        /*!
         * \brief Getteur sur le numero de contexte courant
         */        
        int getNumContexte();
        
        /*!
         * \brief Getteur sur la TDS courante
         */  
        TableDesSymboles* getContext() { return couranteTDS; }
        
        /*!
         * \brief Ajoute un symbole a la table courante
         */        
        void ajouter(Symbole * s);
        
        /*!
         * \brief Commence un nouveau context
         * \param t la table courante
         * La table t devient la table des symboles du context courant
         */
        void startContext(TableDesSymboles *t); 
        
        /*!
         * \brief Reviens au contexte avant startContext
         */
        void endContext();
        
        /*!
         * \brief Recupere le symbole de la TDS courante
         * \param identSymbole le numero du symbole
         */
        Symbole * getSymbole(int identSymbole);
        
        /*!
         * \brief Affiche l'ensemble des tables des symboles
         */
        void afficheGestionTDS();   
        
        void afficheCode3ad();
};
#endif
