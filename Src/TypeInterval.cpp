#include <TypeInterval.h>
#include <iostream>



TypeInterval::TypeInterval(Type * typeOfBorne, Valeur borneInf, Valeur borneSup)
	: Type(""), type(typeOfBorne), inf(borneInf), sup(borneSup)
{
}


bool TypeInterval::operator==(Type const & type) const 
{
	TypeInterval const  *t = dynamic_cast<TypeInterval const*>(&type);
	if (t==0)	return false;// ce n'est meme pas un interval.
	
	return (inf == t->getInf() && sup == t->getSup());
}


void TypeInterval::printToStd() const
{
	std::cout << "<";
	if (type->estChaine()) {
		std::cout << "caractere";
	}else {
		type->printToStd();
	}	
	std::cout << ",";
	::printToStd(inf);
	std::cout << ",";
	::printToStd(sup);
	std::cout << ">";	
}
