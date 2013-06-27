#include "ActionsMath.h"
#include <GestionTDS.hpp>

extern GestionTDS listTDS;

void math_check_operation_autoriser(tAttrExpression &op1)
{
	if (!op1.calculee) {
		Symbole * s1 = listTDS.getSymbole(op1.res);
		if (s1==0 || s1->estProcedure()) {
			char msg[] = " operation interdite (id inconnu ou id est procedure).";
			yyerror(msg);
		}
	}
}

void action_MAthExpr_OP_MUL(tAttrExpression &res, tAttrExpression &op1, tAttrExpression &op2) {
	
	math_check_operation_autoriser(op1);
	math_check_operation_autoriser(op2);
	
	if (! Type::compatibleMult(*op1.type , *op2.type)) {
		char msg[] = " multiplication entre type incompatible.";
		yyerror(msg);
	}
	
	res.code = new ConteneurCode();
	
	if (op1.calculee && op2.calculee) { 
	    // les deux valeurs sont calculable alors on effectue le calcul
		res.valeur = op1.valeur * op2.valeur;
		res.calculee = true;
	} else {
		
		res.calculee = false;
		
		if(op1.type->estReel() || op2.type->estReel()) {
		    // les deux opérandes sont des réels
			res.type = GenerateurType::creerTypeReel();
    	} else if (op1.type->estEntier() || op2.type->estEntier()) {
    	    // les deux opérandes sont des entiers
			res.type = GenerateurType::creerTypeEntier();
	    } else if (op1.type->estBooleen()) { // op2 forcement booleen grace a type::compatible
			res.type = GenerateurType::creerTypeBooleen();
    	} else { //forcement string
			res.type = GenerateurType::creerTypeChaine();
	}
	
	if (op1.calculee && !op2.calculee) {
	        // on ne peut calculer op2
			res.res = SymboleTemporaire::creerTemporaire(res.type);
			res.code->push(*op2.code);
			res.code->push(Instruction(OPCODE_MUL, Operande(res.res), Operande(op1.valeur), Operande(op2.res)));
		} else if (!op1.calculee && op2.calculee) {
		    //on ne peut calculer op1
			res.res = SymboleTemporaire::creerTemporaire(res.type);
			res.code->push(*op1.code);
			res.code->push(Instruction(OPCODE_MUL, Operande(res.res), Operande(op1.res), Operande(op2.valeur)));
		} else {
		    //!op1 && !op2
			res.res = SymboleTemporaire::creerTemporaire(res.type);
			res.code->push(*op1.code);
			res.code->push(*op2.code);
			res.code->push(Instruction(OPCODE_MUL, Operande(res.res), Operande(op1.res), Operande(op2.res))); 
			//res.code->printToStd();
		}	
	}
}

void action_MAthExpr_OP_DIV(tAttrExpression &res, tAttrExpression &op1, tAttrExpression &op2) {

	math_check_operation_autoriser(op1);
	math_check_operation_autoriser(op2);
	
	if (! Type::compatibleDiv(*op1.type , *op2.type)) {
		char msg[] = " division entre type incompatible.";
		yyerror(msg);
	}
	
	res.code = new ConteneurCode();
	
	if (op1.calculee && op2.calculee) { 
	    // les deux valeurs sont calculable alors on effectue le calcul
		res.valeur = op1.valeur / op2.valeur;
		res.calculee = true;
	} else {
		
		res.calculee = false;
		
		if(op1.type->estReel() || op2.type->estReel()) {
		    // les deux opérandes sont des réels
			res.type = GenerateurType::creerTypeReel();
    	} else if (op1.type->estEntier() || op2.type->estEntier()) {
    	    // les deux opérandes sont des entiers
			res.type = GenerateurType::creerTypeEntier();
	    } else if (op1.type->estBooleen()) { // op2 forcement booleen grace a type::compatible
			res.type = GenerateurType::creerTypeBooleen();
    	} else { //forcement string
			res.type = GenerateurType::creerTypeChaine();
	}
	
	if (op1.calculee && !op2.calculee) {
	        // on ne peut calculer op2
			res.res = SymboleTemporaire::creerTemporaire(res.type);
			res.code->push(*op2.code);
			res.code->push(Instruction(OPCODE_DIV, Operande(res.res), Operande(op1.valeur), Operande(op2.res)));
		} else if (!op1.calculee && op2.calculee) {
		    //on ne peut calculer op1
			res.res = SymboleTemporaire::creerTemporaire(res.type);
			res.code->push(*op1.code);
			res.code->push(Instruction(OPCODE_DIV, Operande(res.res), Operande(op1.res), Operande(op2.valeur)));
		} else {
		    //!op1 && !op2
			res.res = SymboleTemporaire::creerTemporaire(res.type);
			res.code->push(*op1.code);
			res.code->push(*op2.code);
			res.code->push(Instruction(OPCODE_DIV, Operande(res.res), Operande(op1.res), Operande(op2.res))); 
			//res.code->printToStd();
		}	
	}
}


