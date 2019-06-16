#include "../header/OutputReApp.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include  <sys/types.h>



OutputReApp::OutputReApp(Base* userLeft, Base* userRight) {
        this->left = userLeft;
        this->right = userRight;
        this->parent = nullptr;
        this->classType = "OutputReApp";
}

void OutputReApp::execute() {
        this->setExecPassed(false);
        int savestdout = 0;
        int file_desc = 0;

        if (this->left->getType() == "Command" || this->left->getType() == "Paren" || this->left->getType() == "Pipe" || this->left->getType() == "InputRe" || this->left->getType() == "OutputReClear" || this->left->getType() == "OutputReApp"){
                initializeFileDesc(savestdout, file_desc);
                this->left->execute();
                restore_CloseFile(savestdout, file_desc); 
                
                this->setExecPassed(this->left->getExecPassed());
        }
        else if (this->left->getType() == "And") {
                this->left->getLeft()->execute();
                if (this->left->getLeft()->getExecPassed() == true) {
                    initializeFileDesc(savestdout, file_desc); 
                    this->left->getRight()->execute();
                     restore_CloseFile(savestdout, file_desc); 

                    if (this->left->getRight()->getExecPassed() == true ) { this->setExecPassed(true); }
                    else { this->setExecPassed(false); }
                }
                else {
                        this->setExecPassed(false);
                }
        }
        else if (this->left->getType() == "Or") {
                this->left->getLeft()->execute();
                if (this->left->getLeft()->getExecPassed() == false) {
                    initializeFileDesc(savestdout, file_desc);
                    this->left->getRight()->execute();
                    restore_CloseFile(savestdout, file_desc);

                    if (this->left->getRight()->getExecPassed() == true ) { this->setExecPassed(true); }
                    else { this->setExecPassed(false); }
                        
                }
                else {
                        this->setExecPassed(true);
                }
        }
        else if (this->left->getType() == "Semicolon") {
                this->left->getLeft()->execute();
                initializeFileDesc(savestdout, file_desc);
                this->left->getRight()->execute();
                restore_CloseFile(savestdout, file_desc);

                if (this->left->getRight()->getExecPassed() == true) { this->setExecPassed(true); }
                else { this->setExecPassed(false); }
        }


}

void OutputReApp::initializeFileDesc(int &savestdout, int &file_desc){
        savestdout = dup(1);
        file_desc  = open(this->right->getFileName(), O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
        dup2(file_desc, 1);
}

void OutputReApp::restore_CloseFile(int &savestdout, int &file_desc){
        dup2(savestdout, 1);
        close(file_desc);
}
