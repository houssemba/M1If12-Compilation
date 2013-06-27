#include <Actions.h>
#include <MapIdent.h>
#include <SymboleVariable.h>
#include <SymboleProgram.h>
#include <SymboleType.h>
#include <SymboleConstante.h>
#include <SymboleFonction.hpp>
#include <SymboleProcedure.h>
#include <SymboleArgument.h>
#include <SymboleChamp.h>
#include <SymboleTemporaire.hpp>
#include <TableDesSymboles.hpp>
#include <GenerateurType.h>
#include <TypeStructure.h>
#include <TypePointeur.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>

extern int yyerror( char * );

extern MapIdent identTable;
extern TableDesSymboles tableSymbole;// a modif______________________________________
extern GestionTDS listTDS;
extern TableDesSymboles TDStmp;

void action_DeclConst(TIdent ident, tAttrExpression expression)
{
	if (! expression.calculee )
	{
		char str[255];
		sprintf(str, "affection d'une expression variable a une constante \"%s\".", ident.name);
		yyerror(str);
	}
	
	int id = identTable.getId(ident.name);
	listTDS.ajouter(new SymboleConstante(expression.type, id, expression.valeur));
}

void action_EnumType(tAttrType & enumType, tAttrListIdent& listEnumValue)
{
	enumType.type = GenerateurType::creerTypeEnum(*(listEnumValue.list));
	 
	// on ajoute les identifiants de l'enum comme des constantes
	
	for (int i=0; i<(int)listEnumValue.list->size(); i++)
	{	
		Valeur v;
		v.enumValeur = listEnumValue.list->at(i);
		v.unionType = ENUM_VALEUR;
		listTDS.ajouter(new SymboleConstante(enumType.type, listEnumValue.list->at(i), v));
	}
}




int mapIdent_add(TIdent& ident) {
	std::string s = ident.name;
	return identTable.add(s);
}

void action_declare_variable(tAttrListIdent& listIdent, tAttrType & type)
{
	for (int i=0; i< (int)listIdent.list->size(); i++)
	{
		int id = (*listIdent.list)[i];
		listTDS.ajouter(new SymboleVariable(type.type, id) );
	}
}

void action_DeclType(TIdent ident, tAttrType & type)
{
	int id = identTable.getId(ident.name);
	listTDS.ajouter(new SymboleType(type.type, id));
	// cree la table des symboles de ce type si c'est un record
	if ( type.type->estStructure() ) {

		listTDS.startContext( new TableDesSymboles(ident.name, 0)); // une TS de record n'a pas de pere
		
		int position = 0;
		TypeStructure * t = dynamic_cast<TypeStructure*>(type.type);
		std::vector<std::pair<int, Type*> > champs = t->getChamps();
		
		for (unsigned int i=0; i<champs.size(); i++)
		{
			std::pair<int, Type*> c = champs.at(i);
			listTDS.ajouter(new SymboleChamp(c.second, position, c.first));
			position++;
		}
		
		listTDS.endContext();
	}
}

void action_declare_constante(TIdent ident)
{
	mapIdent_add(ident);
}

void action_ProgramHeader(TIdent& ident)
{
	if (identTable.getId(ident.name) != 0)
	{
		char str[] = "Mauvaise definition du \"program\"";
		yyerror(str);
	}
	
	//sinon on l'ajoute a la TS.
	int id = identTable.getId(ident.name);
	//tableSymbole.ajouter(id, new SymboleProgram(id)); // CReer la premiere TS a laide du futur gestionnaire de TS puis y ajouter le symbole program
    listTDS.startContext(new TableDesSymboles(ident.name, 0)); // na pas de pere
    listTDS.ajouter(new SymboleProgram(id));
}
#include <iostream>
//#include <vector>

void action_ListIdent(tAttrListIdent& listIdent, TIdent& ident)
{
	listIdent.list = new std::vector<int>();
	listIdent.list->push_back(identTable.getId(ident.name));
}

void action_ListIdent(tAttrListIdent& listIdent, tAttrListIdent& toCopy, TIdent& ident)
{
	listIdent.list = new std::vector<int>(*(toCopy.list));
	listIdent.list->push_back(identTable.getId(ident.name));
	
	delete toCopy.list;//limiter fuite memoire.
	
// pour verifier le fonctionnement de action_ListIdent :	
/*	for(int i=0; i< listIdent.list->size(); i++)
	{
		std::cout << (*listIdent.list)[i]<<" ";
	}
	std::cout << "\n";
*/	
}

