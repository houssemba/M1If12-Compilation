#ifndef __ACTION__H
#define __Action__H

#include <Attributs.h>
#include "GestionTDS.hpp"

int mapIdent_add(TIdent& ident);


void action_ProgramHeader(TIdent& ident);

void action_declare_variable(tAttrListIdent& listident, tAttrType & type);

void action_DeclType(TIdent ident, tAttrType & type);

void action_DeclConst(TIdent ident, tAttrExpression expression);

void action_EnumType(tAttrType & enumType, tAttrListIdent& listEnumValue);

void action_ListIdent(tAttrListIdent& listIdent, TIdent& ident);
void action_ListIdent(tAttrListIdent& listIdent, tAttrListIdent& toCopy, TIdent& ident);
//traitement similaire pour ListEnumValue que ListIdent consiste a faire remonter les identifiants(int).
void action_ListEnumValue(tAttrListIdent& listEnumValue, TIdent& ident);
void action_ListEnumValue(tAttrListIdent& listEnumValue, tAttrListIdent& toCopy, TIdent& ident);



void action_BaseType(tAttrType & baseType, TIdent & ident);
// fonction -->
    /*!
     * \brief Declaration d'une fonction
     * Creer une TDS et rajoute l'ident
     */
    void action_Declarefunction(TIdent &ident, tAttrType &typeRetour);
    void action_Declarefunction(TIdent &ident, tAttrFormalArg & listArg, tAttrType &typeRetour);
    void action_FuncDecl();
//type interval -->
void action_NSInterBase(tAttrInterBase & borne, int entier);//remonter une des borne d'un interval
void action_NSInterBase(tAttrInterBase & borne, TIdent & ident);//remonter une des borne d'un interval -> a partir d"un symbole
void action_InterType(tAttrType & interType, tAttrInterBase & borneI, tAttrInterBase & borneS);// cree le type interval avec les pre-verif necessaire.
void action_InterBase(tAttrInterBase & borneFinal, tAttrInterBase & borneSrc);// interval avec borne negative => verif ke typ = entier car -char,-bool ou -enum pas de sens.
//type tableau -->
void action_ArrayIndex(tAttrType & arrayIndex, TIdent ident);// verif si ident est un typedef d'un interval
void action_ListArrayIndex(tAttrListArrayIndex & listArrayIndex, tAttrType & dim);
void action_ListArrayIndex(tAttrListArrayIndex & listArrayIndex, tAttrListArrayIndex & list, tAttrType & dim);
void action_ArrayType(tAttrType & arrayType, tAttrListArrayIndex & list, tAttrType & containedType);
//procedure -->
void action_ProcHeader(TIdent & ident); // debut de contexte
void action_ProcHeader(TIdent & ident, tAttrFormalArg & listArg);
void action_ProcDecl(); // fin de contexte
//arguments -->
void action_ValFormalArg(tAttrFormalArg & listArg, tAttrListIdent & listIdent, tAttrType & type);// argument en passage par valeur mode constante(modifiable a l'interieur du context)
void action_VarFormalArg(tAttrFormalArg & listArg, tAttrListIdent & listIdent, tAttrType & type);
void action_FormalArg(tAttrFormalArg & listArgDest, tAttrFormalArg & listArgSrc);
void action_ListFormalArgs(tAttrFormalArg & listArg, tAttrFormalArg & list);
void action_ListFormalArgs(tAttrFormalArg & listArgDest, tAttrFormalArg & listArgSrc, tAttrFormalArg & list);
//record = structure
void action_RecordField(tAttrRecordField & fields, tAttrListIdent & listIdent, tAttrType & type);
void action_RecordFields(tAttrRecordField & fieldsDest, tAttrRecordField & fieldsSrc);
void action_RecordFields(tAttrRecordField & fieldsDest, tAttrRecordField & fieldsSrc1, tAttrRecordField & fieldsSrc2);
void action_RecordType(tAttrType & record, tAttrRecordField & fields);








#endif
