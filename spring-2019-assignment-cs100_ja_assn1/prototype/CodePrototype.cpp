#include <iostream>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include  <sys/types.h>
using namespace std;

void executeProgram( char* arguments[]);
int main(int argc, char* argv[]){
	if (argc == 1){
	   cout << "Not enough arguments" <<  endl;
	}
	else {
	//	char* command = argv[1]; // points to the filename associated witht the file being executed
		char* arguments[argc] ;
		for (int i = 0; i < argc - 1; ++i) {
			arguments[i] = argv[i + 1];
		}
		arguments[argc - 1] = NULL; // Array pointers that represent the argument list. This array MUST terminate with a NULL pointer. 
					    // The first string has to be the filename to be executed
		executeProgram(arguments);
	}
	return 0;
}


void executeProgram(char* arguments[]){
	pid_t pid;
	int status;
	pid = fork();// Fork return the ID of the child to the parent,and it returns 0 to the child
	if (pid < 0) { // if fork() returns a negative number then forking the child process failed 
		perror("Forking Failed");
		exit(1);
	}
	else if(pid == 0) { // if the pid is 0 when we know it's the child process, so here we execute a command
		cout <<"Child process is executing. ID: " << pid <<  endl;
		if (execvp(arguments[0], arguments) < 0){ //execvp returns -1 if execution fails
			perror("Execution Failed"); //Only gets here if execution fails
			exit(1);
		}
	}
	else {
		cout << "Parent process is executing. ID: " << pid << endl;	
		while(waitpid(-1, & status, 0) != pid){	 //We use waitpid to wait for the child process to finish executing, THE -1 MEANS WAIT FOR ANY CHILD PROCESS TO FINISH
			cout << "Wating for children to finish" << endl;
		}
	}
	return;
}
