#include <ActionExpression.h>
#include <Actions.h>
#include <ActionsMath.h>
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
#include <SymboleEtiquette.h>
#include <TableDesSymboles.hpp>
#include <GenerateurType.h>
#include <TypeStructure.h>
#include <TypePointeur.h>
#include <TypeTableau.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yyerror( char * );

extern MapIdent identTable;
extern TableDesSymboles tableSymbole;// a modif______________________________________
extern GestionTDS listTDS;
extern TableDesSymboles TDStmp;

void action_ListInstr(tAttrListInstr & instr, tAttrListInstr & instrSrc1, tAttrListInstr & instrSrc2)
{
	instr.code = new ConteneurCode();
	instr.code->push(*instrSrc1.code);
	instr.code->push(*instrSrc2.code);
	delete instrSrc1.code;
	delete instrSrc2.code;
}
void action_ListInstr(tAttrListInstr & instr, tAttrListInstr & instrSrc)
{
	instr.code = new ConteneurCode();
	instr.code->push(*instrSrc.code);
	delete instrSrc.code;
}

void action_Instr_Call(tAttrListInstr & instr, tAttrExpression & expr)
{
	instr.code = new ConteneurCode();
	instr.code->push(*expr.code);
}

void action_TOK_INTEGER(tAttrExpression & expression, TIdent & intEnStr)
{
	int v = atoi(intEnStr.name); 
	expression.type = GenerateurType::creerTypeEntier();
	expression.calculee = true;
	expression.calculable = true;
	expression.type = GenerateurType::creerTypeEntier();
	expression.code = new ConteneurCode();
	expression.adressable = false;
	
	expression.valeur.entier = v;
	expression.valeur.unionType = INT;
}

void action_TOK_REAL(tAttrExpression & expression, TIdent & floatEnStr)
{
	float v = (float)atof(floatEnStr.name); 
	expression.type = GenerateurType::creerTypeReel();
	expression.calculee = true;
	expression.calculable = true;
	expression.type = GenerateurType::creerTypeReel();
	expression.code = new ConteneurCode();
	expression.adressable = false;
	
	expression.valeur.reel = v; 
	expression.valeur.unionType = FLOAT;
}

void action_TOK_BOOLEAN(tAttrExpression & expression, TIdent & boolEnStr)
{
	bool v ;
	if( strcmp(boolEnStr.name,"true") == 0)	v=true ; 
	else 									v=false;
	expression.type = GenerateurType::creerTypeBooleen();
	expression.calculee = true;
	expression.calculable = true;
	expression.type = GenerateurType::creerTypeBooleen();
	expression.code = new ConteneurCode();
	expression.adressable = false;
	
	expression.valeur.booleen = v;
	expression.valeur.unionType = BOOLEAN;

}

void action_TOK_STRING(tAttrExpression & expression, tAttrTOK_STRING str)
{
	// enleve les quote
	str.str->erase(0, 1);
	str.str->erase(str.str->size()-1, 1);
	
	expression.calculee = true;
	expression.calculable = true;
	expression.code = new ConteneurCode();
	expression.adressable = false;
	
	if (str.str->size() == 1) {
		expression.type = GenerateurType::creerTypeChar();
		expression.valeur.caractere = str.str->at(0);
		expression.valeur.unionType = CHAR;
		expression.type = GenerateurType::creerTypeChar();
	
		
	}else {
		expression.type = GenerateurType::creerTypeChaine();
		expression.valeur.chaine = str.str;
		expression.valeur.unionType = STRING;
		expression.type = GenerateurType::creerTypeChaine();
	}
}

void action_KW_NIL(tAttrExpression & expression)
{
	//expression.calculee
}



void action_Instr_OP_AFFECT(tAttrListInstr & instr, tAttrExpression & x, tAttrExpression & y) // x := y ;
{
	Symbole * s = listTDS.getSymbole(x.res);
	if(!s->estVariable() && !s->estChamp() && !s->estArgument() && !s->estTemporaire()) {
		char msg[] = "affectation non autoriser.";
		yyerror(msg);
	}
	Symbole * sy = listTDS.getSymbole(y.res);
	if (!y.calculee && sy!=0 && sy->estProcedure()) {
		char msg[] = "Une procedure n'est pas une rvalue.";
		yyerror(msg);
	}

	
	if (!Type::compatibleAffect(*x.type, *y.type)) {
		char msg[] = " affectation entre type incompatible.";
		yyerror(msg);
	}
	bool estArgVar = false;
	if (s->estArgument()) {
		SymboleArgument * sa = dynamic_cast<SymboleArgument*>(s);
		if (! sa->estConstant()) estArgVar = true;
	}
	instr.code = new ConteneurCode();
	instr.code->push(*x.code);
	if ( (s->getType()->estPointeur() && !x.type->estPointeur()) || estArgVar) { // est une addresse dc dereference avt d'affecter.
		if (y.calculee ) {
			instr.code->push(Instruction(OPCODE_RLT, Operande(x.res), Operande(y.valeur), Operande(Valeur())));
		}else {
			instr.code->push(*y.code);
			instr.code->push(Instruction(OPCODE_RLT, Operande(x.res), Operande(y.res), Operande(Valeur())));
		}
	}else {
		if (y.calculee ) {
			instr.code->push(Instruction(OPCODE_CPY, Operande(x.res), Operande(y.valeur), Operande(Valeur())));
		}else {
			instr.code->push(*y.code);
			instr.code->push(Instruction(OPCODE_CPY, Operande(x.res), Operande(y.res), Operande(Valeur())));
		}	
	}	
}



