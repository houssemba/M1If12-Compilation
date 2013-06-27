%{
    #include <cstddef>
    #include <stdio.h>
    #include <Attributs.h>
    #include <Actions.h>
    #include <cstdio>
	#include <iostream>
	#include <vector>
	#include <string>
	#include <sstream>
	#include <string.h>
	
    #include "Symbole.hpp"
    #include "TableDesSymboles.hpp"
    #include "Type.hpp"
    #include "GestionTDS.hpp"
    #include "ActionsMath.h"
    #include <ActionExpression.h>
    
    extern int yyerror ( char* );
    extern int yylex ();
    //La table des symboles du main
    extern TableDesSymboles *TDS;
    //La liste de toutes les tables des symboles des != contextes
    extern GestionTDS listeTDS;
    //La table des symboles tempo afin de stocker les symboles dans les sous-contextes
    extern TableDesSymboles *TempoTDS;
    
    
    //###########
    //le numero de la TS actuelle
    unsigned int TDSActuelle = 0;
    extern std::vector<int> tabTDSPere; // contient les numeros des TDS en fonction du niveauTDS
%}

//les types
%union{
	TIdent ident;
    tAttrListIdent attrListIdent;
	tAttrType attrType;
	tAttrExpression attrExpression;
	tAttrTOK_STRING attrTOK_STRING;
	tAttrInterBase attrInterBase;
	tAttrListArrayIndex attrListArrayIndex;
	tAttrFormalArg attrFormalArg;
	tAttrRecordField attrRecordField;
	tAttrListInstr attrListInstr;
	tAttrListIndices attrListIndices;
	tAttrBool attrBool;
}

%token KW_PROGRAM
%token KW_CONST
%token KW_TYPE
%token KW_VAR
%token KW_ARRAY
%token KW_OF
%token KW_RECORD
%token KW_BEGIN
%token KW_END
%token KW_DIV
%token KW_MOD
%token KW_AND
%token KW_OR
%token KW_XOR
%token KW_NOT
%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_DO
%token KW_REPEAT
%token KW_UNTIL
%token KW_FOR
%token KW_TO
%token KW_DOWNTO
%token KW_PROC
%token KW_FUNC
%token KW_NIL
%token KW_INTEGER
%token KW_REAL
%token KW_BOOLEAN
%token KW_CHAR
%token KW_STRING

%token SEP_SCOL
%token SEP_DOT
%token SEP_DOTS
%token SEP_DOTDOT
%token SEP_COMMA
%token SEP_CO
%token SEP_CF
%token SEP_PO
%token SEP_PF

%token OP_EQ
%token OP_NEQ
%token OP_LT
%token OP_LTE
%token OP_GT
%token OP_GTE
%token OP_ADD
%token OP_SUB
%token OP_MUL
%token OP_SLASH
%token OP_EXP
%token OP_PTR
%token OP_AFFECT
%token OP_DRF

%token <ident> TOK_IDENT
%token <ident> TOK_INTEGER
%token <ident> TOK_REAL
%token <ident> TOK_BOOLEAN
%token <attrTOK_STRING> TOK_STRING

%start Program

%type < attrListIdent > ListIdent
%type < attrListIdent > ListEnumValue
%type < attrType > Type
%type < attrType > BaseType
%type < attrType > PointerType
%type < attrType > UserType
%type < attrType > EnumType
%type < attrType > InterType
%type < attrType > ArrayIndex
%type < attrType > ArrayType
%type < attrType > RecordType
%type < attrExpression > Expression
%type < attrExpression > AtomExpr
%type < attrExpression > MathExpr
%type < attrExpression > VarExprG
%type < attrExpression > VarExprD
%type < attrExpression > Call
%type < attrExpression > BoolExpr
%type < attrExpression > CompExpr
%type < attrInterBase > InterBase
%type < attrInterBase > NSInterBase

%type < attrListArrayIndex > ListArrayIndex

%type < attrType > FuncResult
%type < ident > FuncIdent
%type < attrFormalArg > FormalArgs
%type < attrFormalArg > ValFormalArg
%type < attrFormalArg > VarFormalArg
%type < attrFormalArg > FormalArg
%type < attrFormalArg > ListFormalArgs

%type < ident > ProcIdent

%type < attrRecordField > RecordField
%type < attrRecordField > RecordFields

%type < attrListInstr > ListInstr
%type < attrListInstr > Instr
%type < attrListInstr > BlockCode

%type < attrListIndices > ListIndices
%type < attrListIndices > Parameters
%type < attrListIndices > ListParameters

