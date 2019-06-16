#include "gtest/gtest.h"
#include "../header/Base.hpp"
#include "../header/Command.hpp"
#include "../header/And.hpp"
#include "../header/Or.hpp"
#include "../header/Semicolon.hpp"
#include "../header/Paren.hpp"
#include <string>
#include <vector>
#include <cstring>
#include <queue>
#include "../src/HelperFunctions.cpp"
#include <iostream>
using namespace std;
//WRITE UNIT TESTS

TEST(BaseTest, Base){
    string output = "";
    vector<char*>v;
    Base* test1 = new Command();
    EXPECT_EQ(test1->getExecPassed(), true); // testing the base objects is constructed as exepected
    test1->setExecPassed(false);
    EXPECT_EQ(test1->getExecPassed(), false);// testing the setter function
  //=============================================================================================
    v  = {"echo", "hello", "world,","how are you?", "I hope ", "this works", nullptr};
    Base* test2 = new Command(v);
   // Base* test2 = new Command(input,7);
    EXPECT_EQ(test2->getExecPassed(), true); // testing the base objects is constructed as exepected
    testing::internal::CaptureStdout();
    test2->execute(); // this should execute successfully
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "hello world, how are you? I hope  this works\n");
    EXPECT_EQ(test2->getExecPassed(), true); //Check if execPassed is set to false

//===============================================================================================
     v = {"eh", "hi", nullptr};
     Base* test3 = new Command(v);
//     Base* test3 = new Command(input2, 3);
     testing::internal::CaptureStdout();
     test3->execute(); // this execution should fail 
     output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "");
     EXPECT_EQ(test3->getExecPassed(), false);
//===================================================================================================
     v  = {"mkdir", "src", nullptr};
     Base* test4 = new Command(v);
     testing::internal::CaptureStdout();
     test4->execute();
     output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output,"");
     EXPECT_EQ(test4->getExecPassed(), false);
}

