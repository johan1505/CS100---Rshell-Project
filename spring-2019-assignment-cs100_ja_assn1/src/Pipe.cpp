#include "../header/Pipe.hpp"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;

Pipe::Pipe(Base* userLeft, Base* userRight) {
        this->left = userLeft;
        this->right = userRight;
        this->parent = nullptr;
        this->classType = "Pipe";
}


void Pipe::execute() {
        

        if (this->left->getType() == "Command" || this->left->getType() == "Paren" || this->left->getType() == "Pipe" || this->left->getType() == "InputRe" || this->left->getType() == "OutputReClear" || this->left->getType() == "OutputReApp" ){
                executePipe(0);
                this->setExecPassed(this->left->getExecPassed());
        }
        else if (this->left->getType() == "And") {
                this->left->getLeft()->execute();
                if (this->left->getLeft()->getExecPassed() == true) {
                    executePipe(1);

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
                    executePipe(1);

                    if (this->left->getRight()->getExecPassed() == true ) { this->setExecPassed(true); }
                    else { this->setExecPassed(false); }
                        
                }
                else {
                        this->setExecPassed(true);
                }
        }
        else if (this->left->getType() == "Semicolon") {
                executePipe(1);

                if (this->left->getRight()->getExecPassed() == true) { this->setExecPassed(true); }
                else { this->setExecPassed(false); }
        }


}

void Pipe::executePipe(int flag){
        int pipefd[2];
        int pid;
        int status;
        int saveStdIn;
        int saveStdOut;
        // make a pipe (fds go in pipefd[0] and pipefd[1])
         //
        if (pipe(pipefd) == -1){
                perror("pipe failed");
                exit(1); // 1 represents a failure
        }
        pid = fork();
        if (pid == -1){
                perror("fork failed");
                exit(1); // 1 represents a failure
        }
        if (pid == 0) {
                // Child process closes up the input side of pipe
                close(pipefd[0]);
                //Child process is gonna send data through the output side of the pipe
                saveStdOut = dup(1); // save stdout
                if (saveStdOut == -1){
                        perror("dup of child failed");
                        exit(1);
                }
                if (dup2(pipefd[1], 1) == -1){ // replace the standard output with the output side of the pipe
                        perror("dup2.0 of child failed");
                        exit(1);
                }
                // execute left child command
                if (flag == 0){
                	this->left->execute(); // This might need to change and might need to add another if branch that chckes for errors thorm form execvp
                }
		else {
			this->left->getRight()->execute();
		}
		// The data from this command should have been sent to the output side of the pipe
                if (dup2(saveStdOut, 1) == -1){ // Restore stdout back
                        perror("dup2.1 of parent failed");
                        exit(1);
                }
                close(pipefd[1]);    // Child process closes up the output side of the pipe
                exit(0);  // if reached here verything went well, 0 means success
        }
        else {
                while (waitpid(-1, &status,0) != pid){} //We use waitpid to wait for the child process to finish executing, THE -1 MEANS WAIT FOR ANY CHILD PROCESS TO FINISH
                if (status > 0 || WEXITSTATUS(status) == 1){ // if child prorcess failed then . MIGHT NEED TO GET RID OF THIS BRANCH
                   perror("Child process failed");
                   exit(1);
                }
                else { //Else the child process was successful so it's safe to proceed
                        // Parent process closes up the output side of pipe
                        close(pipefd[1]);
                        //Parent process is gonna receive up data through the input side of the pipe
                        saveStdIn = dup(0); // save stdin
                        if (saveStdIn == -1){
                                perror("dup of parent failed");
                                exit(1);
                        }
                        if (dup2(pipefd[0], 0) == -1){ // replace standard input with the input side of the pipe
                                perror("dup2.0 of parent failed");
                                exit(1);
                        }
                        // execute the Right child command
                        this->right->execute();
                        //The data necessary for this command should have come from the input side of the pipe
                        if (dup2(saveStdIn, 0) == -1){ // Restore stdin back
                                perror("dup2.1 of parent failed");
                                exit(1);
                        }
                        close(pipefd[0]);  // Child process closes up the input side of the pipe
                }
        }
}