void action_VarExprG_TOK_IDENT(tAttrExpression & res, TIdent & ident)
{
	int id = identTable.getId(ident.name);
	Symbole * s = listTDS.getSymbole(id);
	if (s==0) {
		char msg[] = "identifiant inconnu.";
		yyerror(msg);
	}
	
	
	res.code = new ConteneurCode();
	if (s->estFonction()) {
		SymboleFonction * sf = dynamic_cast<SymboleFonction*>(s);		
		res.res = sf->getResultat();
	} else	res.res = id;

	if (s->estConstante())	{
		res.calculee = true;
		SymboleConstante * sc = dynamic_cast<SymboleConstante*>(s);
		res.valeur = sc->getValeur();
	}else					res.calculee = false;
	res.calculable = true;
	res.adressable = true;
	res.type = s->getType();
	
	
}

void action_VarExprD_TOK_IDENT(tAttrExpression & res, TIdent & ident)
{
	int id = identTable.getId(ident.name);
	Symbole * s = listTDS.getSymbole(id);
	if (s==0) {
		char msg[] = "identifiant inconnu.";
		yyerror(msg);
	}
	
	
	res.code = new ConteneurCode();
	if (s->estFonction()) {
		SymboleFonction * sf = dynamic_cast<SymboleFonction*>(s);		
		res.res = sf->getResultat();
	} else	res.res = id;
	
	if (s->estConstante())	{
		res.calculee = true;
		SymboleConstante * sc = dynamic_cast<SymboleConstante*>(s);
		res.valeur = sc->getValeur();
	}else					res.calculee = false;
	res.calculable = true;
	res.adressable = true;
	res.type = s->getType();
	
	if (s->estArgument()) {
		SymboleArgument * sa = dynamic_cast<SymboleArgument*>(s);
		if (! sa->estConstant()) {
			res.res = SymboleTemporaire::creerTemporaire(s->getType());
			res.code->push(Instruction(OPCODE_RRT, Operande(res.res), Operande(id), Operande(-45)));
		}
	}
	
	
}


void action_VarExprG_OP_PTR(tAttrExpression & res, tAttrExpression & exprP)// expression a gauche.
{
	if(res.type == 0 || !res.type->estPointeur()) {
		char msg[] = "Cette identifiant n'est pas un pointeur";
		yyerror(msg);
	}
	res.code = new ConteneurCode();
	res.code->push(*exprP.code);
	TypePointeur * tp = dynamic_cast<TypePointeur*>(exprP.type);
	res.res = exprP.res;
	res.type = tp->typePointed;
	
}

void action_VarExprD_OP_PTR(tAttrExpression & res, tAttrExpression & exprP)// expression a droite.
{
	if(res.type == 0 || !res.type->estPointeur()) {
		char msg[] = "Cette identifiant n'est pas un pointeur";
		yyerror(msg);
	}
	res.code = new ConteneurCode();
	res.code->push(*exprP.code);
	TypePointeur * tp = dynamic_cast<TypePointeur*>(exprP.type);
	//res.res = tp->idPointed;
	//res.type = tp->typePointed;
	res.res = SymboleTemporaire::creerTemporaire(tp->typePointed);
	res.type = tp->typePointed;
	res.code->push(Instruction(OPCODE_RRT, Operande(res.res), Operande(exprP.res), Operande(-45)));
	
}

void action_VarExprD_OP_DRF(tAttrExpression & res, tAttrExpression & exprV)
{
	if (!exprV.adressable) {
		char msg[] = "expression non adressable";
		yyerror(msg);
	}
	res.code = new ConteneurCode();
	res.code->push(*exprV.code);
	res.type = GenerateurType::creerTypePointeur(exprV.type);
	res.calculee = false;
	res.calculable = true;
	res.adressable = false;
	res.res = SymboleTemporaire::creerTemporaire(res.type);
	res.code->push(Instruction(OPCODE_PTR, Operande(res.res), Operande(exprV.res), Operande(-45)));
}

void actionVarExprG_Structure(tAttrExpression & res, tAttrExpression & expr, TIdent ident)// a gauche on remonte une adresse.
{
	if (!expr.type->estStructure()) {
		char msg[] = "Ceci n'est pas une structure";
		yyerror(msg);
	}
	
	TypeStructure * ts = dynamic_cast<TypeStructure*>(expr.type);
	
	int id = identTable.getId(ident.name);
	if (!ts->isField(id)) {
		char msg[] = "Cette structure n'a pas de champs de se nom.";
		yyerror(msg);
	}
	res.code = new ConteneurCode();
	res.code->push(*expr.code);
	res.type = ts->getTypeField(id); // le type de l'expression est celui du champ designer
	res.res = SymboleTemporaire::creerTemporaire(GenerateurType::creerTypePointeur(ts->getTypeField(id)));// le type de res est un pointeur sur le champ designer
	Valeur v;
	v.entier = TypeStructure::decalage(*ts, id);// calcul le decalage
	v.unionType = INT;
	Symbole * s = listTDS.getSymbole(expr.res);
	
	if ( !s->getType()->estPointeur() && (!s->estArgument() || s->estArgConstant())) {//on id1.id2 => calculer adresse de id1
		int tmp = SymboleTemporaire::creerTemporaire(GenerateurType::creerTypePointeur(expr.type));
		res.code->push(Instruction(OPCODE_PTR, Operande(tmp), Operande(expr.res), Operande(-45)));
		res.code->push(Instruction(OPCODE_ADD, Operande(res.res), Operande(tmp), Operande(v)));
	
	}else {//expr est deja une adresse
		res.code->push(Instruction(OPCODE_ADD, Operande(res.res), Operande(expr.res), Operande(v)));
	}
	
}

