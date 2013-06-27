#ifndef __ATTRIBUT__H
#define __ATTRIBUT__H

#include "Type.hpp"
#include "GenerateurType.h"
#include "Valeur.h"
#include "Symbole.hpp"
#include "ConteneurCode.h"

#include <vector>

/*identifiant*/
struct TIdent {
	char name[255];
};


typedef struct TIdent TIdent;


struct tAttrListIdent {
	std::vector<int> * list;
};
typedef struct tAttrListIdent tAttrListIdent;

struct tAttrListArrayIndex {
	std::vector<Type*> * list;// pr stocker les types des dimension du tableau
};
typedef struct tAttrListArrayIndex tAttrListArrayIndex;

struct tAttrTOK_STRING {
	std::string * str;
};
typedef struct tAttrTOK_STRING tAttrTOK_STRING;

struct tAttrType {
	Type * type;
};
typedef struct tAttrType tAttrType;


				
struct tAttrExpression {
	bool calculee;
	bool calculable;
	bool adressable; // savoir si on peut mettre & dvt : &a ok , &7 pas ok
	Type* type;
	Valeur valeur;
	ConteneurCode * code;// les instruction pour arriver a res.
	int res;// id de la variable temporaire.
};

struct tAttrInterBase {
	Type * type;
	Valeur valeur;
};
typedef struct tAttrInterBase tAttrInterBase;


struct tAttrFormalArg {
	std::vector<Symbole*> * list;
};
typedef struct tAttrFormalArg tAttrFormalArg;


struct tAttrRecordField {
	std::vector<std::pair<int, Type*> > * list;
};
typedef tAttrRecordField tAttrRecordField;


struct tAttrListInstr {
	ConteneurCode * code;
};
typedef tAttrListInstr tAttrListInstr;


struct tAttrListIndices {
	std::vector<tAttrExpression> * list;
};
typedef tAttrListIndices tAttrListIndices;

struct tAttrBool {
	bool montant;
};
typedef tAttrBool tAttrBool;	










#endif