void action_ListEnumValue(tAttrListIdent& listEnumValue, TIdent& ident)
{
	listEnumValue.list = new std::vector<int>();
	listEnumValue.list->push_back(identTable.getId(ident.name));
}

void action_ListEnumValue(tAttrListIdent& listEnumValue, tAttrListIdent& toCopy, TIdent& ident)
{
	listEnumValue.list = new std::vector<int>(*(toCopy.list));
	listEnumValue.list->push_back(identTable.getId(ident.name));
	
	delete toCopy.list;//limiter fuite memoire.

}




void action_NSInterBase(tAttrInterBase & borne, int entier)
{
	borne.valeur.entier = entier;
	borne.valeur.unionType = INT;
	borne.type = GenerateurType::creerTypeEntier();
}

void action_NSInterBase(tAttrInterBase & borne, TIdent & ident)
{
	Symbole * s = listTDS.getSymbole(identTable.getId(ident.name));
	if (s==0) {
		char msg[500];
		sprintf(msg, "Identifiant:%s  inconnu.",ident.name);
		yyerror(msg);
		return;
	}
	if (!s->estConstante()) {
		char msg[500];
		sprintf(msg, "Symbole:%s  n'est pas une constante.",ident.name);
		yyerror(msg);
		return;
	}
	// trouver et constante --> 
	SymboleConstante * sCste = dynamic_cast<SymboleConstante*>(s);
	Type * t = sCste->getType();
	if (!t->estEntier() && !t->estBooleen() && !t->estEnum() && !t->estChaine()) {// un char est confondu ds une string ds une expr
		char msg[] = "bad type:le type d'un interval est un int, char, bool ou enum.";
		yyerror(msg);
		return;
	}
	if (t->estChaine()) {// on assimil un char a une string de taille 1.
		if (sCste->getValeur().chaine->size() != 1){
			char msg[] = "bad type:le type d'un interval est un int, char, bool ou enum.";
			yyerror(msg);
			return;
		}
	}
	borne.type = sCste->getType();
	borne.valeur = sCste->getValeur(); 
}

void action_InterBase(tAttrInterBase & borneFinal, tAttrInterBase & borneSrc)
{
	if (!borneSrc.type->estEntier()) {
		char msg[] = "borne d'interval negative non entiere!";
		yyerror(msg);
		return;
	}
	//bien un entier => inverse sa valeur:
	borneFinal = borneSrc;
	borneFinal.valeur.entier = -borneFinal.valeur.entier;
}

void action_InterType(tAttrType & interType, tAttrInterBase & borneI, tAttrInterBase & borneS)
{
	if (!((*borneI.type) == (*borneS.type))) {
		char msg[] = "Creation d'un interval ayant des bornes de type differents.";
		yyerror(msg);
		return;
	}
	
	if (borneI.valeur >= borneS.valeur){
		char msg[] = "Interval avec borne inf >= borne sup";
		yyerror(msg);
		return;
	}
	// bI < bS et sont de meme type --> creation du type interval.
	interType.type = GenerateurType::creerTypeInterval(borneI.type, borneI.valeur, borneS.valeur);
	
}

void action_ArrayIndex(tAttrType & arrayIndex, TIdent ident)
{
	Symbole * s = listTDS.getSymbole(identTable.getId(ident.name));
	if (s==0) {
		char msg[500];
		sprintf(msg, "Identifiant:%s  inconnu.",ident.name);
		yyerror(msg);
		return;
	}
	if (!s->estType()) {
		char msg[500];
		sprintf(msg, "<%s> Indice d'un tableau doit etre un typdef ou un interval.",ident.name);
		yyerror(msg);
		return;	
	}
	// c'est un type mais sur quoi ?
	SymboleType * st = dynamic_cast<SymboleType*>(s);
	if (!(st->getType()->estInterval())) {
		char msg[500];
		sprintf(msg, "<%s> Indice d'un tableau doit etre un typdef d'un interval.",ident.name);
		yyerror(msg);
		return;	
	}
	
	arrayIndex.type = st->getType();
}


