#ifndef __OUTPUTRECLEAR_HPP__
#define __OUTPUTRECLEAR_HPP__

#include "Base.hpp"

using namespace std;

class OutputReClear : public Base {
    public:
        OutputReClear(Base* userLeft, Base* userRight);
        void execute();
    private:
        void initializeFileDesc(int &savestdout, int &file_desc);
        void restore_CloseFile(int &savestdout, int &file_desc);
};

#endif