%type < attrBool > ForDirection

%nonassoc OP_EQ OP_NEQ OP_GT OP_LT OP_GTE OP_LTE
%left OP_ADD OP_SUB KW_OR KW_XOR
%left OP_MUL OP_SLASH KW_AND KW_DIV KW_MOD
%right KW_NOT OP_NEG OP_POS
%left OP_EXP
%nonassoc OP_PTR
%nonassoc OP_DOT
%left SEP_CO

%nonassoc KW_IFX
%nonassoc KW_ELSE

%%

//##### GRAMMAIRE #####

Program			:	ProgramHeader SEP_SCOL Block SEP_DOT {}
				;

ProgramHeader		:	KW_PROGRAM TOK_IDENT {action_ProgramHeader($2);}

				;

Block				:	BlockDeclConst BlockDeclType BlockDeclVar BlockDeclFunc BlockCode { action_block($5); }
				;

BlockDeclConst			:	KW_CONST ListDeclConst
			 	|
			 	;

ListDeclConst			:	ListDeclConst DeclConst
			 	|	DeclConst
			 	;

DeclConst			:	TOK_IDENT OP_EQ Expression SEP_SCOL {action_DeclConst($1, $3);}
			 	;

BlockDeclType			:	KW_TYPE ListDeclType
			 	|
			 	;

ListDeclType			:	ListDeclType DeclType
			 	|	DeclType
			 	;

DeclType			:	TOK_IDENT OP_EQ Type SEP_SCOL {action_DeclType($1, $3);}
			 	;

BlockDeclVar			:	KW_VAR ListDeclVar
			 	|
			 	;

ListDeclVar			:	ListDeclVar DeclVar
			 	|	DeclVar
			 	;

DeclVar				:	ListIdent SEP_DOTS Type SEP_SCOL {action_declare_variable($1,$3);}
			 	;

ListIdent			:	ListIdent SEP_COMMA TOK_IDENT {action_ListIdent($$, $1, $3);}
			 	|	TOK_IDENT {action_ListIdent($$, $1);}
			 	;

BlockDeclFunc			:	ListDeclFunc SEP_SCOL
			 	|
			 	;

ListDeclFunc			:	ListDeclFunc SEP_SCOL DeclFunc
			 	|	DeclFunc
			 	;

DeclFunc			:	ProcDecl {
                                //procedure declaration
                                //faire un autre num de contexte pour la TDS
                                }
			 	|	FuncDecl
			 	;

ProcDecl			:	ProcHeader SEP_SCOL Block { action_ProcDecl(); /*fin d'une procedure*/}
			 	;

ProcHeader			:	ProcIdent { action_ProcHeader($1); }
			 	|	ProcIdent FormalArgs { action_ProcHeader($1, $2); }
			 	;

ProcIdent			:	KW_PROC TOK_IDENT { strcpy($$.name, $2.name);}
			 	;

FormalArgs			:	SEP_PO ListFormalArgs SEP_PF { $$=$2; }
			 	;

ListFormalArgs			:	ListFormalArgs SEP_SCOL FormalArg { action_ListFormalArgs($$, $1, $3); }
			 	|	FormalArg { action_ListFormalArgs($$, $1); }
			 	;

FormalArg			:	ValFormalArg  { action_FormalArg($$, $1); }
			 	|	VarFormalArg {}
			 	;

ValFormalArg			:	ListIdent SEP_DOTS BaseType { action_ValFormalArg($$, $1, $3); 
                            /* Declaration de variable const ou pas mais transmi par valeur!!!*/}
			 	;

VarFormalArg			:	KW_VAR ListIdent SEP_DOTS BaseType { action_VarFormalArg($$, $2, $4);/* argument passer par adresse car variable*/}
			 	;

FuncDecl			:	FuncHeader SEP_SCOL Block { action_FuncDecl();/*fin du contexte*/}
			 	;

FuncHeader			:	FuncIdent FuncResult {action_Declarefunction($1, $2);} /* Fonction sans args */
			 	|	FuncIdent FormalArgs FuncResult { action_Declarefunction($1, $2, $3); }
			 	;

FuncIdent			:	KW_FUNC TOK_IDENT  {strcpy($$.name, $2.name);}
			 	;

FuncResult			:	SEP_DOTS BaseType {$$ = $2; /* remonte le type de retour de la fct */}
			 	;

Type				:	UserType {$$.type = $1.type;}
			 	|	BaseType { $$.type = $1.type;}
			 	;

