#ifndef __PIPE_HPP__
#define __PIPE_HPP__

#include "Base.hpp"

using namespace std;

class Pipe : public Base {
    public:
        Pipe(Base* userLeft, Base* userRight);
        void execute();
	    char* getFileName() { };
    private:
        void executePipe(int flag);
};

#endif