void action_VarExprD_Structure(tAttrExpression & res, tAttrExpression & expr, TIdent ident)
{
	if (! expr.type->estStructure()) {
		char msg[] = "Ceci n'est pas une structure";
		yyerror(msg);
	}
	
	TypeStructure * ts = dynamic_cast<TypeStructure*>(expr.type);
	
	int id = identTable.getId(ident.name);
	if (!ts->isField(id)) {
		char msg[] = "Cette structure n'a pas de champs de se nom.";
		yyerror(msg);
	}
	res.code = new ConteneurCode();
	res.code->push(*expr.code);
	res.type = ts->getTypeField(id); // le type de l'expression est celui du champ designer
	res.res = SymboleTemporaire::creerTemporaire(ts->getTypeField(id));// le type de res est du type champ designer
	Valeur v;
	v.entier = TypeStructure::decalage(*ts, id);// calcul le decalage
	v.unionType = INT;
	
	Symbole * s = listTDS.getSymbole(expr.res);
	int tmp2 = SymboleTemporaire::creerTemporaire(GenerateurType::creerTypePointeur(ts->getTypeField(id)));//pointeur sur le type du champs
	if ( !(s->getType()->estPointeur()) && (!s->estArgument() || s->estArgConstant())) {//on id1.id2 => calculer adresse de id1
		int tmp = SymboleTemporaire::creerTemporaire(GenerateurType::creerTypePointeur(expr.type));
		
		res.code->push(Instruction(OPCODE_PTR, Operande(tmp), Operande(expr.res), Operande(-45)));
		res.code->push(Instruction(OPCODE_ADD, Operande(tmp2), Operande(tmp), Operande(v)));
		res.code->push(Instruction(OPCODE_RRT, Operande(res.res), Operande(tmp2), Operande(-45)));
	
	}else {//expr est deja une adresse
		res.code->push(Instruction(OPCODE_ADD, Operande(tmp2), Operande(expr.res), Operande(v)));
		res.code->push(Instruction(OPCODE_RRT, Operande(res.res), Operande(tmp2), Operande(-45)));
	}
		
}

void action_VarExprG_Tableau(tAttrExpression & res, tAttrExpression & expr, tAttrListIndices & indices)
{
	if (! expr.type->estTableau()) {
		char msg[] = "Ceci n'est pas un tableau";
		yyerror(msg);
	}
	std::vector<Type*> dims;
	for (unsigned int i=0; i< indices.list->size(); i++)
	{
		dims.push_back(indices.list->at(i).type);
		if(indices.list->at(i).type->estEntier()) {}
	}
	TypeTableau * tt = dynamic_cast<TypeTableau*>(expr.type);
	
	bool compatible = true;
	std::vector<Type*> dimsL = tt->getDims();
	if (dimsL.size() != dims.size())	compatible = false;
	else {
		for (unsigned int i=0; i<dimsL.size(); i++)
		{
			if (! Type::compatibleAffect(*dimsL.at(i), *dims.at(i))) {
				compatible = false;
				break;
			}
		}
	}
	if (!compatible) {
		char msg[] = "Les types des indices sont incompatibles.";
		yyerror(msg);
	}
	
	res.calculee = false;
	res.calculable = true;
	res.adressable = false;
	res.type = tt->getTypeContained();
	res.res = SymboleTemporaire::creerTemporaire(GenerateurType::creerTypePointeur(tt->getTypeContained()));
	res.code = new ConteneurCode();
	res.code->push(*expr.code);
	
	res.code->push(*(indices.list->at(0).code));// premiere iteration res.res = expr.res [ indice[0] ]
	if (! indices.list->at(0).calculee)
		res.code->push(Instruction(OPCODE_ART, Operande(res.res), Operande(expr.res),Operande(indices.list->at(0).res)));
	else	
		res.code->push(Instruction(OPCODE_ART, Operande(res.res), Operande(expr.res),Operande(indices.list->at(0).valeur)));
	
	for (unsigned int i=1; i<indices.list->size(); i++)
	{
		res.code->push(*(indices.list->at(i).code)); // puis boucle iteration res.res = res.res [ indice[i] ]
		//int tmp = SymboleTemporaire::creerTemporaire
		if (! indices.list->at(i).calculee)
			res.code->push(Instruction(OPCODE_ART, Operande(res.res), Operande(res.res),Operande(indices.list->at(i).res)));
		else
			res.code->push(Instruction(OPCODE_ART, Operande(res.res), Operande(res.res),Operande(indices.list->at(i).valeur)));	
	}
}