void action_BaseType(tAttrType & baseType, TIdent & ident)
{
	Symbole * s = listTDS.getSymbole(identTable.getId(ident.name));
	if (s==0) {
		char msg[500];
		sprintf(msg, "Identifiant:%s  inconnu.",ident.name);
		yyerror(msg);
		return;
	}
	if (!s->estType()) {
		char msg[500];
		sprintf(msg, "<%s> Doit etre un typdef.",ident.name);
		yyerror(msg);
		return;	
	}
	
	SymboleType * st = dynamic_cast<SymboleType*>(s);
	baseType.type = st->getType();
}

void action_ListArrayIndex(tAttrListArrayIndex & listArrayIndex, tAttrType & dim)
{
	listArrayIndex.list = new vector<Type*>();
	listArrayIndex.list->push_back(dim.type);
}

void action_ListArrayIndex(tAttrListArrayIndex & listArrayIndex, tAttrListArrayIndex & list, tAttrType & dim)
{
	listArrayIndex.list = new vector<Type*>(*list.list);
	listArrayIndex.list->push_back(dim.type);
	delete list.list;
}

void action_ArrayType(tAttrType & arrayType, tAttrListArrayIndex & list, tAttrType & containedType)
{
	arrayType.type = GenerateurType::creerTypeTableau(containedType.type, *list.list);
}	

void action_ProcHeader(TIdent & ident)
{
	listTDS.ajouter(new SymboleProcedure(0, identTable.getId(ident.name)));
	listTDS.startContext( new TableDesSymboles(ident.name, listTDS.getContext()));
}

void action_ProcHeader(TIdent & ident, tAttrFormalArg & listArg)
{
	SymboleProcedure * sProc = new SymboleProcedure(listArg.list->size(), identTable.getId(ident.name));
	listTDS.ajouter(sProc);
	listTDS.startContext( new TableDesSymboles(ident.name, listTDS.getContext()));	
	std::stack<Instruction> code;
	int position = 0;
	for (unsigned int i=0; i<listArg.list->size(); i++)// ajout des argument ds le nouvo context.
	{
		SymboleArgument * s = dynamic_cast<SymboleArgument*>(listArg.list->at(i));
		s->setPosition(position);
		position++;
		listTDS.ajouter(s);
		sProc->ajouterParam(s->getId(), s->getType(), s->estConstant());
		code.push(Instruction(OPCODE_POP, Operande(s->getId()), Operande(-45), Operande(-45)));
	}
	sProc->setTS(listTDS.getContext());
	while (!code.empty()) {
		sProc->pushCode(code.top());
		code.pop();
	}
}

void action_Declarefunction(TIdent &ident, tAttrType &type) {

    int id = identTable.getId(ident.name);
    // Type de retour de la fonction
    SymboleFonction *fonction = new SymboleFonction(type.type, id, 0, listTDS.getNumContexte());

    listTDS.ajouter(fonction);
    listTDS.startContext(new TableDesSymboles(ident.name, listTDS.getContext()));
    fonction->setTemporaireResultat(SymboleTemporaire::creerTemporaire(type.type));
}

void action_Declarefunction(TIdent &ident, tAttrFormalArg & listArg, tAttrType &typeRetour)
{
	SymboleFonction * sFonc = new SymboleFonction(typeRetour.type, identTable.getId(ident.name), listArg.list->size(), listTDS.getNumContexte());
	listTDS.ajouter( sFonc);
	
	listTDS.startContext(new TableDesSymboles(ident.name, listTDS.getContext()));
	
	int position = 0;
	std::stack<Instruction> code;
	for (unsigned int i=0; i<listArg.list->size(); i++)
	{
		SymboleArgument * s = dynamic_cast<SymboleArgument*>(listArg.list->at(i));
		s->setPosition(position);
		position++;
		listTDS.ajouter(s);
		sFonc->ajouterParam(s->getId(), s->getType(), s->estConstant());
		code.push(Instruction(OPCODE_POP, Operande(s->getId()), Operande(-45), Operande(-45)));
	}
	sFonc->setTS(listTDS.getContext());
	while (!code.empty()) {
		sFonc->pushCode(code.top());
		code.pop();
	}
	sFonc->setTemporaireResultat(SymboleTemporaire::creerTemporaire(typeRetour.type));
}

