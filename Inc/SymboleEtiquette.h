#ifndef __SYMBOLE_ETIQUETTE_H
#define __SYMBOLE_ETIQUETTE_H

#include <Symbole.hpp>


class SymboleEtiquette : public Symbole
{
	private:
	
	SymboleEtiquette(int id) : Symbole("etiquette", id) {}
	static int whileCount;
	static int ifCount;
	static int repeatCount;
	static int forCount;
	
	public:
	
	static void creerWhileShort(int & start);
	static void creerWhileLong(int &start,int &body,int &end); 
	
	static void creerIfShort(int & ifBody, int & ifEnd);
	static void creerIfLong(int & ifBody, int & ifElse);
	
	static void creerRepeatShort(int & repeat);
	static void creerRepeatLong(int & repStart, int & repEnd);
	
	static void creerFor(int & forTest, int & forEnd);
	
	void printToStd();
	
	
	
	bool estEtiquette() { return false; }
};






























#endif
