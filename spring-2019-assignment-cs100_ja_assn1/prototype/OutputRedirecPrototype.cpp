#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <sys/wait.h>
#include  <sys/types.h>
using namespace std;

void executeProgram(char* arguments[]);
int main(){

	// Stuff for the execute function of the ">" operator
	int savestdout;
	savestdout = dup(1);	
	int file_desc = open("O2", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
	dup2(file_desc, 1);
	char* arg[] = { "ls", NULL };
	executeProgram(arg);
	close(file_desc);
	dup2(savestdout, 1);
	//truncate("OUTPUTFILE", 0);	
	cout << "Outputting to screen" << endl;
	//Stuff for the execute function of the ">>" operator
//	int savestdout;
//	savestdout = dup(1);
//	int file_desc = open("Nofile2", O_WRONLY | O_CREAT | O_APPEND);
//	dup2(file_desc, 1);
//	char* arg[] = { "ls", NULL };
//	executeProgram(arg);
//	dup2(savestdout, 1);
//	close(file_desc);

	//Stuff for the execute function of the "<" operator
//	int savestdin;
//        savestdin = dup(0);
//	int file_desc = open("OUTPUTFILE", O_RDONLY);
//	if (file_desc < 0){
//		perror("");
//	}
//	else {
//		dup2(file_desc, 0);
//		char* arg[] = {"cat", NULL};
//		executeProgram(arg);
//		dup2(savestdin, 0);
//	}
//	close(file_desc);
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
//                cout <<"Child process is executing. ID: " << pid <<  endl;
                if (execvp(arguments[0], arguments) < 0){ //execvp returns -1 if execution fails
                        perror("Execution Failed"); //Only gets here if execution fails
                        exit(1);
                }
        }
        else {
  //              cout << "Parent process is executing. ID: " << pid << endl;
                while(waitpid(-1, & status, 0) != pid){  //We use waitpid to wait for the child process to finish executing, THE -1 MEANS WAIT FOR ANY CHILD PROCESS TO FINISH
                        cout << "Wating for children to finish" << endl;
                }
        }
        return;
}
