#ifndef __TYPE_HPP__
#define __TYPE_HPP__

#include <iostream>
#include <string>
/**
 * \file Type.hpp
 * \brief En-tete du type de symbole
 * \author JeanMichel LE
 * \version 0.1
 * \date 13 octobre 2012
 *
 * Le type d'un symbole
 *
 */
using namespace std;

/*! 
* \class Type
* \brief classe representant un type
*
*  Classe qui permet de définir un type a un symbole
*/
class Type {

    protected:
    string nom; /*!< entier, reel, booleen, pointeur, tableau ... */
    
    
    /*!
     * \brief Constructeur
     * Constructeur de la classe Type
    */
    Type();
    
    /*!
     * \brief Constructeur
     * Constructeur de la classe Type avec un type
     * \param type définie un type
    */    
    Type(const Type &t);
    
    /*!
     * \brief Constructeur
     * Constructeur de la classe Type avec un nom
     * \param nomType définie un nom au type
    */
    Type(string const &nomType);
    
    /*!
     *  \brief Destructeur
     *  Destructeur de la classe Type
     */
    ~Type();

    public:
    /**
    *   \brief geteur type ---> deprecated
    *   \return Retourne le type
    */
    string getStringType() {return nom;}
    
    virtual bool operator==(const Type & _type) const = 0;
    
    virtual bool estEntier() const{return false;}
    virtual bool estReel() const {return false;}
    virtual bool estBooleen() const {return false;}    
    virtual bool estChar() const {return false;}
    virtual bool estChaine() const {return false;}
    virtual bool estPointeur() const {return false;}
    virtual bool estTableau() const {return false;}
    virtual bool estStructure() const {return false;}
    virtual bool estInterval() const {return false;}
    virtual bool estEnum() const {return false;}
    
    virtual void printToStd() const = 0; // doit etre implementer ds tous les type dérivé
    
    static bool compatiblePlus(Type const & t1, Type const & t2);
    static bool compatibleAffect(Type const & t1, Type const & t2);
    static bool compatibleMult(Type const & t1, Type const & t2);
    static bool compatibleDiv(Type const & t1, Type const & t2);
    static bool compatibleDividente(Type const &t1, Type const &t2);
    
    static bool compatibleComparaison(Type const & t1, Type const & t2);
    
    static bool compatibleNegation(Type const &t1);
};

#endif