TEST(TestCommand, Test){
//================================TESTING THE TEST COMMANDS=========================================================
     string output = "";
     vector<char*> v;
     v = {"test", "-e", "src/main.cpp", nullptr};
     Base* test5 = new Command(v);
     testing::internal::CaptureStdout();
     test5->execute();
     output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "(True)\n");
     EXPECT_EQ(test5->getExecPassed(), true);
	
     v = {"test", "-e", "src/noFile", nullptr};
     test5 = new Command(v);
     testing::internal::CaptureStdout();
     test5->execute();
     output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "(False)\n");
     EXPECT_EQ(test5->getExecPassed(), false);

     v = {"test", "-e", "src/", nullptr};
     test5 = new Command(v);
     testing::internal::CaptureStdout();
     test5->execute();
     output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "(True)\n");
     EXPECT_EQ(test5->getExecPassed(), true);

     v = {"test", "-e", "noDirec/", nullptr};
     test5 = new Command(v);
     testing::internal::CaptureStdout();
     test5->execute();
     output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "(False)\n");
     EXPECT_EQ(test5->getExecPassed(), false);

 
     v = {"test", "-f", "src/Command.cpp", nullptr};
     test5 = new Command(v);
     testing::internal::CaptureStdout();
     test5->execute();
     output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "(True)\n");
     EXPECT_EQ(test5->getExecPassed(), true);

     v = {"test", "-f", "src/", nullptr};
     test5 = new Command(v);
     testing::internal::CaptureStdout();
     test5->execute();
     output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "(False)\n");
     EXPECT_EQ(test5->getExecPassed(), false);

     v = {"test", "-f", "src/noFile", nullptr};
     test5 = new Command(v);
     testing::internal::CaptureStdout();
     test5->execute();
     output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "(False)\n");
     EXPECT_EQ(test5->getExecPassed(), false);

     v = {"test", "-f", "Nodirec/", nullptr};
     test5 = new Command(v);
     testing::internal::CaptureStdout();
     test5->execute();
     output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "(False)\n");
     EXPECT_EQ(test5->getExecPassed(), false);

     v = {"test", "-d", "header/", nullptr};
     test5 = new Command(v);
     testing::internal::CaptureStdout();
     test5->execute();
     output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "(True)\n");
     EXPECT_EQ(test5->getExecPassed(), true);

     v = {"test", "-d", "integration_tests/", nullptr};
     test5 = new Command(v);
     testing::internal::CaptureStdout();
     test5->execute();
     output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "(True)\n");
     EXPECT_EQ(test5->getExecPassed(), true);

     v = {"test", "-d", "noDic/", nullptr};
     test5 = new Command(v);
     testing::internal::CaptureStdout();
     test5->execute();
     output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "(False)\n");
     EXPECT_EQ(test5->getExecPassed(), false);

     v = {"test", "-d", "unit_tests/unit_test.cpp", nullptr};
     test5 = new Command(v);
     testing::internal::CaptureStdout();
     test5->execute();
     output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "(False)\n");
     EXPECT_EQ(test5->getExecPassed(), false);

     v = {"test", "-d", "integration_tests/noFile", nullptr};
     test5 = new Command(v);
     testing::internal::CaptureStdout();
     test5->execute();
     output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "(False)\n");
     EXPECT_EQ(test5->getExecPassed(), false);

     v = {"test", "src/main.cpp", nullptr};
     test5 = new Command(v);
     testing::internal::CaptureStdout();
     test5->execute();
     output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "(True)\n");
     EXPECT_EQ(test5->getExecPassed(), true);
	
     v = {"test", "integration_tests", nullptr};
     test5 = new Command(v);
     testing::internal::CaptureStdout();
     test5->execute();
     output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "(True)\n");
     EXPECT_EQ(test5->getExecPassed(), true);
    
     v = {"test", "integration_tests/multiple_commands_tests.sh", nullptr};
     test5 = new Command(v);
     testing::internal::CaptureStdout();
     test5->execute();
     output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "(True)\n");
     EXPECT_EQ(test5->getExecPassed(), true);


     v = {"test", "unit_tests/noFile.cpp", nullptr};
     test5 = new Command(v);
     testing::internal::CaptureStdout();
     test5->execute();
     output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "(False)\n");
     EXPECT_EQ(test5->getExecPassed(), false);

    v = {"test", "noDic/", nullptr};
     test5 = new Command(v);
     testing::internal::CaptureStdout();
     test5->execute();
     output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "(False)\n");
     EXPECT_EQ(test5->getExecPassed(), false);
}