void action_VarExprD_Tableau(tAttrExpression & res, tAttrExpression & expr, tAttrListIndices & indices)// remonte une valeur
{
	if (! expr.type->estTableau()) {
		char msg[] = "Ceci n'est pas un tableau";
		yyerror(msg);
	}
	std::vector<Type*> dims;
	for (unsigned int i=0; i< indices.list->size(); i++)
	{
		dims.push_back(indices.list->at(i).type);
		if(indices.list->at(i).type->estEntier()) {}
	}
	TypeTableau * tt = dynamic_cast<TypeTableau*>(expr.type);
	
	bool compatible = true;
	std::vector<Type*> dimsL = tt->getDims();
	if (dimsL.size() != dims.size())	compatible = false;
	else {
		for (unsigned int i=0; i<dimsL.size(); i++)
		{
			if (! Type::compatibleAffect(*dimsL.at(i), *dims.at(i))) {
				compatible = false;
				break;
			}
		}
	}
	if (!compatible) {
		char msg[] = "Les types des indices sont incompatibles.";
		yyerror(msg);
	}
	
	res.calculee = false;
	res.calculable = true;
	res.adressable = false;
	res.type = tt->getTypeContained();
	res.res = SymboleTemporaire::creerTemporaire(tt->getTypeContained());
	res.code = new ConteneurCode();
	res.code->push(*expr.code);
	
	res.code->push(*(indices.list->at(0).code));// premiere iteration res.res = expr.res [ indice[0] ]

	int tmp = SymboleTemporaire::creerTemporaire(GenerateurType::creerTypePointeur(tt->getTypeContained()));
	if (! indices.list->at(0).calculee)
		res.code->push(Instruction(OPCODE_ART, Operande(tmp), Operande(expr.res),Operande(indices.list->at(0).res)));
	else	
		res.code->push(Instruction(OPCODE_ART, Operande(tmp), Operande(expr.res),Operande(indices.list->at(0).valeur)));
	
	for (unsigned int i=1; i<indices.list->size(); i++)
	{
		res.code->push(*(indices.list->at(i).code)); // puis boucle iteration res.res = res.res [ indice[i] ]
		
		if (! indices.list->at(i).calculee)
			res.code->push(Instruction(OPCODE_ART, Operande(tmp), Operande(tmp),Operande(indices.list->at(i).res)));
		else
			res.code->push(Instruction(OPCODE_ART, Operande(tmp), Operande(tmp),Operande(indices.list->at(i).valeur)));	
	}
	
	res.code->push(Instruction(OPCODE_RRT, Operande(res.res), Operande(tmp),Operande(-45)));	
}


void action_Call(tAttrExpression & res, TIdent & ident, tAttrListIndices & params)
{
	Symbole * s = listTDS.getSymbole(identTable.getId(ident.name));
	if (s==0) {
		char msg[] = "Appel interdit identifiant inconnu.";
		yyerror(msg); 
	}
	if (! s->estProcedure() && ! s->estFonction()) {
		char msg[] = "Appel interdit ce n'est pas une fonction/procedure.";
		yyerror(msg); 
	}
	res.calculee = false;
	res.calculable = true;
	res.adressable = false; // foncteur en pascal ????
	res.code = new ConteneurCode();
	//res.type = GenerateurType::creerTypeEntier();
	//res.res = 25;
	if (s->estProcedure()) {
		SymboleProcedure * sp = dynamic_cast<SymboleProcedure*>(s);
		if (((unsigned int)sp->getArite()) != params.list->size()) {
			char msg[] = "Le nombre de parametre est mauvais.";
			yyerror(msg);
		}
		for (int i=0; i<sp->getArite(); i++) {
			tAttrExpression expr = params.list->at(i);
			if (! Type::compatibleAffect(*sp->getTypeParam(i), *expr.type) ) {
				char msg[] = "Le/Les types des parametres sont incompatibles.";
				yyerror(msg);
			}
			if (sp->estParamConstant(i)) {
				if (expr.calculee)		res.code->push(Instruction(OPCODE_PSH, Operande(expr.valeur), Operande(-45), Operande(-45)));
				else					res.code->push(Instruction(OPCODE_PSH, Operande(expr.res), Operande(-45), Operande(-45)));
			}else {//on envoi une adresse
				if (expr.calculee) {
					char msg[] = "parametre non adressable.";
					yyerror(msg);
				}else			res.code->push(Instruction(OPCODE_PSP, Operande(expr.res), Operande(-45), Operande(-45)));
			}	
		}
		res.code->push(Instruction(OPCODE_CLL, Operande(s->getId()), Operande(-45), Operande(-45)));
		res.res = sp->getId();
	
	}else {// fonction
	
		SymboleFonction * sf = dynamic_cast<SymboleFonction*>(s);
		if ( ((unsigned int)sf->getArite()) != params.list->size() ) {
			char msg[] = "Le nombre de parametre est mauvais.";
			yyerror(msg);
		}
		for (int i=0; i<sf->getArite(); i++) {
			tAttrExpression expr = params.list->at(i);
			if (! Type::compatibleAffect(*sf->getTypeParam(i), *expr.type) ) {
				char msg[] = "Le/Les types des parametres sont incompatibles.";
				yyerror(msg);
			}
			if (sf->estParamConstant(i)) {
				if (expr.calculee)		res.code->push(Instruction(OPCODE_PSH, Operande(expr.valeur), Operande(-45), Operande(-45)));
				else					res.code->push(Instruction(OPCODE_PSH, Operande(expr.res), Operande(-45), Operande(-45)));
			}else {//on envoi une adresse
				if (expr.calculee) {
					char msg[] = "parametre non adressable.";
					yyerror(msg);
				}else			res.code->push(Instruction(OPCODE_PSP, Operande(expr.res), Operande(-45), Operande(-45)));
			}	
		}
		res.res = SymboleTemporaire::creerTemporaire(sf->getType());
		res.code->push(Instruction(OPCODE_CLL, Operande(s->getId()), Operande(-45), Operande(-45)));
		res.code->push(Instruction(OPCODE_POP, Operande(res.res), Operande(-45), Operande(-45)));
		res.type = sf->getType();
	}
	
}


