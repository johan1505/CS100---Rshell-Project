#ifndef __Paren_HPP__
#define __Paren_HPP__

#include "Base.hpp"

using namespace std;

class Paren : public Base {
    public:
	Paren(Base* userRight); //right is the default pointer	
        void execute();
	char* getFileName() { };	
};

#endif