UserType			:	EnumType {$$.type = $1.type;}
			 	|	InterType {$$.type = $1.type;}
			 	|	ArrayType {$$.type = $1.type;}
			 	|	RecordType {$$.type = $1.type;}
			 	|	PointerType {$$.type = $1.type;}
			 	;

BaseType			:	TOK_IDENT { action_BaseType($$, $1);/*verif si ce symbole est un "type" pascal sinon -> yyerror: ident n'est pas un type.*/}
				|   KW_INTEGER {$$.type = GenerateurType::creerTypeEntier();}
				|	KW_REAL {$$.type = GenerateurType::creerTypeReel();}
				|	KW_BOOLEAN {$$.type = GenerateurType::creerTypeBooleen();}
				|	KW_CHAR {$$.type = GenerateurType::creerTypeChar();}
				|	KW_STRING {$$.type = GenerateurType::creerTypeChaine();}
				;

EnumType			:	SEP_PO ListEnumValue SEP_PF { action_EnumType($$, $2); }
			 	;

ListEnumValue			:	ListEnumValue SEP_COMMA TOK_IDENT {action_ListEnumValue($$,$1,$3);}
			 	|	TOK_IDENT {action_ListEnumValue($$,$1);}
			 	;

InterType			:	InterBase SEP_DOTDOT InterBase { action_InterType($$, $1, $3);/*verif $1 < $3*/ }
			 	;

InterBase			:	NSInterBase { $$ = $1; }
			 	|	OP_SUB NSInterBase { action_InterBase($$, $2);/*represente le -5 de [-5..3]  verif pas une enum*/}
			 	;

NSInterBase			:	TOK_IDENT { action_NSInterBase($$, $1); }//action_NSInterBase_TOK_IDENT($$, $1); /*verif type = const enum ou const int ou const char*/}
			 	|	TOK_INTEGER { action_NSInterBase($$, atoi($1.name)); }
			 	;

ArrayType			:	KW_ARRAY SEP_CO ListArrayIndex SEP_CF KW_OF Type { action_ArrayType($$, $3, $6); }
			 	;

ListArrayIndex			:	ListArrayIndex SEP_COMMA ArrayIndex { action_ListArrayIndex($$, $1, $3); }
				|	ArrayIndex { action_ListArrayIndex($$, $1); }
				;

ArrayIndex			:	TOK_IDENT { action_ArrayIndex($$, $1); }
			 	|	InterType { $$.type = $1.type; }
			 	;

RecordType			:	KW_RECORD RecordFields KW_END { action_RecordType($$, $2); }
			 	;

RecordFields			:	RecordFields SEP_SCOL RecordField { action_RecordFields($$, $1, $3); }
			 	|	RecordField { action_RecordFields($$, $1); }
			 	;

RecordField			:	ListIdent SEP_DOTS Type { action_RecordField($$, $1, $3); }
			 	;

PointerType			:	OP_PTR Type {$$.type = GenerateurType::creerTypePointeur($2.type);}
			 	;

BlockCode			:	KW_BEGIN ListInstr KW_END { action_BlockCode($$,$2); }
				|	KW_BEGIN ListInstr SEP_SCOL KW_END { action_BlockCode($$,$2); }
				|	KW_BEGIN KW_END { action_BlockCode($$); }
			 	;

ListInstr			:	ListInstr SEP_SCOL Instr { action_ListInstr($$, $1, $3); }
			 	|	Instr { action_ListInstr($$, $1); }
			 	;

Instr				:	KW_WHILE Expression KW_DO Instr { action_Instr_While($$, $2, $4); }
			 	|	KW_REPEAT ListInstr KW_UNTIL Expression { action_Instr_REPEAT($$, $2, $4); }
			 	|	KW_FOR TOK_IDENT OP_AFFECT Expression ForDirection Expression KW_DO Instr { action_Instr_FOR($$, $2, $4, $5, $6, $8); }
			 	|	KW_IF Expression KW_THEN Instr %prec KW_IFX { action_Instr_IF_THEN($$, $2, $4); }
			 	|	KW_IF Expression KW_THEN Instr KW_ELSE Instr { action_Instr_IF_THEN_ELSE($$, $2, $4, $6); }
			 	|	VarExprG OP_AFFECT Expression { action_Instr_OP_AFFECT($$,$1, $3);  }
			 	|	Call { action_Instr_Call($$, $1); }
			 	|	BlockCode { action_Instr_BlockCode($$, $1); }
			 	;

ForDirection			:	KW_TO {$$.montant = true;}
			 	|	KW_DOWNTO {$$.montant = false;}
			 	;