void action_BoolExpr_NOT(tAttrExpression & res, tAttrExpression & expr)
{
	math_check_operation_autoriser(expr);
	
	res.code = new ConteneurCode();
	res.code->push(*expr.code);
	res.calculable = true;
	res.adressable = false;
	res.type = GenerateurType::creerTypeBooleen();
	if (expr.calculee) {
		res.calculee = true;
		res.valeur.booleen = ! expr.valeur.booleen;
		res.valeur.unionType = BOOLEAN;
	}else {
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_NOT, Operande(res.res), Operande(expr.res), Operande(-45)));
	}
}

void action_BoolExpr_AND(tAttrExpression & res, tAttrExpression & x, tAttrExpression & y)
{
	math_check_operation_autoriser(x);
	math_check_operation_autoriser(y);
	
	res.code = new ConteneurCode();
	res.code->push(*x.code);
	res.code->push(*y.code);
	res.calculable = true;
	res.adressable = false;
	res.type = GenerateurType::creerTypeBooleen();
	if (x.calculee && y.calculee) {
		res.calculee = true;
		res.valeur.booleen = x.valeur.booleen && y.valeur.booleen;
		res.valeur.unionType = BOOLEAN;
	}else if (x.calculee) {// seul x calculee
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_AND, Operande(res.res), Operande(x.valeur), Operande(y.res)));
	}else if (y.calculee) {
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_AND, Operande(res.res), Operande(x.res), Operande(y.valeur)));
	}else {
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_AND, Operande(res.res), Operande(x.res), Operande(y.res)));
	}
}
void action_BoolExpr_OR(tAttrExpression & res, tAttrExpression & x, tAttrExpression & y)
{
	math_check_operation_autoriser(x);
	math_check_operation_autoriser(y);
	
	res.code = new ConteneurCode();
	res.code->push(*x.code);
	res.code->push(*y.code);
	res.calculable = true;
	res.adressable = false;
	res.type = GenerateurType::creerTypeBooleen();
	if (x.calculee && y.calculee) {
		res.calculee = true;
		res.valeur.booleen = x.valeur.booleen || y.valeur.booleen;
		res.valeur.unionType = BOOLEAN;
	}else if (x.calculee) {// seul x calculee
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_OR, Operande(res.res), Operande(x.valeur), Operande(y.res)));
	}else if (y.calculee) {
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_OR, Operande(res.res), Operande(x.res), Operande(y.valeur)));
	}else {
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_OR, Operande(res.res), Operande(x.res), Operande(y.res)));
	}
}
void action_BoolExpr_XOR(tAttrExpression & res, tAttrExpression & x, tAttrExpression & y)
{
	tAttrExpression xN, yN, and1, and2;
	action_BoolExpr_NOT(xN, x);
	action_BoolExpr_NOT(yN, y);
	action_BoolExpr_AND(and1, xN, y);
	action_BoolExpr_AND(and2, x, yN);
	action_BoolExpr_OR(res, and1, and2);// xN.y + x.yN = XOR
}


