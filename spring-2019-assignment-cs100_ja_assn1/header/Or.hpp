#ifndef __OR_HPP__
#define __OR_HPP__

#include "Base.hpp"

using namespace std;

class Or : public Base {
    public:

        Or(Base* userLeft, Base* userRight);
        void execute();
	char* getFileName() { };
};

#endif