TEST(CombinedTestCommands, TestCommands) {
    string output = "";
    vector<char*> input1 = {"test", "-e", "src/main.cpp", nullptr};  //testing two correct arguments;
    vector<char*> input2 = {"echo", "hi", nullptr};
    Base* command1 = new Command(input1);
    Base* command2 = new Command(input2);

    Base* And1 = new And(command1, command2);
    testing::internal::CaptureStdout();
    And1->execute(); // this should execute successfully
    output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "(True)\nhi\n");
    EXPECT_EQ(And1->getExecPassed(), true);

    vector<char*> input3 = {"test", "-f", "src/Command.cpp", nullptr};  //testing 1st is a correct argument;
    vector<char*> input4 = {"echo", "hi", nullptr};
    Base* command3 = new Command(input3);
    Base* command4 = new Command(input4);
    Base* And2 = new And(command3, command4);
    testing::internal::CaptureStdout();
    And2->execute(); // this should execute successfully
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(True)\nhi\n");
    EXPECT_EQ(And2->getExecPassed(), true);

    vector<char*> input5 = {"test", "-d",  "unit_tests/", nullptr};  //testing 2nd is a correct argument;
    vector<char*> input6 = {"echo", "hi", nullptr};
    Base* command5 = new Command(input5);
    Base* command6 = new Command(input6);
    Base* And3 = new And(command5, command6);
    testing::internal::CaptureStdout();
    And3->execute(); // this should execute successfully
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(True)\nhi\n");
    EXPECT_EQ(And3->getExecPassed(), true);

    Base* And4 = new And(And1, command2); //tree test
    testing::internal::CaptureStdout();
    And4->execute(); // this should execute successfully
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(True)\nhi\nhi\n");
    EXPECT_EQ(And4->getExecPassed(), true);

    vector<char*> input7 = {"test", "-e", "noDic/noFile", nullptr};  //testing two correct arguments;
    vector<char*> input8 = {"echo", "hi", nullptr};
    Base* command7 = new Command(input7);
    Base* command8 = new Command(input8);

    Base* Or1 = new Or(command7, command8);
    testing::internal::CaptureStdout();
    Or1->execute(); // this should execute successfully
    output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "(False)\nhi\n");
    EXPECT_EQ(Or1->getExecPassed(), true);

    vector<char*> input9 = {"test", "-f", "src/Nofile.cpp", nullptr};  //testing 1st is a correct argument;
    vector<char*> input10 = {"echo", "hi", nullptr};
    
    Base* command9 = new Command(input9);
    Base* command10 = new Command(input10);
    Base* Or2 = new Or(command9, command10);
    testing::internal::CaptureStdout();
    Or2->execute(); // this should execute successfully
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(False)\nhi\n");
    EXPECT_EQ(Or2->getExecPassed(), true);

    vector<char*> input11 = {"test", "-d", "src/main.cpp", nullptr };  //testing 2nd is a correct argument;
    vector<char*> input12 = {"echo", "hi", nullptr};

    Base* command11 = new Command(input11);
    Base* command12 = new Command(input12);
    Base* Or3 = new Or(command11, command12);
    testing::internal::CaptureStdout();
    Or3->execute(); // this should execute successfully
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(False)\nhi\n");
    	EXPECT_EQ(Or3->getExecPassed(), true);

    Base* Or4 = new Or(Or1, command8); //tree test
    testing::internal::CaptureStdout();
    Or4->execute(); // this should execute successfully
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(False)\nhi\n");
    EXPECT_EQ(Or4->getExecPassed(), true);
}
TEST(AndTest,And) {
    string output = "";
    vector<char*> input1 = {"echo", "hello", nullptr};  //testing two correct arguments;
    vector<char*> input2 = {"echo", "hi", nullptr};
    Base* command1 = new Command(input1);
    Base* command2 = new Command(input2);

    Base* And1 = new And(command1, command2);
    testing::internal::CaptureStdout();
    And1->execute(); // this should execute successfully
    output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "hello\nhi\n");
    EXPECT_EQ(And1->getExecPassed(), true);

    vector<char*> input3 = {"echo", "hello", nullptr};  //testing 1st is a correct argument;
    vector<char*> input4 = {"e", "hi", nullptr};
    Base* command3 = new Command(input3);
    Base* command4 = new Command(input4);
    Base* And2 = new And(command3, command4);
    testing::internal::CaptureStdout();
    And2->execute(); // this should execute successfully
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "hello\n");
    EXPECT_EQ(And2->getExecPassed(), false);

    vector<char*> input5 = {"e", "hello", nullptr};  //testing 2nd is a correct argument;
    vector<char*> input6 = {"echo", "hi", nullptr};
    Base* command5 = new Command(input5);
    Base* command6 = new Command(input6);
    Base* And3 = new And(command5, command6);
    testing::internal::CaptureStdout();
    And3->execute(); // this should execute successfully
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");
    EXPECT_EQ(And3->getExecPassed(), false);

    Base* And4 = new And(And1, command2); //tree test
    testing::internal::CaptureStdout();
    And4->execute(); // this should execute successfully
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "hello\nhi\nhi\n");
    EXPECT_EQ(And4->getExecPassed(), true);
}

