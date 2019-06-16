#ifndef __BASE_HPP__
#define __BASE_HPP__

#include <string>
using namespace std;

class Base {
    private: // if needed, this can be changed to proteceted
        bool execPassed;
    protected:
	Base* left;
	Base* right;
	Base* parent;
	string classType; 
    public:
        Base();
        virtual void execute() = 0; //pure virtual function. This function is commented out in order to test the Base class
        bool getExecPassed()const;
        void setExecPassed(bool execPassed);
	string getType() { return this->classType; }
	Base* getLeft() { return this->left; }
	Base* getRight() { return this->right; }
	Base* getParent() { return this->parent; }
	virtual char* getFileName() = 0;
	void setParent(Base* userPtr) { this->parent = userPtr;}
};

#endif
