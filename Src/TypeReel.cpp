#include <TypeReel.h>


TypeReel::TypeReel()
	: Type("")
{
}

bool TypeReel::operator==(const Type & type) const	 
{
	const TypeReel * t = dynamic_cast<const TypeReel*>(&type);
	return t!=0;
}


void TypeReel::printToStd() const
{
	std::cout << "reel";
}