void action_CompExpr_OP_EQ(tAttrExpression & res, tAttrExpression & x, tAttrExpression & y)
{
	math_check_operation_autoriser(x);
	math_check_operation_autoriser(y);
	
	if (! Type::compatibleComparaison(*x.type, *y.type) ) {
		char msg[]= "Comparaison entre type incompatible.";
		yyerror(msg);
	}

	res.code = new ConteneurCode();
	res.code->push(*x.code);
	res.code->push(*y.code);
	res.adressable = false;
	res.type = GenerateurType::creerTypeBooleen();
	if (x.calculee && y.calculee) {
		res.calculee = true;
		res.valeur.booleen = x.valeur == y.valeur;
		res.valeur.unionType = BOOLEAN;
	}else if (x.calculee) {// seul x calculee
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_EQ, Operande(res.res), Operande(x.valeur), Operande(y.res)));
	}else if (y.calculee) {
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_EQ, Operande(res.res), Operande(x.res), Operande(y.valeur)));
	}else {
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_EQ, Operande(res.res), Operande(x.res), Operande(y.res)));
	}
}
void action_CompExpr_OP_NEQ(tAttrExpression & res, tAttrExpression & x, tAttrExpression & y)
{
	math_check_operation_autoriser(x);
	math_check_operation_autoriser(y);
	
	if (! Type::compatibleComparaison(*x.type, *y.type) ) {
		char msg[]= "Comparaison entre type incompatible.";
		yyerror(msg);
	}

	res.code = new ConteneurCode();
	res.code->push(*x.code);
	res.code->push(*y.code);
	res.adressable = false;
	res.type = GenerateurType::creerTypeBooleen();
	if (x.calculee && y.calculee) {
		res.calculee = true;
		res.valeur.booleen = !(x.valeur == y.valeur);
		res.valeur.unionType = BOOLEAN;
	}else if (x.calculee) {// seul x calculee
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_NEQ, Operande(res.res), Operande(x.valeur), Operande(y.res)));
	}else if (y.calculee) {
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_NEQ, Operande(res.res), Operande(x.res), Operande(y.valeur)));
	}else {
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_NEQ, Operande(res.res), Operande(x.res), Operande(y.res)));
	}
}
void action_CompExpr_OP_LT(tAttrExpression & res, tAttrExpression & x, tAttrExpression & y)
{
	math_check_operation_autoriser(x);
	math_check_operation_autoriser(y);
	
	if (! Type::compatibleComparaison(*x.type, *y.type) ) {
		char msg[]= "Comparaison entre type incompatible.";
		yyerror(msg);
	}

	res.code = new ConteneurCode();
	res.code->push(*x.code);
	res.code->push(*y.code);
	res.adressable = false;
	res.type = GenerateurType::creerTypeBooleen();
	if (x.calculee && y.calculee) {
		res.calculee = true;
		res.valeur.booleen = x.valeur < y.valeur;
		res.valeur.unionType = BOOLEAN;
	}else if (x.calculee) {// seul x calculee
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_LT, Operande(res.res), Operande(x.valeur), Operande(y.res)));
	}else if (y.calculee) {
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_LT, Operande(res.res), Operande(x.res), Operande(y.valeur)));
	}else {
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_LT, Operande(res.res), Operande(x.res), Operande(y.res)));
	}
}
void action_CompExpr_OP_LTE(tAttrExpression & res, tAttrExpression & x, tAttrExpression & y)
{
	math_check_operation_autoriser(x);
	math_check_operation_autoriser(y);
	
	if (! Type::compatibleComparaison(*x.type, *y.type) ) {
		char msg[]= "Comparaison entre type incompatible.";
		yyerror(msg);
	}

	res.code = new ConteneurCode();
	res.code->push(*x.code);
	res.code->push(*y.code);
	res.adressable = false;
	res.type = GenerateurType::creerTypeBooleen();
	if (x.calculee && y.calculee) {
		res.calculee = true;
		res.valeur.booleen = x.valeur <= y.valeur;
		res.valeur.unionType = BOOLEAN;
	}else if (x.calculee) {// seul x calculee
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_LE, Operande(res.res), Operande(x.valeur), Operande(y.res)));
	}else if (y.calculee) {
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_LE, Operande(res.res), Operande(x.res), Operande(y.valeur)));
	}else {
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_LE, Operande(res.res), Operande(x.res), Operande(y.res)));
	}
}
void action_CompExpr_OP_Gt(tAttrExpression & res, tAttrExpression & x, tAttrExpression & y)
{
	math_check_operation_autoriser(x);
	math_check_operation_autoriser(y);
	
	if (! Type::compatibleComparaison(*x.type, *y.type) ) {
		char msg[]= "Comparaison entre type incompatible.";
		yyerror(msg);
	}

	res.code = new ConteneurCode();
	res.code->push(*x.code);
	res.code->push(*y.code);
	res.adressable = false;
	res.type = GenerateurType::creerTypeBooleen();
	if (x.calculee && y.calculee) {
		res.calculee = true;
		res.valeur.booleen = x.valeur > y.valeur;
		res.valeur.unionType = BOOLEAN;
	}else if (x.calculee) {// seul x calculee
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_GT, Operande(res.res), Operande(x.valeur), Operande(y.res)));
	}else if (y.calculee) {
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_GT, Operande(res.res), Operande(x.res), Operande(y.valeur)));
	}else {
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_GT, Operande(res.res), Operande(x.res), Operande(y.res)));
	}
}
void action_CompExpr_OP_GTE(tAttrExpression & res, tAttrExpression & x, tAttrExpression & y)
{
	math_check_operation_autoriser(x);
	math_check_operation_autoriser(y);
	
	if (! Type::compatibleComparaison(*x.type, *y.type) ) {
		char msg[]= "Comparaison entre type incompatible.";
		yyerror(msg);
	}

	res.code = new ConteneurCode();
	res.code->push(*x.code);
	res.code->push(*y.code);
	res.adressable = false;
	res.type = GenerateurType::creerTypeBooleen();
	if (x.calculee && y.calculee) {
		res.calculee = true;
		res.valeur.booleen = x.valeur >= y.valeur;
		res.valeur.unionType = BOOLEAN;
	}else if (x.calculee) {// seul x calculee
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_GE, Operande(res.res), Operande(x.valeur), Operande(y.res)));
	}else if (y.calculee) {
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_GE, Operande(res.res), Operande(x.res), Operande(y.valeur)));
	}else {
		res.calculee = false;
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(Instruction(OPCODE_GE, Operande(res.res), Operande(x.res), Operande(y.res)));
	}
}


void action_Instr_While(tAttrListInstr & instr, tAttrExpression & expr, tAttrListInstr & instrLoop)
{
	instr.code = new ConteneurCode();
	
	if (expr.calculee) {
		if( expr.valeur.unionType != BOOLEAN ) {
			char msg[] = "L'expression conditionnel doit etre booleene";
			yyerror(msg);
		}
		if (!expr.valeur.booleen) { // nop 
			instr.code->push(Instruction(OPCODE_NONE, Operande(-45), Operande(-45), Operande(-45)));
			return;
		}
		else {
			int whStart;
			SymboleEtiquette::creerWhileShort(whStart);// modif start
			instr.code->push(Instruction(OPCODE_NONE, Operande(-45), Operande(-45), Operande(-45), whStart));
			instr.code->push(*instrLoop.code);
			instr.code->push(Instruction(OPCODE_JMP, Operande(whStart), Operande(-45), Operande(-45)));
		}	
	}else { // non calculee
		if(! expr.type->estBooleen() ) {
			char msg[] = "L'expression conditionnel doit etre booleene";
			yyerror(msg);
		}		
		int whStart, whBody, whEnd;
		SymboleEtiquette::creerWhileLong(whStart, whBody, whEnd);// modif start, body et end
		
		instr.code->push(Instruction(OPCODE_NONE, Operande(-45), Operande(-45), Operande(-45), whStart));//start: .....
		instr.code->push(*expr.code);																	// calcul expr		
		instr.code->push(Instruction(OPCODE_JMPC, Operande(expr.res), Operande(whBody), Operande(-45)));// if expr ---> body: 
		instr.code->push(Instruction(OPCODE_JMP, Operande(whEnd), Operande(-45), Operande(-45)));       // JMP --> end:
		instr.code->push(Instruction(OPCODE_NONE, Operande(-45), Operande(-45), Operande(-45), whBody));// body:  ....
		instr.code->push(*instrLoop.code);																// instruction a faire
		instr.code->push(Instruction(OPCODE_JMP, Operande(whStart), Operande(-45), Operande(-45)));		// JMP --> start:
		instr.code->push(Instruction(OPCODE_NONE, Operande(-45), Operande(-45), Operande(-45), whEnd)); // end:   ....
	}
}

