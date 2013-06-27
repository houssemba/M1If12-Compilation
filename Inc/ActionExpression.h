#ifndef __ACTION_EXPRESSION_H
#define __ACTION_EXPRESSION_H

#include <Attributs.h>
#include "GestionTDS.hpp"


// les expressions
	void action_ListInstr(tAttrListInstr & instr, tAttrListInstr & instrSrc1, tAttrListInstr & instrSrc2);
	void action_ListInstr(tAttrListInstr & instr, tAttrListInstr & instrSrc);	
	void action_Instr_Call(tAttrListInstr & instr, tAttrExpression & expr);
	
	void action_TOK_INTEGER(tAttrExpression & expression, TIdent & intEnStr);
	void action_TOK_REAL(tAttrExpression & expression, TIdent & floatEnStr);
	void action_TOK_BOOLEAN(tAttrExpression & expression, TIdent & boolEnStr);
	void action_TOK_STRING(tAttrExpression & expression, tAttrTOK_STRING str);
	void action_KW_NIL(tAttrExpression & expression);
	
	// instruction
	void action_Instr_OP_AFFECT(tAttrListInstr & instr, tAttrExpression & x, tAttrExpression & y); // x := y ;
	void action_Instr_BlockCode(tAttrListInstr & instr, tAttrListInstr & instrBlock);
	void action_Instr_While(tAttrListInstr & instr, tAttrExpression & expr, tAttrListInstr & instrLoop);// while( expr) { instrLoop }
	void action_Instr_IF_THEN(tAttrListInstr & instr, tAttrExpression & expr, tAttrListInstr & instrBlock);// if then
	void action_Instr_IF_THEN_ELSE(tAttrListInstr & instr, tAttrExpression & expr, tAttrListInstr & instrThen, tAttrListInstr & instrElse); //if then else
	void action_Instr_REPEAT(tAttrListInstr & instr, tAttrListInstr & instrBlock, tAttrExpression & expr); // repeat until
	void action_Instr_FOR(tAttrListInstr & instr, TIdent ident, tAttrExpression & exprToAffect, tAttrBool & montant, tAttrExpression & expr, tAttrListInstr & instrBlock); // for
	
	// VarExpr -->
	void action_VarExprG_TOK_IDENT(tAttrExpression & res, TIdent & ident);
	void action_VarExprD_TOK_IDENT(tAttrExpression & res, TIdent & ident);
	void action_VarExprD_OP_PTR(tAttrExpression & res, tAttrExpression & exprP);
	void action_VarExprG_OP_PTR(tAttrExpression & res, tAttrExpression & exprP);
	void action_VarExprD_OP_DRF(tAttrExpression & res, tAttrExpression & exprV);// &b
	//structure -->
	void actionVarExprG_Structure(tAttrExpression & res, tAttrExpression & expr, TIdent ident);// remonte une adresse pr stockage
	void action_VarExprD_Structure(tAttrExpression & res, tAttrExpression & expr, TIdent ident);// remonte une valeur pr utilisation
	// tableau -->
	void action_VarExprG_Tableau(tAttrExpression & res, tAttrExpression & expr, tAttrListIndices & indices);// remonte une adresse
	void action_VarExprD_Tableau(tAttrExpression & res, tAttrExpression & expr, tAttrListIndices & indices);// remonte une valeur
	
	// indice tableau ->
	void action_ListIndices(tAttrListIndices & res, tAttrExpression & expr);
	void action_ListIndices(tAttrListIndices & res, tAttrListIndices & src, tAttrExpression & expr);
	
	// appel des fct/proc
	void action_Call(tAttrExpression & res, TIdent & ident, tAttrListIndices & params);
	
	//comparaison d'expression
	void action_CompExpr_OP_EQ(tAttrExpression & res, tAttrExpression & x, tAttrExpression & y);
	void action_CompExpr_OP_NEQ(tAttrExpression & res, tAttrExpression & x, tAttrExpression & y);
	void action_CompExpr_OP_LT(tAttrExpression & res, tAttrExpression & x, tAttrExpression & y);
	void action_CompExpr_OP_LTE(tAttrExpression & res, tAttrExpression & x, tAttrExpression & y);
	void action_CompExpr_OP_Gt(tAttrExpression & res, tAttrExpression & x, tAttrExpression & y);
	void action_CompExpr_OP_GTE(tAttrExpression & res, tAttrExpression & x, tAttrExpression & y);
	
	// expression booleenne pure
	void action_BoolExpr_NOT(tAttrExpression & res, tAttrExpression & expr);
	void action_BoolExpr_AND(tAttrExpression & res, tAttrExpression & x, tAttrExpression & y);
	void action_BoolExpr_OR(tAttrExpression & res, tAttrExpression & x, tAttrExpression & y);
	void action_BoolExpr_XOR(tAttrExpression & res, tAttrExpression & x, tAttrExpression & y);
	
	void action_Parameters(tAttrListIndices & res);
	
	void action_BlockCode(tAttrListInstr & block, tAttrListInstr & instrList);
	void action_BlockCode(tAttrListInstr & block);
	void action_block(tAttrListInstr & block); // block TOTAL
























#endif
