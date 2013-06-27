#include <ConteneurCode.h>
#include <iostream>

using std::cout;
using std::endl;


ConteneurCode::ConteneurCode()
	: instructionList()
{
}
	
void ConteneurCode::push(Instruction i)
{
	instructionList.push_back(i);
}
	
void ConteneurCode::push(std::vector<Instruction> const & list)
{
	for (unsigned int i=0; i<list.size(); i++)
	{
		instructionList.push_back(list.at(i));
	}
}

void ConteneurCode::push(ConteneurCode const &c)
{
	push(c.instructionList);
}


void ConteneurCode::printToStd()
{
	for (unsigned int i=0; i<instructionList.size(); i++)
	{
		instructionList.at(i).printToStd();
		cout << endl;
	}
}