Expression			:	MathExpr { $$ = $1; }
			 	|	CompExpr { $$ = $1; }
			 	|	BoolExpr { $$ = $1; }
			 	|	AtomExpr { $$ = $1; }
			 	|	VarExprD { $$ = $1; }
				|	Call { $$ = $1; }
			 	;

MathExpr			:	Expression OP_ADD Expression { action_MAthExpr_OP_ADD($$, $1, $3); }
			 	|	Expression OP_SUB Expression { action_MAthExpr_OP_SUB($$, $1, $3); }
			 	|	Expression OP_MUL Expression { action_MAthExpr_OP_MUL($$, $1, $3); }
			 	|	Expression OP_SLASH Expression { action_MAthExpr_OP_DIV($$, $1, $3); }
			 	|	Expression KW_DIV Expression { action_MAthExpr_OP_DIVIDENTE($$, $1, $3); }
			 	|	Expression KW_MOD Expression { action_MathExpr_MOD($$, $1, $3); }
			 	|	Expression OP_EXP Expression 
			 	|	OP_SUB Expression %prec OP_NEG { action_MAthExpr_OP_NEG($$, $2); }
			 	|	OP_ADD Expression %prec OP_POS { $$ = $2; }
			 	;

CompExpr			:	Expression OP_EQ Expression { action_CompExpr_OP_EQ($$, $1, $3); }
			 	|	Expression OP_NEQ Expression { action_CompExpr_OP_NEQ($$, $1, $3); }
			 	|	Expression OP_LT Expression { action_CompExpr_OP_LT($$, $1, $3); }
			 	|	Expression OP_LTE Expression { action_CompExpr_OP_LTE($$, $1, $3); }
			 	|	Expression OP_GT Expression { action_CompExpr_OP_Gt($$, $1, $3); }
			 	|	Expression OP_GTE Expression { action_CompExpr_OP_GTE($$, $1, $3); }
			 	;

BoolExpr			:	Expression KW_AND Expression { action_BoolExpr_AND($$, $1, $3); }
			 	|	Expression KW_OR Expression { action_BoolExpr_OR($$, $1, $3); }
			 	|	Expression KW_XOR Expression { action_BoolExpr_XOR($$, $1, $3); }
			 	|	KW_NOT Expression { action_BoolExpr_NOT($$, $2); }
			 	;

AtomExpr			:	SEP_PO Expression SEP_PF { $$=$2; /*parenthese*/}
			 	|	TOK_INTEGER { action_TOK_INTEGER($$, $1); }
			 	|	TOK_REAL { action_TOK_REAL($$, $1); }
			 	|	TOK_BOOLEAN { action_TOK_BOOLEAN($$, $1); }
			 	|	KW_NIL { action_KW_NIL($$);/*_______________________________________________________________________________________________*/ }
			 	|	TOK_STRING { action_TOK_STRING($$, $1); }
			 	;

VarExprD				:	TOK_IDENT { action_VarExprD_TOK_IDENT($$, $1); }
				|	VarExprD SEP_CO ListIndices SEP_CF { action_VarExprD_Tableau($$, $1, $3); }
				|	VarExprD SEP_DOT TOK_IDENT %prec OP_DOT { action_VarExprD_Structure($$, $1, $3); }
				|	VarExprD OP_PTR { action_VarExprD_OP_PTR($$, $1); }
				|	OP_DRF VarExprD { action_VarExprD_OP_DRF($$, $2); }
				;

VarExprG				:	TOK_IDENT { action_VarExprG_TOK_IDENT($$, $1); }
				|	VarExprG SEP_CO ListIndices SEP_CF { action_VarExprG_Tableau($$, $1, $3); }
				|	VarExprG SEP_DOT TOK_IDENT %prec OP_DOT { actionVarExprG_Structure($$, $1, $3); }
				|	VarExprG OP_PTR { action_VarExprG_OP_PTR($$, $1); }
				;				

Call			 	:	TOK_IDENT Parameters { action_Call($$, $1, $2); }
				;

Parameters			:	SEP_PO ListParameters SEP_PF { $$.list = $2.list; }
				|	SEP_PO SEP_PF { action_Parameters($$); }
				;

ListIndices			:	ListIndices SEP_COMMA Expression { action_ListIndices($$, $1, $3); }
				|	Expression { action_ListIndices($$, $1); }
				;

ListParameters			:	ListParameters SEP_COMMA Expression { action_ListIndices($$, $1, $3);/*fai la meme chose remonte les expr*/ }
				|	Expression { action_ListIndices($$, $1); }
				;

%%
