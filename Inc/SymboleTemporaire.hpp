#ifndef __SYMBOLETEMPORAIRE_HPP__
#define __SYMBOLETEMPORAIRE_HPP__

#include "Symbole.hpp"
#include "Code3ad.hpp"
#include "Operande.hpp"

#include <string>
#include "Type.hpp"
using namespace std;

/**
 * Gestion d'une constante.
 */
class SymboleTemporaire : public Symbole  {
       
	private:
    	Type *type; 
    	static int nb;

	public:
        /**
         * \brief Constructeur, initialise le Temporaire
         * \param pType type du symboleTemporaire
         * \param pId ident depuis la table des indent
         */
        SymboleTemporaire(Type *pType, int pId);
        
        static int creerTemporaire(Type * type);
        
        bool estTemporaire() { return true; }

        /**
         * \brief Constructeur, initialise le Temporaire
         * \param pId identifiant du symbole
         * \param pNomTemporaire strin nom du symbole
         * \param pType type du symbole
         */
        //SymboleTemporaire(int pId, string pNomTemporaire, Type* pType);

        /**
         * \brief Accesseur
	     * \return Type
         */
    	Type* getType() { return this->type; }
    	
    	/**
    	 * \brief Affiche les informations sur le symboleTemporaire
    	 */
    	void printToStd();

        /**
         * \brief Destructeur
         */
        ~SymboleTemporaire();
};

#endif