// Division euclidienne
void action_MAthExpr_OP_DIVIDENTE(tAttrExpression &res, tAttrExpression &op1, tAttrExpression &op2) {
	math_check_operation_autoriser(op1);
	math_check_operation_autoriser(op2);
	
	if (! Type::compatibleDividente(*op1.type , *op2.type)) {
		char msg[] = " dividente entre type incompatible.";
		yyerror(msg);
	}
	
	res.code = new ConteneurCode();
	
	if (op1.calculee && op2.calculee) { 
        //division euclidienne de int
        if (op1.valeur.unionType == INT && op2.valeur.unionType == INT) {
            res.valeur.entier = (int)(op1.valeur.entier / op2.valeur.entier);
        }
        
        //division euclidienne de real
        if (op1.valeur.unionType == FLOAT && op2.valeur.unionType == FLOAT) {
            res.valeur.entier = (int)(op1.valeur.reel / op2.valeur.reel);
        }
        
        //division euclidienne de real + int
        if ((op1.valeur.unionType == INT && op2.valeur.unionType == FLOAT) || 
                (op1.valeur.unionType == FLOAT && op2.valeur.unionType == INT)) {
            if (op1.valeur.unionType == INT) {
                res.valeur.entier = (int)(op1.valeur.entier / op2.valeur.reel);
            } else {
                res.valeur.entier = (int)(op1.valeur.reel / op2.valeur.entier);
            }
        }
        res.valeur.unionType = INT;
        res.calculee = true;
	} else {
		
		res.calculee = false;

    	    // les deux opérandes sont forcement des entiers grace a type::compatible
			res.type = GenerateurType::creerTypeEntier();
	    
	if (op1.calculee && !op2.calculee) {
	        // on ne peut calculer op2
			res.res = SymboleTemporaire::creerTemporaire(res.type);
			res.code->push(*op2.code);
			res.code->push(Instruction(OPCODE_DIV, Operande(res.res), Operande(op1.valeur), Operande(op2.res)));
		} else if (!op1.calculee && op2.calculee) {
		    //on ne peut calculer op1
			res.res = SymboleTemporaire::creerTemporaire(res.type);
			res.code->push(*op1.code);
			res.code->push(Instruction(OPCODE_DIV, Operande(res.res), Operande(op1.res), Operande(op2.valeur)));
		} else {
		    //!op1 && !op2
			res.res = SymboleTemporaire::creerTemporaire(res.type);
			res.code->push(*op1.code);
			res.code->push(*op2.code);
			res.code->push(Instruction(OPCODE_DIV, Operande(res.res), Operande(op1.res), Operande(op2.res))); 
			//res.code->printToStd();
		}	
	}
}

void action_MAthExpr_OP_ADD(tAttrExpression & res, tAttrExpression & op1, tAttrExpression & op2)
{	
	math_check_operation_autoriser(op1);
	math_check_operation_autoriser(op2);
	if (! Type::compatiblePlus(*op1.type , *op2.type)) {
		char msg[] = " addition entre type incompatible.";
		yyerror(msg);
	}
	
	res.code = new ConteneurCode();
			
	if (op1.calculee && op2.calculee) {
		res.valeur = op1.valeur + op2.valeur;
		res.calculee = true;
	
	} else {
		
		res.calculee = false;
		if(op1.type->estReel() || op2.type->estReel()) {
			res.type = GenerateurType::creerTypeReel();
		}else if (op1.type->estEntier() || op2.type->estEntier()) {
			res.type = GenerateurType::creerTypeEntier();
		}else if (op1.type->estBooleen()) {// op2 forcement booleen grace a type::compatible
			res.type = GenerateurType::creerTypeBooleen();
		}else {//forcement string
			res.type = GenerateurType::creerTypeChaine();
		}
		if (op1.calculee && !op2.calculee) {
			res.res = SymboleTemporaire::creerTemporaire(res.type);
			res.code->push(*op2.code);
			res.code->push(Instruction(OPCODE_ADD, Operande(res.res), Operande(op1.valeur), Operande(op2.res)));
		}else if (!op1.calculee && op2.calculee) {
			res.res = SymboleTemporaire::creerTemporaire(res.type);
			res.code->push(*op1.code);
			res.code->push(Instruction(OPCODE_ADD, Operande(res.res), Operande(op1.res), Operande(op2.valeur)));
		} else {//!op1 && !op2
			res.res = SymboleTemporaire::creerTemporaire(res.type);
			res.code->push(*op1.code);
			res.code->push(*op2.code);
			res.code->push(Instruction(OPCODE_ADD, Operande(res.res), Operande(op1.res), Operande(op2.res))); 
			//res.code->printToStd();
		}	
	}
}

