# CS 100 Programming Project

SPRING 2019

Team Members:
* Johan Guzman Avalos -- 861312308
* Adrian De La Torre  -- 862047345

# INTRODUCTION

Our program will be able to emulate the functionality of a command shell. Our "rshell" program will be capable of take in command lines and arguments as inputs, parse the given input, and execute the commands taking into consideration the possible connectors that may come along with the command. Our program will be developed following a composite pattern. The input from the user will be analyzed and decomposed by a parsing function. As the input is decomposed, it will be transformed into Command or Connector classes that, through an interface, will form a composite object that will be able to be recursively executed.  

# DIAGRAM

![UML Diagram](https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/blob/master/images/Basic%20Command%20shell%20(new%20idea).png?raw=true)

# CLASSES

*Base Class*

The Base class will act as our interface and will contain the pure virtual function execute() which is  meant to be implemented within both the leaf and composite classes. There is also a bool execPassed, along with the implementation of it's set and get functions since they are common among the composite and base classes. Essentially, the base class serves as the connection between these classes in order to allow for recursive composition to be possible.

*Command Class*  

The Command class is our leaf class which will implement the function execute(), making use of the waitpid(), execvp() and fork() in order to make the correct execution of commands or to notify if there was a failed execution and setting execPassed accordingly. The class attribute will be an array of char* named exe and will be passed through to the previously mentioned functions.


*SemiColon Class*

The SemiColon class will implement the execute function as followed: The function will initialize execPassed as false and will perform an execute on both the left Base pointer and right Base pointer no matter what. Then it will call right -> getExecPassed(). Then the execPassed will be set to match the right child's return.

*And Class*

The And class will implement the execute function as followed: The function will initialize execPassed as **false** and will perform an execute on the left Base pointer, then call left -> getExecPassed(). If the call returns **true** then the right Base pointer will be executed, at which point  it will call right -> getExecPassed() and the execPassed will be set to match the right child's return.

*Or Class*

The Or class will implement the execute function as followed: The function will initialize execPassed as **true** and will perform an execute on the left Base pointer, then call left -> getExecPassed(). If the call returns **false** then the right Base pointer will be executed, at which point  it will call right -> getExecPassed() and the execPassed will be set to match the right child's return.

# PROTOTYPES/RESEARCH

### Prototype Findings

- execvp()
    - The execvp() function takes as paramaters:
        - 1st paremeter: A char pointer that points to a null-terminated string that represents tha name of the executable to execute
        - 2nd parameter: An array of char pointers(the first element in this array has to be the name of the executable, the remaining elements represent the list of arguments), this array **must terminate with a NULL pointer**
    - execvp() returns -1 if execution fails

- fork()
    - The fork() system call serves to create a new process
    - New processes become child processes of the caller, the parent process    
    - After a child process is created, both parent and child will execute the next instruction followng the fork() system call
    - fork() retuns the ID of child (positive number) to the parent process, and it returns 0 to the child process
    - If fork() returns a negative number then forking the child process failed

- waitpid()
    - After a fork() system call, this function serves to avoid making child processes "zombies"
    - waitpid() is used to suspend execution of the calling process
    - Execution of the calling process is suspended until its child process finish execution
    - A parent process should use waitpid() to wait for its child process to finish execution

We plan to use these three functions as helpers in the implementation of the execute() function of the leaf class Command. Our excute function will responsible for the proper execution ot user-inputted commands; this will be accomplished by using the fork() system call to create a child process that calls the execvp() function which will execute a command. The waitpid() function will be used to make the parent process wait until the command has been sucessfully executed or failed execution. If execvp() returns -1, we will set the inherited bool variable execPassed to false. This will let know the parent composite that its left or right child object failed executing its command and thus decide whether or not its right child should be executed or ignored before trickling back up.

### Connectors Preliminary Testing

#### Assignment 2 Findings

We started testing how connectors interact in different situation with some basic commands.

```
git map && vim READ.md || git status
```

When running this command line in hammer, the first command (git map) is executed, but it fails; therefore, the second command (vim READ.md) is ignored and not executed. Furthermore, the last command (git status) also gets executed, and it succeeds. The last command was executed not because the second command was not executed but because the first command, the last command attempted to be executed, failed thus respecting the rule of the connector "||" that says "the next command is executed if the first one fails." 

