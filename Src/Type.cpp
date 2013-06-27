#include "Type.hpp"
#include <TypePointeur.h>
#include <TypeInterval.h>

#include <iostream>

/**
 * \file Type.cpp
 * \brief fonctions des types
 * \author JeanMichel LE
 * \version 0.1
 * \date 13 octobre 2012
 *
 * Gestion d'un type
 *
 */

/**
 * Les types : int, float, boolean, string, char, enum, interval, pointeur, struct, tableau
 */
 

Type::Type() {
}

Type::Type(string const & t) {
    nom = t;
}

Type::Type(const Type &type) {
	
	this->nom = type.nom;
}


Type::~Type() {
}

/**
 * int + real = OK
 */
bool Type::compatibleMult(Type const & t1, Type const & t2) { 
    bool calculable = false;
	
	if (t1.estEntier() || t1.estReel()) {
	    if (t2.estEntier() || t2.estReel()) {
	        calculable = true;
	    }
	}
	
	return calculable;
}

/**
 * int et real = ok
 */
bool Type::compatibleDiv(Type const & t1, Type const & t2) {
    bool calculable = false;
        
    if ((t1.estEntier() || t1.estReel()) || (t2.estEntier() || t2.estReel())) {
	    calculable = true;
	}
	
    return calculable;
}


/**
 * int et real = int
 * retourne tjr un integer
 **/
bool Type::compatibleDividente(Type const & t1, Type const & t2) {
    bool calculable = false;
        
    if ((t1.estEntier() || t1.estReel()) || (t2.estEntier() || t2.estReel())) {
	    calculable = true;
	}
	
    return calculable;
}


/**
 * int + int = int  
 * string1 + string2 = string1string2 
 * int + bool = int
 * int + real = real
 * char + string = string
 * char + char = string
 */
bool Type::compatiblePlus(Type const & t1, Type const & t2) {
    
    // addition de chaine
	if ((t1.estChaine() && t2.estChaine()) ||
	    (t1.estChar() && t2.estChaine()) ||
	    (t1.estChaine() && t2.estChar()) ||
	    (t1.estChar() && t2.estChar()) ) {
		return true; //str op str
	}	
	
	if (t1.estEntier() || t1.estReel() || t1.estBooleen()) {
		if (t2.estEntier() || t2.estReel() || t2.estBooleen()) 	return true;
		else 													return false;
	}

	return false;
}

bool Type::compatibleAffect(Type const & t1, Type const & t2)
{
    // affectation char + string = string
    if ((t1.estChaine() && t2.estChaine()) ||
	    (t1.estChar() && t2.estChaine()) ||
	    (t1.estChar() && t2.estChar()) ||
	    (t1.estChaine() && t2.estChar())) {	
		return true;
	}	
	
		
	if (t1.estEntier() || t1.estReel() || t1.estBooleen()) {
		if (t2.estEntier() || t2.estReel() || t2.estBooleen()) 	return true;
		else 													return false;
	}

    if (-t1.estEntier() || -t1.estReel()) {
		if (-t2.estEntier() || -t2.estReel()) 	return true;
		else 									return false;
	}
	
	if (t1.estPointeur() && t2.estPointeur()) {
		TypePointeur const * tp1 = dynamic_cast<TypePointeur const*>(&t1);
		TypePointeur const * tp2 = dynamic_cast<TypePointeur const*>(&t2);
		if ((*tp1->typePointed) == (*tp2->typePointed))	return true;
		else											return false;
	}
	
	if (t1.estInterval()) {
		TypeInterval const * ti1 = dynamic_cast<TypeInterval const *>(&t1);
		if (t2.estInterval()) {
			TypeInterval const * ti2 = dynamic_cast<TypeInterval const *>(&t2);
			return compatibleAffect(*(ti1->getTypeBorne()), *(ti2->getTypeBorne()));
		}
		if (t2.estEntier() || t2.estBooleen() || t2.estEnum() || t2.estChar()) {//refuse les reel
			return compatibleAffect((*ti1->getTypeBorne()), t2);
		}
	}
	
	if (t1.estEnum() && t2.estEnum()) {
		if (t1 == t2)	return true;
	}
	
	if (t1.estStructure() && t2.estStructure()) {
		if (t1 == t2)	return true;
	}
	
	return false;
}

bool Type::compatibleComparaison(Type const &t1, Type const &t2) {

    if (t1.estEntier() || t1.estReel() || t1.estBooleen()) {
		if (t2.estEntier() || t2.estReel() || t2.estBooleen())
		    return true;
	}
	
	if (t1.estChaine() && t2.estChaine())
		return true;
    	
    if (t1.estChar() && t2.estChar()) {	
		return true;
	}
	
	if (t1.estEnum() && t2.estEnum()) {
		if (t1 == t2)	return true;
	}
	
	return false;
}

/**
 * INT et REAL -> OK
 * Boolean a voir
 */
bool Type::compatibleNegation(Type const &t1) {

    if (t1.estEntier() || t1.estReel()) {
		    return true;
	}
	return false;
}
