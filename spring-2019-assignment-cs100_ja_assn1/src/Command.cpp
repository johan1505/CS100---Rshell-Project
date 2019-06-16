#include "../header/Command.hpp"
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include  <sys/types.h>
#include <iostream>
#include <sys/stat.h>
using namespace std;

Command::Command(){ this->left = nullptr;
		    this->right = nullptr;
		    this->parent = nullptr;
		    this->classType = "Command";
}
		    
 // this should automatically call the default constructor of the Base class

Command::~Command(){ delete []exe; }

Command::Command(const vector<char*>&args){
	this->left = nullptr;
	this->right = nullptr;
	this->parent = nullptr;
	this->classType = "Command";
	exe = new char* [args.size()];
	for (unsigned i = 0; i < args.size(); i++){
		exe[i] = args.at(i);
	}
}

void Command::execute(){
	if (static_cast<string>(exe[0]) == "exit"){
		exit(0);
	}
	else if (static_cast<string>(exe[0]) == "test"){
		struct stat statBuf;
		if (static_cast<string>(exe[1]) != "-e" && static_cast<string>(exe[1]) != "-d" && static_cast<string>(exe[1]) != "-f"){ // If the string at pos 1 is not any of these flags ten we have to use the -e test flag
			if(stat(exe[1], &statBuf) != 0){
				cout << "(False)" << endl;
				this->setExecPassed(false);
			}
			else {
				cout << "(True)" << endl;
				this->setExecPassed(true);
			}	
		}
		else {	
			if (stat(exe[2], &statBuf) != 0){ //Note: stat() returns -1 if it fails and 0 if it succeeds. Should setExecPassed be called here???
				cout << "(False)" << endl;
				this->setExecPassed(false);
			}
			else { //Note macros evaluate to a nonzero value if the test is true and to 0 if the test is false
				if (static_cast<string>(exe[1]) == "-e"){
				//	cout << "-e branch is taken" << endl;
					cout << "(True)" << endl;
					this->setExecPassed(true);
				}
				else if (static_cast<string>(exe[1]) == "-f"){
				//	cout << "-f branch is taken" << endl;
					if (S_ISREG(statBuf.st_mode) != 0){
						 cout << "(True)" << endl;
                              	  		 this->setExecPassed(true);
					}
					else {
						cout << "(False)" << endl;
						this->setExecPassed(false);
					}
                       		 }
				else if (static_cast<string>(exe[1]) == "-d"){
				//	cout << "-d branch is taken" << endl;
                                	if (S_ISDIR(statBuf.st_mode) != 0){
                                        	 cout << "(True)" << endl;
                                        	 this->setExecPassed(true);
                                	}
                               		 else {
                                        	cout << "(False)" << endl;
                                       		this->setExecPassed(false);
                               		 }
                       		 }
			}
		}
	}
	else {
		pid_t pid;
		int status;
		pid = fork();// Fork return the ID of the child to the parent,and it returns 0 to the child
		if (pid < 0) { // if fork() returns a negative number then forking the child process failed 
			perror("Forking Failed");
			exit(1);
		}
		else if(pid == 0) { // if the pid is 0 when we know it's the child process, so here we execute a command
			//cout <<"Child process is executing" << endl; // This line of code will be ran assuming that args at least stores the name of an executable
			if (execvp(exe[0], exe) == -1){ //execvp returns -1 if execution fail
				perror(""); //Only gets here if execution fails
				exit(1);	
			}
      		  // if execution is sucessful then execPassed remains true;
		}
		else {
			//cout << "Parent process is executing" << endl;	
			while(waitpid(-1, & status, 0) != pid){}	 //We use waitpid to wait for the child process to finish executing, THE -1 MEANS WAIT FOR ANY CHILD PROCESS TO FINISH
			if (status >0 || WEXITSTATUS(status) == 1){// If execution failed then set execPassed to false
			   this->setExecPassed(false);
			}		
		}
	}
	return;
}


char* Command::getFileName() {
	return exe[0];
}





