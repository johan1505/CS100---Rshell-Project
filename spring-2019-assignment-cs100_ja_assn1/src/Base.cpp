#include "../header/Base.hpp"

Base::Base() : execPassed(true){} 
// Assume the executions always pass, this will be changed if they fail. 
//This can be changed if necessary.

bool Base::getExecPassed()const{
    return this->execPassed;
}

void Base::setExecPassed(bool execPassed){
    this->execPassed = execPassed;
    return;
}