TEST(OrTest, Or) {
    string output = "";
    vector<char*> input1 = {"echo", "hello", nullptr};  //testing two correct arguments;
    vector<char*> input2 = {"echo", "hi", nullptr};
    Base* command1 = new Command(input1);
    Base* command2 = new Command(input2);

    Base* Or1 = new Or(command1, command2);
    testing::internal::CaptureStdout();
    Or1->execute(); // this should execute successfully
    output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "hello\n");
    EXPECT_EQ(Or1->getExecPassed(), true);

    vector<char*> input3 = {"echo", "hello", nullptr};  //testing 1st is a correct argument;
    vector<char*> input4 = {"e", "hi", nullptr};
    
    Base* command3 = new Command(input3);
    Base* command4 = new Command(input4);
    Base* Or2 = new Or(command3, command4);
    testing::internal::CaptureStdout();
    Or2->execute(); // this should execute successfully
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "hello\n");
    EXPECT_EQ(Or2->getExecPassed(), true);

    vector<char*> input5 = {"e", "hello", nullptr};  //testing 2nd is a correct argument;
    vector<char*> input6 = {"echo", "hi", nullptr};
    Base* command5 = new Command(input5);
    Base* command6 = new Command(input6);
    Base* Or3 = new Or(command5, command6);
    testing::internal::CaptureStdout();
    Or3->execute(); // this should execute successfully
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "hi\n");
    EXPECT_EQ(Or3->getExecPassed(), true);

    Base* Or4 = new Or(Or1, command2); //tree test
    testing::internal::CaptureStdout();
    Or4->execute(); // this should execute successfully
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "hello\n");
    EXPECT_EQ(Or4->getExecPassed(), true);
}

TEST(SemicolonTest, Semicolon) {
    string output = "";
    vector<char*> input1 = {"echo", "hello", nullptr};  //testing two correct arguments;
    vector<char*> input2 = {"echo", "hi", nullptr};
    Base* command1 = new Command(input1);
    Base* command2 = new Command(input2);

    Base* Semicolon1 = new Semicolon(command1, command2);
    testing::internal::CaptureStdout();
    Semicolon1->execute(); // this should execute successfully
    output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "hello\nhi\n");
    EXPECT_EQ(Semicolon1->getExecPassed(), true);

    vector<char*> input3 = {"echo", "hello", nullptr};  //testing 1st is a correct argument;
    vector<char*> input4 = {"e", "hi", nullptr};
    Base* command3 = new Command(input3);
    Base* command4 = new Command(input4);
    Base* Semicolon2 = new Semicolon(command3, command4);
    testing::internal::CaptureStdout();
    Semicolon2->execute(); // this should execute successfully
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "hello\n");
    EXPECT_EQ(Semicolon2->getExecPassed(), false);

    vector<char*> input5 = {"e", "hello", nullptr};  //testing 2nd is a correct argument;
    vector<char*> input6 = {"echo", "hi", nullptr};
    Base* command5 = new Command(input5);
    Base* command6 = new Command(input6);
    Base* Semicolon3 = new Semicolon(command5, command6);
    testing::internal::CaptureStdout();
    Semicolon3->execute(); // this should execute successfully
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "hi\n");
    EXPECT_EQ(Semicolon3->getExecPassed(), true);

    Base* Semicolon4 = new Semicolon(Semicolon1, command2); //tree test
    testing::internal::CaptureStdout();
    Semicolon4->execute(); // this should execute successfully
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "hello\nhi\nhi\n");
    EXPECT_EQ(Semicolon4->getExecPassed(), true);
}