void action_MAthExpr_OP_SUB(tAttrExpression & res, tAttrExpression & op1, tAttrExpression & op2)
{
	math_check_operation_autoriser(op1);
	math_check_operation_autoriser(op2);
	
	if (! Type::compatiblePlus(*op1.type , *op2.type)) {
		char msg[] = " soustraction entre type incompatible.";
		yyerror(msg);
	}
	res.code = new ConteneurCode();
			
	if (op1.calculee && op2.calculee) {
		res.valeur = op1.valeur - op2.valeur;
		res.calculee = true;
	
	} else {
		
		res.calculee = false;
		if(op1.type->estReel() || op2.type->estReel()) {
			res.type = GenerateurType::creerTypeReel();
		}else if (op1.type->estEntier() || op2.type->estEntier()) {
			res.type = GenerateurType::creerTypeEntier();
		}else if (op1.type->estBooleen()) {// op2 forcement booleen grace a type::compatible
			res.type = GenerateurType::creerTypeBooleen();
		}else {//forcement string
			res.type = GenerateurType::creerTypeChaine();
		}
		if (op1.calculee && !op2.calculee) {
			res.res = SymboleTemporaire::creerTemporaire(res.type);
			res.code->push(*op2.code);
			res.code->push(Instruction(OPCODE_SUB, Operande(res.res), Operande(op1.valeur), Operande(op2.res)));
		}else if (!op1.calculee && op2.calculee) {
			res.res = SymboleTemporaire::creerTemporaire(res.type);
			res.code->push(*op1.code);
			res.code->push(Instruction(OPCODE_SUB, Operande(res.res), Operande(op1.res), Operande(op2.valeur)));
		} else {//!op1 && !op2
			res.res = SymboleTemporaire::creerTemporaire(res.type);
			res.code->push(*op1.code);
			res.code->push(*op2.code);
			res.code->push(Instruction(OPCODE_SUB, Operande(res.res), Operande(op1.res), Operande(op2.res))); 
			//res.code->printToStd();
		}	
	}
}

void action_MAthExpr_OP_NEG(tAttrExpression &res, tAttrExpression &op1) {

	if (!Type::compatibleNegation(*op1.type)) {
		char msg[] = " negation d'un type imcompactible.";
		yyerror(msg);
	}
	
	res.code = new ConteneurCode();
	res.type = op1.type;
	res.calculee = op1.calculee;
	res.calculable = op1.calculable;
	res.adressable = op1.adressable;
	
	if (op1.calculee) {
	    res.valeur = -op1.valeur;
	} else {
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(*op1.code);
		res.code->push(Instruction(OPCODE_NEG, Operande(res.res), Operande(op1.res), Operande(-45)));
	}
}

void action_MAthExpr_OP_SUP(tAttrExpression &res, tAttrExpression &op1) {

	if (!Type::compatibleNegation(*op1.type)) {
		char msg[] = " negation d'un type imcompactible.";
		yyerror(msg);
	}
	
	res.code = new ConteneurCode();
	res.type = op1.type;
	res.calculee = op1.calculee;
	res.calculable = op1.calculable;
	res.adressable = op1.adressable;
	
	if (op1.calculee) {
	    res.valeur = -op1.valeur;
	} else {
		res.res = SymboleTemporaire::creerTemporaire(res.type);
		res.code->push(*op1.code);
		res.code->push(Instruction(OPCODE_NEG, Operande(res.res), Operande(op1.res), Operande(-45)));
	}
}

#include <ActionExpression.h>

void action_MathExpr_MOD(tAttrExpression & res, tAttrExpression & op1, tAttrExpression & op2)
{
/*	if( !op1.type->estEntier() || !op2.type->estEntier()) {
		char msg[] = "mod reserver pour les entiers";
		yyerror(msg);
	}
	int r = SymboleTemporaire::creerTemporaire(GenerateurType::creerTypeEntier());
	
	tAttrExpression cond ;
	tAttrListInstr resTmp, exprR;
	
	exprR.code = new ConteneurCode();
	action_CompExpr_OP_GTE(cond, op1, op2);
	//action_MAthExpr_OP_SUB(exprR, exprR, op2);
	if (op2.calculee) exprR.code->push(Instruction(OPCODE_SUB, Operande(r), Operande(r), Operande(op2.valeur)));
	else			  exprR.code->push(Instruction(OPCODE_SUB, Operande(r), Operande(r), Operande(op2.res)));	
	
	res.code = new ConteneurCode();
	if (op1.calculee) 	res.code->push(Instruction(OPCODE_CPY, Operande(r), Operande(op1.valeur), Operande(-45)));
	else				res.code->push(Instruction(OPCODE_CPY, Operande(r), Operande(op1.res), Operande(-45)));
	action_Instr_While(resTmp, cond, exprR);
	
	res.code->push(*resTmp.code);
	
*/	
}




















