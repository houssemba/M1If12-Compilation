#ifndef __MAP_IDENT__H
#define __MAP_IDENT__H

#include <map>
#include <string>

class MapIdent {
	public:
	MapIdent();

	int add(std::string const & name);
	std::string getName(int id);
	int getId(std::string const & name);
	/* affiche toute la table des identifiants. !! Sensible a la casse.*/
	void printToStd();


	private:
	std::map<std::string, int> _fromName;
	std::map<int, std::string> _fromId;
	std::map<std::string, int> _lowercase;
	int nbSymbol;
};


#endif