//**************Test for makeObject(), a helper in main that creates the object returned************
TEST(makeObjectTest, makeObject) {
	string output;
	
	//test 1	
	queue<vector<char*> > q;
	vector<char*> first = {"echo", "hi", nullptr};
	vector<char*> connector = {"||", nullptr};
	vector<char*> second = {"echo", "bye", nullptr};	
	q.push(first);
	q.push(connector);
	q.push(second);

	testing::internal::CaptureStdout();
    	makeObject(q)->execute(); // this should execute successfully
    	output = testing::internal::GetCapturedStdout();
    	EXPECT_EQ(output, "hi\n");

	//test 2
	queue<vector<char*> > q2;
        first = {"echo", "whoa", nullptr};
        connector = {"&&", nullptr};
        second = {"echo", nullptr};
        q2.push(first);
        q2.push(connector);
        q2.push(second);

        testing::internal::CaptureStdout();
        makeObject(q2)->execute(); // this should execute successfully
        output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "whoa\n\n");
    
	//test 3
	queue<vector<char*> > q3;
        first = {"echo", "hello", "world", nullptr};
	q3.push(first);
        connector = {"&&", nullptr};
	q3.push(connector);
        second = {"echo", nullptr};
	q3.push(second);
        connector = {"||", nullptr};
        q3.push(connector);
	second = {"echo" , nullptr};
        q3.push(second);

	testing::internal::CaptureStdout();
        makeObject(q3)->execute(); // this should execute successfully
        output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "hello world\n\n");

	//test 4
	queue<vector<char*> > q4;
	vector<char*> openParen = { "(", nullptr};
	vector<char*> closedParen = { ")", nullptr};
	q4.push(openParen);
        first = {"echo", "A", nullptr};
        q4.push(first);
        connector = {"&&", nullptr};
        q4.push(connector);
        second = {"echo", "B",  nullptr};
        q4.push(second);
	q4.push(closedParen); 
        connector = {"||", nullptr};
        q4.push(connector);
	q4.push(openParen);
        second = {"echo", "C" , nullptr};
        q4.push(second);
	connector = {"&&", nullptr};
        q4.push(connector);
	second = {"echo", "D" , nullptr};
        q4.push(second);
	q4.push(closedParen);


        testing::internal::CaptureStdout();
        makeObject(q4)->execute(); // this should execute successfully
        output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "A\nB\n");

	//test 5
	queue <vector<char*> > q5;
        first = {"echo", "A", nullptr};
        q5.push(first);
        connector = {"&&", nullptr};
        q5.push(connector);
	q5.push(openParen);
	q5.push(openParen);
        second = {"echo", "B",  nullptr};
        q5.push(second);
        q5.push(closedParen);
        connector = {"||", nullptr};
        q5.push(connector);
        q5.push(openParen);
        second = {"echo", "C" , nullptr};
        q5.push(second);
        connector = {"&&", nullptr};
        q5.push(connector);
        second = {"echo", "D" , nullptr};
        q5.push(second);
        q5.push(closedParen);
	q5.push(closedParen);

        testing::internal::CaptureStdout();
        makeObject(q5)->execute(); // this should execute successfully
        output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "A\nB\n");	
}

TEST(makeParenTempQueueTest, makeParenTempQueue) {
    string output;
    vector<char*> input;
    vector<char*> openP = {"(", nullptr};
    vector<char*> closeP = {")", nullptr};
    vector<char*> And = {"&&", nullptr};
    vector<char*> Or = {"||", nullptr};
    vector<char*> SemiColon = {";", nullptr};
    queue<vector<char*> > tempQueue;


    //test 1
    queue <vector<char*> > q1;
    q1.push(openP);
    input = {"echo", "A", nullptr};
    q1.push(input);
    q1.push(And);
    input = {"echo", "B",  nullptr};
    q1.push(input);
    q1.push(closeP);
    q1.pop(); 

    testing::internal::CaptureStdout();
    tempQueue = makeParenTempQueue(q1);
    makeObject(tempQueue)->execute();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "A\nB\n");

    //test 2
    queue <vector<char*> > q2;
    q2.push(openP);
    input = {"echo", "A", nullptr};
    q2.push(input);
    q2.push(closeP);
    q2.push(And);
    input = {"echo", "B",  nullptr};
    q2.push(input);
    q2.pop(); 

    
    testing::internal::CaptureStdout();
    tempQueue = makeParenTempQueue(q2);
    makeObject(tempQueue)->execute();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "A\n");

    //test 3
    queue <vector<char*> > q3;
    q3.push(openP);
    input = {"echo", "A", nullptr};
    q3.push(input);
    q3.push(And);
    q3.push(openP);
    input = {"echo", "B",  nullptr};
    q3.push(input);
    input = {"echo", "C",  nullptr};
    q3.push(input);
    q3.push(closeP);
    q3.push(closeP);
    q3.pop(); 

    testing::internal::CaptureStdout();
    tempQueue = makeParenTempQueue(q3);
    makeObject(tempQueue)->execute();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "A\nB\n");
}




