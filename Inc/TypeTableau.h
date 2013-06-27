#ifndef __TYPE_TABLEAU_H
#define __TYPE_TABLEAU_H

#include "Type.hpp"

#include <vector>

class TypeTableau : public Type
{
	private:
        std::vector<Type*> dims;
        Type * typeContained;
            
	public:
        TypeTableau(Type * typeContained, std::vector<Type*> const & dimsList); 
        
        bool operator==(Type const & type) const;
        
        void printToStd() const;
        
        bool estTableau() const { return true; }
        
        Type * getTypeContained() { return typeContained; }
        
        std::vector<Type*> getDims() { return dims; }
};

#endif
