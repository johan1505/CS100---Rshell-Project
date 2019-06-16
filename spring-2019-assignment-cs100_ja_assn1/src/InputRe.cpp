#include "../header/InputRe.hpp"


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include  <sys/types.h>

#include <iostream>
using namespace std;

InputRe::InputRe(Base* userLeft, Base* userRight) {
        this->left = userLeft;
        this->right = userRight;
        this->parent = nullptr;
        this->classType = "InputRe";
}

void InputRe::execute() {
        this->setExecPassed(false);


        int savestdin = dup(0);
        int file_desc = open(this->right->getFileName(), O_RDONLY);

        if (this->left->getType() == "Command" || this->left->getType() == "Paren" || this->left->getType() == "Pipe" || this->left->getType() == "InputRe" || this->left->getType() == "OutputReClear" || this->left->getType() == "OutputReApp" ) {
              

                if (file_desc < 0) { 
                        perror("");
                        this->setExecPassed(false); 
                }
                else {
                        dup2(file_desc, 0);
                        this->left->execute();
                        restore_Input(savestdin, file_desc);

                        if (this->left->getExecPassed() == true) { this->setExecPassed(true); }
                        else { this->setExecPassed(false); }
                }
        }
        else if (this->left->getType() == "And") {
               

                this->left->getLeft()->execute();
                if (this->left->getLeft()->getExecPassed() == true) {
                        if (file_desc < 0) {
                                perror("");
                                this->setExecPassed(false);
                        }
                        else {

                                dup2(file_desc, 0);
                                this->left->getRight()->execute();
                                restore_Input(savestdin, file_desc);

                                if (this->left->getRight()->getExecPassed() == true ) { this->setExecPassed(true); }
                                else { this->setExecPassed(false); }
                        }
                }
                else {
                        this->setExecPassed(false);
                }
        }
        else if (this->left->getType() == "Or") {
                

                this->left->getLeft()->execute();
                if (this->left->getLeft()->getExecPassed() == false) {
                        if (file_desc < 0) {
                                perror("");
                                this->setExecPassed(false);
                        }
                        else {

                                dup2(file_desc, 0);
                                this->left->getRight()->execute();
                                restore_Input(savestdin, file_desc);

                                if (this->left->getRight()->getExecPassed() == true) { this->setExecPassed(true); }
                                else { this->setExecPassed(false); }
                        }
                }
                else {
                        this->setExecPassed(true);
                }
        }
        else if (this->left->getType() == "Semicolon") {
                

                this->left->getLeft()->execute();
                if (file_desc < 0) {
                        perror("");
                        this->setExecPassed(false);
                }
                else {

                        dup2(file_desc, 0);
                        this->left->getRight()->execute();
                        restore_Input(savestdin, file_desc);

                        if (this->left->getRight()->getExecPassed() == true ) { this->setExecPassed(true); }
                        else { this->setExecPassed(false); }
                }
        }

        

        
        close(file_desc);
}



void InputRe::restore_Input(int &savestdin, int &file_desc){
        dup2(savestdin, 0);
        close(file_desc);
}