```
git map || vim READ.md && git status
```

This basic command showed us that the flow of how commands are executed due to intermidiate connectors can be chained. As we know, the first command failed. Since the connector to the next command is "||" the second command is executed and succeeds. At this point, the next connector is "&&" and since the previous commandd was sucessful executed, the third command gets executed. 

Moreover, testing more complex command line revealed us more insight about how a shell program ingests and executes user inputs

```
ls -a; ech world || eho test || git map; git status
```

When executing this command line, the first command (ls -a) gets executed. The second command (ech world) is executed and fails due to a syntax error; since this command failed and the connector to the next command is "||", the third command (eho test) is also excuted, but it also fails. Similarly, the fourth command (git map) is attempeted to execute and fails. The third and fourth commands were executed only because their **last commands (ech world and eho test, respectively) were executed and failed**. Thus, the rule for connector "||" shows that the command after "||" is executed only if the **last command executed fails.** Furthermore, the fifth command (git status) gets successfully executed regardless of the unsucessful execution of the previous command (git map).

```
ls -a; echo hello || echo lol || git map; git status
```

This command line is almost the same as the previous one, but the second command (echo hello) now is successfully executed. Because of this and the presence of the "||" connector, the third command gets ignored and not executed. Similarly, the fourth commad (git map) gets ignored and not executed since the last command executed (echo world) did not fail. And again, the fifth command (git status) is sucessfully executed regardless of the no execution of the previous command (git map).

```
echo world || vim REARD.md && ech test || git status
```

In a similar way, this command line demonstrates how the "&&" works. This first command (echo world) is successfully executed. The second command (vim READ.md) is not executed because of the "||" connector. The third command (ech test) is executed since the last command executed (echo world) was succesful; however, this command fails, and because of the "||" that follows it, the fourth command (git status) is successfully executed.


#### Assignment 3 Findings

We started to consider how parantheses affected the precedence of operators

First, we consider a simple command:

```
echo world && (echo hi && echo bye)
```

This command first executes echo world and since it succeeds, it then executed the commmands inside of the parentheses; echo hi gets executed first and since it succeeds, echo bye gets executed next. In our composite tree this command would be represented by a tree having the first && operator at the root, the command ehco world as the left child of the root, and the right child of the root would be a subtree with the second && operator at its root and the commands echo hi and echo bye as the left and right children respectively.

Another series of commands that we consider had multiple commands inside of parenthesis:

```
git status && (echo world && echo hi || echo bye) && git status
```

This command first executes the first git status, then it executes the commands inside of the parentheses, first executeds echo world then echo hi and it skips the command echo bye, finally the second git status command gets executed. In our composite tree, this series of commands would be represented by a tree with the second && at the root, the left child of the root would be a subtree with the first && operator at the root-- its left child would be the first git status and the right child would be the another subtree composed of the commands inside of the parentheses. Finally the right child of the root would be the second git status command.

Also, for the test functionality portion of this assignment we tested the following commands at our root directory

```
test -e unit_tests/unit_test.cpp && echo "File/Directory exists"
```

This command outputs "File exists" since the file unit_test.cpp file exists inside of the directory unit_tests and the test command returns TRUE thus executing the command echo "File exists" that comes after the && operator

```
test -f unit_tests/unit_test.cpp && echo "File/Directory exists and is a regular file"
```

This command outputs "File exists and is a regular file". Since here we are using the -f flag, the test command checks if the file at the provided path is a regular file, and since unit_test.cpp is one, it returns TRUE thus executing the command echo "File exists and is a regular file"

```
test -d unit_tests && echo "File/Directory exists and is a directory"
```

This command outputs "File/Directory exists and is a directory". Since here we are using the -d flag, the test command checks if the file at the provided path is a directory, and since unit_tests is one, it returns TRUE thus executing the command echo "File/Directory exists and is a directory"

#### Assignment 4 Findings

We started by testing simple commands that involved I/O redirectioning.

```
echo world > testFile
```

The above command redirectioned the output of the command "echo world" to the file "testFile". We noticed that, when we ran this command, the file "testFile" did not exist in our current directory. This showed us that, since it didn't exist, the file was created for us.

```
cat > testfile
```

