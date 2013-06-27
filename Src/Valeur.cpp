#include <Valeur.h>
#include <iostream>
#include <stdlib.h>
#include <MapIdent.h>

extern MapIdent identTable;


//##### operateur de comparaison #####
bool operator==(const Valeur & v1, const Valeur & v2)
{
	if (v1.unionType != v2.unionType)		return false;

	switch( v1.unionType )
	{
		case INT:
			return (v1.entier == v2.entier);
		break;
		
		case ENUM_VALEUR:
			return (v1.enumValeur == v2.enumValeur);
		break;
		
		case FLOAT:
			return(v1.reel == v2.reel);
		break;
		
		case BOOLEAN:
			return(v1.booleen == v2.booleen);
		break;
		
		case CHAR:
			return(v1.caractere == v2.caractere);
		break;
		
		case STRING:
			if (v1.chaine==0 || v2.chaine==0)	return false;
			return(*v1.chaine == *v2.chaine);	
		break;
		
		default:
			std::cout << "\nValeur unhandled !!!" << std::endl;					
			exit(1);
			return false;
	}
}

bool operator>(const Valeur & v1, const Valeur & v2)
{
	if (v1.unionType != v2.unionType)		return false;

	switch( v1.unionType )
	{
		case INT:
			return (v1.entier > v2.entier);
		break;
		
		case ENUM_VALEUR:
			return (v1.enumValeur > v2.enumValeur);
		break;
		
		case FLOAT:
			return(v1.reel > v2.reel);
		break;
		
		case BOOLEAN:
			return(v1.booleen > v2.booleen);
		break;
		
		case CHAR:
			return(v1.caractere > v2.caractere);
		break;
		
		case STRING:
			if (v1.chaine==0 || v2.chaine==0)	return false;
			return(*v1.chaine > *v2.chaine);	
		break;
		
		default:
			std::cout << "\nValeur unhandled !!!" << std::endl;			
			exit(1);
			return false;
	}
	
    // REAL < INT
    if ((v1.unionType == INT && v2.unionType == FLOAT) || 
            (v1.unionType == FLOAT && v2.unionType == INT)) {
		if (v1.unionType == INT)
		    return (v1.entier < v2.reel);
		else
            return (v1.entier < v2.reel);
	}
}

bool operator<(const Valeur &v1, const Valeur &v2) {
    return !operator>(v1, v2);
}

bool operator>=(const Valeur & v1, const Valeur & v2)
{
	return (v1>v2 || v1==v2);
}

bool operator<=(const Valeur & v1, const Valeur & v2)
{
	return (v1<v2 || v1==v2);
}

void printToStd(Valeur v)
{
	switch( v.unionType )
	{
		case INT:
			std::cout <<v.entier;
		break;
		
		case ENUM_VALEUR:
			std::cout <<identTable.getName(v.enumValeur);
		break;
		
		case FLOAT:
			std::cout <<v.reel;
		break;
		
		case BOOLEAN:
			if (v.booleen)		std::cout <<"true";
			else				std::cout <<"false";	
		break;
		
		case CHAR:
			std::cout << "'" << v.caractere << "'";
		break;
		
		case STRING:
			if (v.chaine==0) { std::cout << "\nValeur str* = null !!!" << std::endl;	return;}
			std::cout << "'" << *v.chaine << "'";	
		break;
		
		default:
			std::cout << "\nValeur unhandled !!!" << std::endl;			
			exit(1);
			return;
	
	}
}

