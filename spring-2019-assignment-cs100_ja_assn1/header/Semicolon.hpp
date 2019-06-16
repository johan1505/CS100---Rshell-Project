#ifndef __SEMICOLON_HPP__
#define __SEMICOLON_HPP__

#include "Base.hpp"

using namespace std;

class Semicolon : public Base {
    public:
        Semicolon(Base* userLeft, Base* userRight);
	void execute();
	char* getFileName() { };

};

#endif

