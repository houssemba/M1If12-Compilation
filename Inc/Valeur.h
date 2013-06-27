#ifndef __VALEUR_H
#define __VALEUR_H

#include <string>
#include <stdio.h>
#include <cstring>
using namespace std;

enum UnionType {INT, ENUM_VALEUR, FLOAT, BOOLEAN, CHAR, STRING };
struct Valeur
{
	union {
		int entier;
		int enumValeur; // c int represente un element(identifiant) d"une enum pascal
		float reel;
		bool booleen;
		char caractere;
		std::string * chaine;
	};
	UnionType unionType;
	
	
};
typedef struct Valeur Valeur;

bool operator==(const Valeur & v1, const Valeur & v2);
bool operator>(const Valeur & v1, const Valeur & v2);
bool operator>=(const Valeur & v1, const Valeur & v2);
bool operator<(const Valeur & v1, const Valeur & v2);
bool operator<=(const Valeur & v1, const Valeur & v2);

Valeur operator+(const Valeur & v1, const Valeur & v2);
Valeur operator-(const Valeur & v1, const Valeur & v2);

Valeur operator-(const Valeur & v1);

/**
 * negation de v1
 */
Valeur operator-(const Valeur &v1);

/**
 * Multiplication de deux valeur
 */
Valeur operator*(const Valeur &v1, const Valeur &v2);

/**
 * Division de deux valeur
 */
Valeur operator/(const Valeur &v1, const Valeur &v2);


void printToStd(Valeur v);

#endif