This command ran the executable cat, which takes input from the user, and redirections that input into the file "testFile." In this case, the file "testFile" was overwritten with the output of "cat". We concluded that the ">" operator always overwrites the testfile on its right side.

We also tested some more complex commands that involved I/0 redirectioning.

```
echo world && echo hi > testfile
```

This command executed the command "echo world" sending its output to the standard output. Then it redirectioned the output of the command "echo hi" to the file "testfile". We noticed that the ">" operator only sends the ouput of the command on its lefthand side to the file on its righthand side. 
Note: This finding also applies to the ">>" operator.

```
echo world >> testfile && echo hi
```

This command first redirections the output of the command "echo world" to the file "testfile". Since this execution was successful, the command after the "&&" connector gets executed and thus "hi" is outputted to the standard output.

```
ech world > testfile && echo hi
```

On the othr hand, this command attempts to redirections the output of the command "ech world" to the file "testfile"; however, since the command fails the execution of the redirection also fails. As a consequence, the command after the "&&" connector does not get executed.


Conclusions from preliminary testing:

* A command can be executed or not be executed
* If a command is executed, the execution can either succeed or fail
* Connectors play an important roll when deciding what commands to do not execute.
* Commands that are not executed are simply ignored and not taken into consideration when making the decision of whether or not execute the next command 
* A command that is after the ";" connector is always executed, regardless of whether the previous command is executed or not. 
* The command after "||" connector is executed only if the last command executed fails.
* The command after "&&" connector is executed only if the last command executed succeeds.

# DEVELOPMENT AND TESTING ROADMAP

Tasks to be completed:

- [x] [#1][i1] Include the gtest framework (git submodule …)
- [x] [#2][i2] Create CMakeLists.txt
- [x] [#3][i3] Set up unit_test.cpp file
- [x] [#4][i4] Set up main so that it continuously gets user input and calls the respective functions to decompose the given command lines.
- [x] [#5][i5] Implement the functionality of the parse function in the main.cpp file
- [x] [#6][i6] Unit test the parse function's helper functions
- [x] [#7][i7] Make Base class header file (base.h) (class is abstract — execute() function is pure virtual)
- [x] [#8][i8] Implement getExecPassed() and setExecPassed() in base.cpp
- [x] [#9][i9] Unit test getExecPassed() and setExecPassed() 
- [x] [#10][i10] Make Command class header file(command.h) — this class inherits from the Base class
- [x] [#11][i11] Implement the execute() function of the command class (using execvp(), fork(), and waitpid()) along with any helper function needed in its command.cpp file
- [x] [#12][i12] Unit test the helper functions and the execute() functions of Command class
- [x] [#13][i13] Make Connector class header file (connector.h) (class is abstract - execute() function is pure virtual)
- [x] [#14][i14] Make Semicolon class header file (semicolon.h) — this class inherits from the Connector class
- [x] [#15][i15] Implement execute() function in semicolon.cpp file
- [x] [#16][i16] Unit test the execute() function of the Semicolon class
- [x] [#17][i17] Make And class header file (and.h) — this class inherits from the Connector class
- [x] [#18][i18] Implement execute() function in add.cpp file
- [x] [#19][i19] Unit test the execute() function of the Add class
- [x] [#20][i20] Make Or class header file (or.h) — this class inherits from the Connector class
- [x] [#21][i21] Implement execute() function in or.cpp file
- [x] [#22][i22] Unit test the execute() function of the Or class
- [x] [#23][i23] Create and implement single_command_tests.sh to test for command executions
- [x] [#24][i24] Create and implement multiple_commands_tests.sh to test for command executions
- [x] [#25][i25] Create and implement commented_command_tests.sh to test for commented out commands
- [x] [#26][i26] Create and implement exit_command_tests.sh to test for proper exit functionality


[i1]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/1
[i2]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/2
[i3]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/3
[i4]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/4
[i5]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/5
[i6]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/6
[i7]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/7
[i8]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/8
[i9]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/9
[i10]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/10
[i11]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/11
[i12]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/12
[i13]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/13
[i14]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/14
[i15]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/15
[i16]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/16
[i17]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/17
[i18]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/18
[i19]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/19
[i20]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/20
[i21]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/21
[i22]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/22
[i23]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/23
[i24]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/24
[i25]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/25
[i26]: https://github.com/cs100/spring-2019-assignment-cs100_ja_assn1/issues/26
