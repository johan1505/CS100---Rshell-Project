#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__
#include "Base.hpp"
#include <vector>
using namespace std;

class Command : public Base {
    private: 
	char** exe;
    public:
        Command();
      	Command(const vector<char*> &args);
	~Command();
        void execute();
	char* getFileName();
};

#endif
