#ifndef __ACTIONSMATH_H__
#define __ACTIONSMATH_H__

#include "Attributs.h"
#include "SymboleTemporaire.hpp"
#include <iostream>

extern int yyerror(char*);


/**
 * \file ActionMath.hpp
 * \brief En-tete des actions mathématique à réaliser lorsqu'on rencontre une opération
 * \author JeanMichel LE
 * \version 0.1
 * \date 3 novembre 2012
 *
 * Gestion des expressions mathématique
 */
using namespace std;

void math_check_operation_autoriser(tAttrExpression &op1);// verif id connu et pas procedure.

void actionMath_add(tAttrExpression &expr1, tAttrExpression &expr2);
/**
 * Multiplication
 */
void action_MAthExpr_OP_MUL(tAttrExpression &res, tAttrExpression &op1, tAttrExpression &op2);
/**
 * Division
 */
void action_MAthExpr_OP_DIV(tAttrExpression &res, tAttrExpression &op1, tAttrExpression &op2);

void action_MAthExpr_OP_DIVIDENTE(tAttrExpression &res, tAttrExpression &op1, tAttrExpression &op2);

void action_MAthExpr_OP_ADD(tAttrExpression & res, tAttrExpression & op1, tAttrExpression & op2);

void action_MAthExpr_OP_SUB(tAttrExpression & res, tAttrExpression & op1, tAttrExpression & op2);

/**
 * Met la valeur négatif op1
 */
void action_MAthExpr_OP_NEG(tAttrExpression & res, tAttrExpression & op1);

void action_MathExpr_MOD(tAttrExpression & res, tAttrExpression & op1, tAttrExpression & op2);

#endif