TEST(ParseHelpersTest, ParseHelpers){
    string s = "";
    vector<string>v;
    unsigned int i = 0;
    unsigned int counter = 0;
    unsigned int pos = 0;
    ////CheckForWhiteSpaceAtEnd helper
    s = "test1 ";
    CheckForWhiteSpaceAtEnd(s);
    EXPECT_EQ(s, "test1 ");
    s = "test";
    CheckForWhiteSpaceAtEnd(s);
    EXPECT_EQ(s, "test\n");
     
    //nextQMark helper
    s = "";
    EXPECT_EQ(nextQMark(s, 0), false);
    s = "\"hello world\"";
    EXPECT_EQ(nextQMark(s, 1), true);
    s = "\"hi\" and \"bye\"";
    EXPECT_EQ(nextQMark(s, 1), true);
    s = "\"bye";
    EXPECT_EQ(nextQMark(s, 1), false);
  
    //dealWithQMark
    s = "\"hello world\"";
    i = 0;
    counter = 0;
    dealWithQMark(s, i, counter);
    EXPECT_EQ(i, 12);
    EXPECT_EQ(counter, 12);
    
    s = "\"hello";
    i = 0;
    counter = 0;
    dealWithQMark(s, i, counter);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(counter, 0);
	 
    //getRidOfQMarks helper
    s = "\"\"";
    getRidOfQMarks(s);
    EXPECT_EQ(s, "");
    s = "\"h\"";
    getRidOfQMarks(s);
    EXPECT_EQ(s, "h");
    s = "\"hi\"";
    getRidOfQMarks(s);
    EXPECT_EQ(s, "hi");
    s = "\"hellooooooooooooooooooo woooooooooooooooorld\"";
    getRidOfQMarks(s);
    EXPECT_EQ(s, "hellooooooooooooooooooo woooooooooooooooorld");

    //isNumberOfParenthesesEven
    s = "(echo world && (echo hi && (echo bye && mkdir test))) && (ls -a)"; 
    EXPECT_EQ(isNumberOfParenthesesEven(s), true);
    s = "(((((((((ech hi)";
    EXPECT_EQ(isNumberOfParenthesesEven(s), false);
    s = "(echo world) && (echo hi && (ls -a)";
    EXPECT_EQ(isNumberOfParenthesesEven(s), false);
    s = "(((((((((((((((((mkdir test)))))))))))))))))";
    EXPECT_EQ(isNumberOfParenthesesEven(s), true);
    s = "(((echo hi && echo world)); ((ls && echo world && (mkdir test || echo hi); (echo lol && exit))))";
    EXPECT_EQ(isNumberOfParenthesesEven(s), true);
    s = "echo \"(())))\"";
    EXPECT_EQ(isNumberOfParenthesesEven(s), true);
    s = "((echo hi && echo \"(())))))\") && (echo world && ls))"; 
    EXPECT_EQ(isNumberOfParenthesesEven(s), true);
    s = "(mkdir test && ls) #((()))))))))";
    EXPECT_EQ(isNumberOfParenthesesEven(s), true);
    s = "((mkdir test && ls) #)";
    EXPECT_EQ(isNumberOfParenthesesEven(s), false);
}

TEST(setParentTest, setParent) { 

string output = "";
vector<char*> input1 = {"echo", "hello", nullptr};  //testing two correct arguments;
vector<char*> input2 = {"echo", "hi", nullptr};
Base* command1 = new Command(input1);
Base* command2 = new Command(input2);
Base* And1 = new And(command1, command2);
command1->setParent(And1);

testing::internal::CaptureStdout();
command1->getParent()->execute(); // this should execute successfully
output = testing::internal::GetCapturedStdout();
EXPECT_EQ(output, "hello\nhi\n");
EXPECT_EQ(command1->getParent()->getExecPassed(), true);

EXPECT_EQ(command2->getParent(), nullptr);
}


TEST(getFileNameTest, getFileName){
    string output = "";
    vector<char*>v;
    Base* test1 = new Command();
    EXPECT_EQ(test1->getExecPassed(), true); 
    test1->setExecPassed(false);
    EXPECT_EQ(test1->getExecPassed(), false);
 

    v  = {"echo", "hello", "world,","how are you?", "I hope ", "this works", nullptr};
    Base* test2 = new Command(v);
    EXPECT_EQ(test2->getFileName(), "echo");
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
