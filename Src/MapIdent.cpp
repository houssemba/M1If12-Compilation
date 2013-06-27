#include <MapIdent.h>

#include <iostream>
#include <algorithm>
#include <vector>

MapIdent::MapIdent()
{
	nbSymbol = 0;
}

int MapIdent::add(std::string const & name)
{
    std::string tmp(name);
    std::transform(tmp.begin(), tmp.end(), tmp.begin(),(int(&)(int))std::tolower);

    std::map<std::string, int>::iterator it = _lowercase.find(tmp);
    if (it != _lowercase.end()) return (*it).second;

	// add it in the two map with the same nbSymbol
	_fromName[name] = nbSymbol;
	_fromId[nbSymbol] = name;
    _lowercase[tmp] = nbSymbol;

	return nbSymbol++; // post incrementation to the next identifiant.
}

std::string MapIdent::getName(int id)
{
	if (id < 0)	return "";
	std::map<int, std::string>::iterator it =_fromId.find(id);
	if (it == _fromId.end())	return "";
	return (*it).second;
}

int MapIdent::getId(std::string const & name)
{
    std::string tmp(name);
    std::transform(tmp.begin(), tmp.end(), tmp.begin(),(int(&)(int))std::tolower);

	std::map<std::string, int>::iterator it = _lowercase.find(tmp);
	if (it == _lowercase.end())	return -1;
	return (*it).second;
}

void MapIdent::printToStd()
{
	std::cout << "** Table Identificateur" << std::endl;
	std::map<std::string, int>::iterator it = _fromName.begin();
	std::vector<std::string> nameList;/*utiliser pour trier les noms.*/
	for(;it != _fromName.end(); it++)
	{
		nameList.push_back(it->first);
	}

	sort(nameList.begin(), nameList.end());
	std::vector<std::string>::iterator itName = nameList.begin();
	for(;itName != nameList.end(); itName++)
	{
		std::cout << *itName << " " << _fromName[*itName] <<std::endl;
	}

}