void action_Instr_IF_THEN(tAttrListInstr & instr, tAttrExpression & expr, tAttrListInstr & instrBlock)
{
	instr.code = new ConteneurCode();
	
	if (expr.calculee) {
		if( expr.valeur.unionType != BOOLEAN ) {
			char msg[] = "L'expression conditionnel doit etre booleene";
			yyerror(msg);
		}
		if (!expr.valeur.booleen) { // nop 
			instr.code->push(Instruction(OPCODE_NONE, Operande(-45), Operande(-45), Operande(-45)));
			return;
		}
		else { //if vrai ->> on fai directement les instructions.
			instr.code->push(*instrBlock.code);
		}	
	
	}else {
		if(! expr.type->estBooleen() ) {
			char msg[] = "L'expression conditionnel doit etre booleene";
			yyerror(msg);
		}
		int ifBody, ifEnd;
		SymboleEtiquette::creerIfShort(ifBody, ifEnd);
		
		instr.code->push(*expr.code);																	// calcul expr		
		instr.code->push(Instruction(OPCODE_JMPC, Operande(expr.res), Operande(ifBody), Operande(-45)));// if expr ---> body: 
		instr.code->push(Instruction(OPCODE_JMP, Operande(ifEnd), Operande(-45), Operande(-45)));       // JMP --> end:
		instr.code->push(Instruction(OPCODE_NONE, Operande(-45), Operande(-45), Operande(-45), ifBody));// body:  ....
		instr.code->push(*instrBlock.code);																// instruction a faire
		instr.code->push(Instruction(OPCODE_NONE, Operande(-45), Operande(-45), Operande(-45), ifEnd));// end:   ....
	}
}

void action_Instr_IF_THEN_ELSE(tAttrListInstr & instr, tAttrExpression & expr, tAttrListInstr & instrThen, tAttrListInstr & instrElse)
{
	instr.code = new ConteneurCode();
	
	if (expr.calculee) {
		if( expr.valeur.unionType != BOOLEAN ) {
			char msg[] = "L'expression conditionnel doit etre booleene";
			yyerror(msg);
		}
		if (!expr.valeur.booleen) { // else 
			instr.code->push(*instrElse.code);
			return;
		}
		else { //if vrai ->> on fai directement les instructions Then.
			instr.code->push(*instrThen.code);
		}	
	
	}else {
		if(! expr.type->estBooleen() ) {
			char msg[] = "L'expression conditionnel doit etre booleene";
			yyerror(msg);
		}
		int ifBody, ifElse;
		SymboleEtiquette::creerIfLong(ifBody, ifElse);
		
		instr.code->push(*expr.code);																	// calcul expr		
		instr.code->push(Instruction(OPCODE_JMPC, Operande(expr.res), Operande(ifBody), Operande(-45)));// if expr ---> body: 
		instr.code->push(Instruction(OPCODE_JMP, Operande(ifElse), Operande(-45), Operande(-45)));       // JMP --> else:
		instr.code->push(Instruction(OPCODE_NONE, Operande(-45), Operande(-45), Operande(-45), ifBody));// body:  ....
		instr.code->push(*instrThen.code);																// instruction a faire then 
		instr.code->push(Instruction(OPCODE_NONE, Operande(-45), Operande(-45), Operande(-45), ifElse));// else:   ....
		instr.code->push(*instrElse.code);																// instruction a faire else 
	}
}

void action_Instr_REPEAT(tAttrListInstr & instr, tAttrListInstr & instrBlock, tAttrExpression & expr)
{
	instr.code = new ConteneurCode();
	
	if (expr.calculee) {
		if( expr.valeur.unionType != BOOLEAN ) {
			char msg[] = "L'expression conditionnel doit etre booleene";
			yyerror(msg);
		}
		if (!expr.valeur.booleen) { // else 
			int repeat;
			SymboleEtiquette::creerRepeatShort(repeat);
			instr.code->push(Instruction(OPCODE_NONE, Operande(-45), Operande(-45), Operande(-45), repeat));// repeat:  ....
			instr.code->push(*instrBlock.code);
			instr.code->push(Instruction(OPCODE_JMP, Operande(repeat), Operande(-45), Operande(-45)));
			return;
		}
		else { //if vrai ->> on fai directement les instructions Then.
			instr.code->push(*instrBlock.code);
		}
		
	}else {
		if(! expr.type->estBooleen() ) {
			char msg[] = "L'expression conditionnel doit etre booleene";
			yyerror(msg);
		}
		int repStart, repEnd;
		SymboleEtiquette::creerRepeatLong(repStart, repEnd);
		
		instr.code->push(Instruction(OPCODE_NONE, Operande(-45), Operande(-45), Operande(-45), repStart));
		instr.code->push(*instrBlock.code);
		instr.code->push(*expr.code);
		instr.code->push(Instruction(OPCODE_JMPC, Operande(expr.res), Operande(repEnd), Operande(-45)));
		instr.code->push(Instruction(OPCODE_JMP, Operande(repStart), Operande(-45), Operande(-45)));
		instr.code->push(Instruction(OPCODE_NONE, Operande(-45), Operande(-45), Operande(-45), repEnd));
	}	
}

