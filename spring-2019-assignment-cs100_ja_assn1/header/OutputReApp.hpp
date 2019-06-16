#ifndef __OUTPUTREAPP_HPP__
#define __OUTPUTREAPP_HPP__

#include "Base.hpp"

using namespace std;

class OutputReApp : public Base {
    public:
        OutputReApp(Base* userLeft, Base* userRight);
        void execute();
    private:
        void initializeFileDesc(int &savestdout, int &file_desc);
        void restore_CloseFile(int &savestdout, int &file_desc);
	    char* getFileName() { };
};

#endif