Valeur operator+(const Valeur & v1, const Valeur & v2)
{
	Valeur ret;
	//addition de int
	if (v1.unionType == INT && v2.unionType == INT) {
		ret.entier = v1.entier + v2.entier;
		ret.unionType = INT;
	}
	
	//addition de real
	if (v1.unionType == FLOAT && v2.unionType == FLOAT) {
		ret.reel = v1.reel + v2.reel;
		ret.unionType = FLOAT;
	}
	
	//addition de real + int
    if ((v1.unionType == INT && v2.unionType == FLOAT) || 
            (v1.unionType == FLOAT && v2.unionType == INT)) {
		if (v1.unionType == INT) {
		    ret.reel = v1.entier + v2.reel;
		} else {
		    ret.reel = v1.reel + v2.entier;
		}
		ret.unionType = FLOAT;
	}	
	
	//addition de int + bool
    if ((v1.unionType == INT && v2.unionType == BOOLEAN) || 
            (v1.unionType == BOOLEAN && v2.unionType == INT)) {
        
        if (v1.unionType == INT) {
		    ret.entier = v1.entier + v2.booleen;
		} else {
		    ret.entier = v1.booleen + v2.entier;
		}
		ret.unionType = INT;
	}	
	
	//addition de chaine
	if (v1.unionType == STRING && v2.unionType == STRING) {

        std::string *tempoStr = new std::string();
	    *tempoStr += *v1.chaine; 
		*tempoStr += *v2.chaine;
		ret.chaine = tempoStr;
		
		ret.unionType = STRING;
	}
	
	//addition de char
	if (v1.unionType == CHAR && v2.unionType == CHAR) {
		ret.caractere = (char)((v1.caractere + v1.caractere)%127);
		ret.unionType = CHAR;
	}
	
	//addition de char + string
	if ((v1.unionType == CHAR && v2.unionType == STRING) ||
	    (v1.unionType == STRING && v2.unionType == CHAR)) {
        
        std::string *tempoStr = new std::string();
        if (v1.unionType == CHAR) { 
            *tempoStr += v1.caractere;
            *tempoStr += *v2.chaine;
        } else {
           *tempoStr += *v1.chaine;
           *tempoStr += v2.caractere;
        }
		ret.chaine = tempoStr;
		ret.unionType = STRING;
	}
	
	//addition
	return ret;
}

Valeur operator-(const Valeur & v1, const Valeur & v2)
{
	//division de int
	Valeur ret;
	if (v1.unionType == INT && v2.unionType == INT) {
		ret.entier = v1.entier - v2.entier;
		ret.unionType = INT;
	}
	
	//division de real
	if (v1.unionType == FLOAT && v2.unionType == FLOAT) {
		ret.reel = v1.reel - v2.reel;
		ret.unionType = FLOAT;
	}
	
	//division de real * int
    if ((v1.unionType == INT && v2.unionType == FLOAT) || 
            (v1.unionType == FLOAT && v2.unionType == INT)) {
		if (v1.unionType == INT) {
		    ret.reel = v1.entier - v2.reel;
		} else {
		    ret.reel = v1.reel - v2.entier;
		}
		ret.unionType = FLOAT;
	}	
		
	return ret;
}

Valeur operator*(const Valeur & v1, const Valeur & v2)
{
	//multiplication de int
	Valeur ret;
	if (v1.unionType == INT && v2.unionType == INT) {
		ret.entier = v1.entier * v2.entier;
		ret.unionType = INT;
	}
	
	//multiplication de real
	if (v1.unionType == FLOAT && v2.unionType == FLOAT) {
		ret.reel = v1.reel * v2.reel;
		ret.unionType = FLOAT;
	}
	
	//multiplication de real * int
    if ((v1.unionType == INT && v2.unionType == FLOAT) || 
            (v1.unionType == FLOAT && v2.unionType == INT)) {
		if (v1.unionType == INT) {
		    ret.reel = v1.entier * v2.reel;
		} else {
		    ret.reel = v1.reel * v2.entier;
		}
		ret.unionType = FLOAT;
	}	
		
	//multiplication
	return ret;

}

Valeur operator/(const Valeur & v1, const Valeur & v2)
{
	Valeur ret;
	
	if (v1.unionType == INT && v2.unionType == INT) {
	    if (v2.entier == 0) {
	        fprintf(stderr, "Impossible de diviser par 0...\n");
            exit(EXIT_FAILURE);
        }
        if ((v1.entier % v2.entier)==0) {
            ret.entier = v1.entier / v2.entier;
      		ret.unionType = INT;
        } else {
            ret.reel = (float)v1.entier / v2.entier;
            ret.unionType = FLOAT;
        }
	}
	
	//division de real
	if (v1.unionType == FLOAT && v2.unionType == FLOAT) {
		ret.reel = v1.reel / v2.reel;
		ret.unionType = FLOAT;
	}
	
	if ((v1.unionType == INT && v2.unionType == FLOAT) || 
            (v1.unionType == FLOAT && v2.unionType == INT)) {
		if (v1.unionType == INT) {
		    ret.reel = v1.entier / v2.reel;
		} else {
		    ret.reel = v1.reel / v2.entier;
		}
		ret.unionType = FLOAT;
	}	

	return ret;
}

/**
 * operateur de négation
 */
Valeur operator-(const Valeur &v1) {
    //negation de int
	Valeur ret;
	if (v1.unionType == INT) {
		ret.entier = -v1.entier;
		ret.unionType = INT;
	}
	
	if (v1.unionType == FLOAT) {
		ret.reel = -v1.reel;
		ret.unionType = FLOAT;
	}	

	return ret;
}


