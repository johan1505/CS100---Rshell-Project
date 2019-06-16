#include <iostream>
#include <string>
#include "../header/Base.hpp"
#include <cstring>
#include <queue>
#include <vector>
#include "../header/Command.hpp"
#include "../header/And.hpp"
#include "../header/Or.hpp"
#include "../header/Semicolon.hpp"
#include "../header/Paren.hpp"
#include "../header/OutputReClear.hpp"
#include "../header/OutputReApp.hpp"
#include "../header/InputRe.hpp"
#include "../header/Pipe.hpp"
#include <list>
#include "HelperFunctions.cpp"
using namespace std;

Base* parseInput(string &userInput);

int main(){
    string userInput;
    Base* root;
    while(1){
        cout << "$ ";
        getline(cin, userInput); // getline extracts characters until it finds a newline
        if (isNumberOfParenthesesEven(userInput)){
                root = parseInput(userInput);
                if (root){
            root->execute();
            }
        }
        else {
            cout << "Uneven number of parentheses, please enter your command again" << endl;
        }
    }
    return 0;
}

Base* parseInput(string &s){
    vector <string> v;
    unsigned i = 0;
    unsigned pos = 0;
    unsigned counter = 0;
    int possibleHashTagPos = 0;
    string substring = "";
    vector<char*>temp;
    queue <vector<char*> > q;
    
    if (s.length() > 0){   // If the input is greater then 0 then parse it
        CheckForWhiteSpaceAtEnd(s);
        //Parsing begins
        while (i < s.length()){
            while (s.at(i) != ' ' && s.at(i) != '\n'){
		        if (s.at(i) == '['){
                    v.push_back("test");
                    break;
                }
                else if (s.at(i) == ']'){ // if a closing bracket is found then break and ignore it. Note at this position counter is 0 an pos = i
                    break;
                }
                else if (s.at(i) == '(' ){
                        counter++; //incease counter and break to push the parenthesis into the vector
                        break;
                }
                else if (s.at(i) == ')'){
                    if (s.at(i - 1) != ')'){ // If the char previous was not a closing parentheses then push it to the vector, point pos to i, and set counter to 1
                        substring = s.substr(pos, counter); //so that the current closing parentheses gets stored in the vector
                        if (substring.length() > 0){  //If the subtring is empty then don't push it to the vector
                            v.push_back(s.substr(pos, counter));
                        }
                        pos = i;
                        counter = 1;
                        break;
                    }
                    else {
                        counter++;
                        break;
                    }
                }
                else if (s.at(i) == '\"'){	
                    dealWithQMark(s,i,counter);
                }
		        else if (s.at(i) == '#'){  //if a hashtag is found then do not analyze the string anymore
		            i = s.length();	
                    break;
                }
                else if(s.at(i) == ';'){
                    dealWithSemicolon(s,v,pos,counter,i);
                }
                i++;
                counter++;
		        if (i >= s.length()){
                    break;
                }
            }
	        substring = s.substr(pos, counter);
            if (substring.length() > 0){
                v.push_back(substring);
		        //cout << "substring was pushed to vector" << endl;
            }
            counter = 0;
            i++;
            if (i < s.length()){
                while (s.at(i) == ' '){
                    i++;
                    if (i >= s.length()){
                        break;
                    }
                }
            }
            pos = i;
        }
		//USE THIS LOOP TO TEST THE CONTENTS OF THE VECTOR OF STRINGS
	  //  cout << "Outputing the contents of v" << endl;
          //  for (i = 0; i < v.size(); i++){
          //      cout << "Element at pos. " << i << ": " << v.at(i) << endl;
          ///  }
        //Parsing ends
        //Making of the queue begins
	//cout << "Making of the queue begins" << endl;
        i = 0;
	    while (i < v.size()){
		    if (v.at(i) == "(" || v.at(i) == ")" || v.at(i) == "&&" || v.at(i) == "||" || v.at(i) == ";" || v.at(i) == "<" || v.at(i) == ">" || v.at(i) == ">>" || v.at(i) == "|"){
			    temp.push_back(strcpy(new char[v.at(i).length() + 1], v.at(i).c_str()));
			    q.push(temp);
			    temp.resize(0);
			    i++;
		    }
		    else {
			    while (v.at(i) != "||" && v.at(i) != "&&" && v.at(i) != ";" && v.at(i) != "(" && v.at(i) != ")" && v.at(i) != "<" && v.at(i) != ">" && v.at(i) != ">>" && v.at(i) != "|"){
				    if (v.at(i).at(0) == '\"' && v.at(i).at(v.at(i).length() - 1) == '\"'){
		                    getRidOfQMarks(v.at(i));
               		}
                   	temp.push_back(strcpy(new char[v.at(i).length() + 1], v.at(i).c_str()));
                    i++;
                	if (i >= v.size()){
                 		break;
            		}
			    }
			    temp.push_back(nullptr);
			    q.push(temp);
			    temp.resize(0);
		    }
	    }
	//USE THIS CODE TO TEST THE CONTENT OF QUEUE
	/*
	cout << "Making queue ends" << endl;
        cout << "Size of queue: " << q.size() << endl << endl;
  
       cout << "Testing the output of the queue" << endl << endl;
       unsigned int j = 0;
       while (q.size() > 0){
           i = 0;
           cout << "Vector at pos " << j << "( size: " << q.front().size() << " )" << endl;
           cout << "s" << i << ": " << q.front().at(i);
           for (i = 1; i < q.front().size() - 1; ++i){
               cout << " " << "s" << i << ": " << q.front().at(i);
           }
           cout << endl;
           q.pop();
           j++;
       }
	*/

        //Making queue ends
    	return makeObject(q);
    }
    return nullptr;
}