void action_FuncDecl()
{
	Symbole * s = listTDS.getSymbole(identTable.getId(listTDS.getContext()->getName()));
	SymboleFonction * sf = dynamic_cast<SymboleFonction*>(s);
	sf->pushCode(Instruction(OPCODE_PSH, Operande(sf->getResultat()), Operande(-45), Operande(-45)));
	sf->pushCode(Instruction(OPCODE_RET, Operande(-45), Operande(-45), Operande(-45)));
	listTDS.endContext();
}

void action_ProcDecl()
{
	Symbole * s = listTDS.getSymbole(identTable.getId(listTDS.getContext()->getName()));
	SymboleProcedure * sp = dynamic_cast<SymboleProcedure*>(s);
	sp->pushCode(Instruction(OPCODE_RET, Operande(-45), Operande(-45), Operande(-45)));
	listTDS.endContext();
}

void action_ValFormalArg(tAttrFormalArg & listArg, tAttrListIdent & listIdent, tAttrType & type)
{
	int position = 0;
	listArg.list = new std::vector<Symbole*>();
	
	for (unsigned int i=0; i<listIdent.list->size(); i++) 
	{
		listArg.list->push_back( new SymboleArgument(true, type.type, position, listIdent.list->at(i)) );
		position++;
	}
}

void action_VarFormalArg(tAttrFormalArg & listArg, tAttrListIdent & listIdent, tAttrType & type)
{
	listArg.list = new std::vector<Symbole*>();
	
	for (unsigned int i=0; i<listIdent.list->size(); i++) 
	{																// posi 0 sera modif + haut
		listArg.list->push_back( new SymboleArgument(false, type.type, 0, listIdent.list->at(i)) );
	}
}

void action_FormalArg(tAttrFormalArg & listArgDest, tAttrFormalArg & listArgSrc)
{
	listArgDest.list = new std::vector<Symbole*>(*listArgSrc.list); 
	
	delete listArgSrc.list;
}

void action_ListFormalArgs(tAttrFormalArg & listArg, tAttrFormalArg & list)
{
	listArg.list = new std::vector<Symbole*>(*list.list);
	delete list.list;
}

void action_ListFormalArgs(tAttrFormalArg & listArgDest, tAttrFormalArg & listArgSrc, tAttrFormalArg & list)
{
	listArgDest.list = new std::vector<Symbole*>(*listArgSrc.list);
	for (unsigned int i =0; i<list.list->size(); i++)
	{	
		listArgDest.list->push_back(list.list->at(i));
	}	
	
	delete listArgSrc.list;
	delete list.list;
}

void action_RecordField(tAttrRecordField & fields, tAttrListIdent & listIdent, tAttrType & type)
{
	fields.list = new std::vector<std::pair<int, Type*> >();
	
	for (unsigned int i=0; i<listIdent.list->size(); i++)
	{
		fields.list->push_back(std::pair<int, Type*>(listIdent.list->at(i), type.type) );
	}
}

void action_RecordFields(tAttrRecordField & fieldsDest, tAttrRecordField & fieldsSrc)
{
	fieldsDest.list = new std::vector<std::pair<int, Type*> >();
	
	for (unsigned int i=0; i<fieldsSrc.list->size(); i++)
	{
		fieldsDest.list->push_back(fieldsSrc.list->at(i) );
	}
	
	delete fieldsSrc.list;
}

void action_RecordFields(tAttrRecordField & fieldsDest, tAttrRecordField & fieldsSrc1, tAttrRecordField & fieldsSrc2)
{
	fieldsDest.list = new std::vector<std::pair<int, Type*> >();
	
	for (unsigned int i=0; i<fieldsSrc1.list->size(); i++)
	{
		fieldsDest.list->push_back(fieldsSrc1.list->at(i) );
	}
	
	for (unsigned int i=0; i<fieldsSrc2.list->size(); i++)
	{
		fieldsDest.list->push_back(fieldsSrc2.list->at(i) );
	}
	
	delete fieldsSrc1.list;
	delete fieldsSrc2.list;
}

void action_RecordType(tAttrType & record, tAttrRecordField & fields)
{
	record.type = GenerateurType::creerTypeStructure(*fields.list);
	
}