void action_Instr_FOR(tAttrListInstr & instr, TIdent ident, tAttrExpression & exprToAffect, tAttrBool & montant, tAttrExpression & expr, tAttrListInstr & instrBlock)
{
	int id = identTable.getId(ident.name);
	Symbole * s = listTDS.getSymbole(id);
	if (s==0) {
		char msg[] = "identifiant inconnu";
		yyerror(msg);
	}
	if(!s->estVariable() && !s->estChamp() && !s->estArgument() && !s->estTemporaire()) {
		char msg[] = "affectation non autoriser.";
		yyerror(msg);
	}
	if( ! Type::compatibleAffect(*s->getType(), *exprToAffect.type) || ! Type::compatibleComparaison(*s->getType(), *expr.type)) {
		char msg[] = "boucle sur des types incompatibles.";
		yyerror(msg);
	}
	
	instr.code = new ConteneurCode();	
	//  id := exprToAffect
	if (exprToAffect.calculee)	instr.code->push(Instruction(OPCODE_CPY, Operande(id), Operande(exprToAffect.valeur), Operande(-45)));
	else {
		instr.code->push(*exprToAffect.code);
		instr.code->push(Instruction(OPCODE_CPY, Operande(id), Operande(exprToAffect.res), Operande(-45)));	
	}	
	
	int forTest, forEnd;
	SymboleEtiquette::creerFor(forTest, forEnd);
	instr.code->push(Instruction(OPCODE_NONE, Operande(-45), Operande(-45), Operande(-45), forTest));
	instr.code->push(*expr.code);
	int testB = SymboleTemporaire::creerTemporaire(GenerateurType::creerTypeBooleen());
	// TEST du FOR
	if(montant.montant) {
		if (expr.calculee)	instr.code->push(Instruction(OPCODE_GT, Operande(testB), Operande(id), Operande(expr.valeur)));
		else				instr.code->push(Instruction(OPCODE_GT, Operande(testB), Operande(id), Operande(expr.res)));
	}else {
		if (expr.calculee)	instr.code->push(Instruction(OPCODE_LT, Operande(testB), Operande(id), Operande(expr.valeur)));
		else				instr.code->push(Instruction(OPCODE_LT, Operande(testB), Operande(id), Operande(expr.res)));
	}
	
	instr.code->push(Instruction(OPCODE_JMPC, Operande(testB), Operande(forEnd), Operande(-45)));
	instr.code->push(*instrBlock.code);
	Valeur v;
	v.entier = 1;
	v.unionType = INT;
	if(montant.montant)	instr.code->push(Instruction(OPCODE_ADD, Operande(id), Operande(id), Operande(v)));
	else				instr.code->push(Instruction(OPCODE_SUB, Operande(id), Operande(id), Operande(v)));
	instr.code->push(Instruction(OPCODE_JMP, Operande(forTest), Operande(-45), Operande(-45)));
	instr.code->push(Instruction(OPCODE_NONE, Operande(-45), Operande(-45), Operande(-45), forEnd));
}


void action_Instr_BlockCode(tAttrListInstr & instr, tAttrListInstr & instrBlock)
{
	instr.code = new ConteneurCode();
	instr.code->push(*instrBlock.code);
}

void action_ListIndices(tAttrListIndices & res, tAttrExpression & expr)
{
	res.list = new std::vector<tAttrExpression>();
	res.list->push_back(expr);
}

void action_ListIndices(tAttrListIndices & res, tAttrListIndices & src, tAttrExpression & expr)
{
	res.list = new std::vector<tAttrExpression>();
	for (unsigned int i=0; i<src.list->size(); i++) {
		res.list->push_back(src.list->at(i));
	}
	res.list->push_back(expr);
}


void action_BlockCode(tAttrListInstr & block, tAttrListInstr & instrList)
{
	block.code = new ConteneurCode();
	block.code->push(*instrList.code);
}
void action_BlockCode(tAttrListInstr & block){
	block.code = new ConteneurCode();
}

void action_block(tAttrListInstr & block)
{
	int id = identTable.getId(listTDS.getContext()->getName());
	Symbole * s = listTDS.getSymbole(id);
	if (s->estProgram()) {
		SymboleProgram * sp = dynamic_cast<SymboleProgram*>(s);
		sp->pushCode(*block.code);
	}
	if (s->estFonction()) {
		SymboleFonction * sf = dynamic_cast<SymboleFonction*>(s);
		sf->pushCode(*block.code);
	}
	if (s->estProcedure()) {
		SymboleProcedure * sp = dynamic_cast<SymboleProcedure*>(s);
		sp->pushCode(*block.code);
	}
}

void action_Parameters(tAttrListIndices & res)
{
	res.list = new std::vector<tAttrExpression>();// initialise a vide == pas de paramettre
}
