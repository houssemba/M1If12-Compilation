#ifndef __OPERATION_HPP__
#define __OPERATION_HPP__

#include "Valeur.h"
#include "Type.hpp"
#include "TypeEntier.h"
#include "Symbole.hpp"

class Operation {

    private:
        bool operationIdent;
        Symbole *identifiant;
        Valeur *valeur;
    
    public:
        Operation();
        ~Operation();
};
#endif



