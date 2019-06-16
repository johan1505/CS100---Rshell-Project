#ifndef __AND_HPP__
#define __AND_HPP__

#include "Base.hpp"

using namespace std;

class And : public Base {
    public:
	//Add();
	//Add(Base* userLeft);
	And(Base* userLeft, Base* userRight);
        void execute();
	char* getFileName() { };	
};

#endif

