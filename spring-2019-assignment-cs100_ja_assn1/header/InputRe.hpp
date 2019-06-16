#ifndef __INPUTRE_HPP__
#define __INPUTRE_HPP__

#include "Base.hpp"

using namespace std;

class InputRe : public Base {
    public:
        InputRe(Base* userLeft, Base* userRight);
        void execute();
	char* getFileName() { };
    private:
	void restore_Input(int &savestdin, int &file_desc);
};

#endif
