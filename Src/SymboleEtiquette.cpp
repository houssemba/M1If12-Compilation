#include <SymboleEtiquette.h>
#include <MapIdent.h>
#include <GestionTDS.hpp>
#include <sstream>

extern MapIdent identTable;
extern GestionTDS listTDS;



int SymboleEtiquette::whileCount = 0;
int SymboleEtiquette::ifCount = 0;
int SymboleEtiquette::repeatCount = 0;
int SymboleEtiquette::forCount = 0;

void SymboleEtiquette::creerWhileShort(int &start)
{
	std::ostringstream ss;
	ss << whileCount;
	string nameTmp = "__%%_WH" + ss.str();
	whileCount++;
	int ret = identTable.add(nameTmp);
	
	listTDS.ajouter( new SymboleEtiquette(ret) );
	
	start = ret;
}

void SymboleEtiquette::creerWhileLong(int &start,int &body,int &end)
{
	std::ostringstream ss;
	ss << whileCount;
	string nameTmpS = "__%%_WH" + ss.str();
	string nameTmpB = "__%WHBd" + ss.str();
	string nameTmpE = "__%WHEd" + ss.str();
	whileCount++;
	// add to the TI
	start = identTable.add(nameTmpS);
	body = identTable.add(nameTmpB);
	end = identTable.add(nameTmpE);
	//add to the TS
	listTDS.ajouter( new SymboleEtiquette(start) );
	listTDS.ajouter( new SymboleEtiquette(body) );
	listTDS.ajouter( new SymboleEtiquette(end) );
	
}

void SymboleEtiquette::creerIfShort(int & ifBody, int & ifEnd)
{
	std::ostringstream ss;
	ss << ifCount;
	string nameTmpB = "__%IFBd" + ss.str();
	string nameTmpE = "__%IFEd" + ss.str();
	ifCount++;
	// add to the TI
	ifBody = identTable.add(nameTmpB);
	ifEnd = identTable.add(nameTmpE);
	//add to the TS
	listTDS.ajouter( new SymboleEtiquette(ifBody) );
	listTDS.ajouter( new SymboleEtiquette(ifEnd) );
}

void SymboleEtiquette::creerIfLong(int & ifBody, int & ifElse)
{
	std::ostringstream ss;
	ss << ifCount;
	string nameTmpB = "__%IFBd" + ss.str();
	string nameTmpE = "__%IFEl" + ss.str();
	ifCount++;
	// add to the TI
	ifBody = identTable.add(nameTmpB);
	ifElse = identTable.add(nameTmpE);
	//add to the TS
	listTDS.ajouter( new SymboleEtiquette(ifBody) );
	listTDS.ajouter( new SymboleEtiquette(ifElse) );
}

void SymboleEtiquette::creerRepeatLong(int & repStart, int & repEnd)
{
	std::ostringstream ss;
	ss << repeatCount;
	string nameTmpB = "__%RPSt" + ss.str();
	string nameTmpE = "__%RPEd" + ss.str();
	repeatCount++;
	// add to the TI
	repStart = identTable.add(nameTmpB);
	repEnd = identTable.add(nameTmpE);
	//add to the TS
	listTDS.ajouter( new SymboleEtiquette(repStart) );
	listTDS.ajouter( new SymboleEtiquette(repEnd) );
}

void SymboleEtiquette::creerRepeatShort(int & repeat)
{
	std::ostringstream ss;
	ss << repeatCount;
	string nameTmpB = "__%RPSt" + ss.str();
	repeatCount++;
	// add to the TI
	repeat = identTable.add(nameTmpB);
	//add to the TS
	listTDS.ajouter( new SymboleEtiquette(repeat) );
}

void SymboleEtiquette::creerFor(int & forTest, int & forEnd)
{
	std::ostringstream ss;
	ss << forCount;
	string nameTmpB = "__%frSt" + ss.str();
	string nameTmpE = "__%frEd" + ss.str();
	forCount++;
	// add to the TI
	forTest = identTable.add(nameTmpB);
	forEnd = identTable.add(nameTmpE);
	//add to the TS
	listTDS.ajouter( new SymboleEtiquette(forTest) );
	listTDS.ajouter( new SymboleEtiquette(forEnd) );
}

void SymboleEtiquette::printToStd() {

    cout << endl;
}
