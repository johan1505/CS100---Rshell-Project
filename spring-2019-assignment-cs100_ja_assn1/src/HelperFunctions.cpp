#include "../header/OutputReClear.hpp"
#include "../header/OutputReApp.hpp"
#include "../header/InputRe.hpp"
#include "../header/Pipe.hpp"

void CheckForWhiteSpaceAtEnd(string &s);
bool nextQMark(const string &s, unsigned int i);
void dealWithSemicolon(const string &s, vector<string> &v, unsigned int &pos, unsigned int &counter, unsigned int i);
void dealWithQMark(const string &s, unsigned int &i, unsigned int &counter);
void getRidOfQMarks(string& s);
bool isNumberOfParenthesesEven(const string& s); // Unit test this function
queue<vector<char*> > makeParenTempQueue (queue<vector<char*> >& q);
Base* makeObject(queue<vector<char*> > &q);

void CheckForWhiteSpaceAtEnd(string &s){
    if (s.at(s.length() - 1) != ' '){ // If the user input does not end with a whitespace then push an endl;
        s.push_back('\n');
    }
    return;
}

void dealWithQMark(const string &s, unsigned int &i, unsigned int &counter){
    bool isNextQMark;
    i++;
    isNextQMark = nextQMark(s,i);
    if (!isNextQMark){
      i--;
      return;
    }
     while(s.at(i) != '\"'){
          i++;
          counter++;
     }
    counter++;
    return;
}



bool nextQMark(const string &s, unsigned int i){
     for (unsigned int j = i; j < s.length(); j++){
          if (s.at(j) == '\"'){
               return true;
          }
     }
     return false;
}

void dealWithSemicolon(const string &s, vector<string> &v, unsigned int &pos, unsigned int &counter, unsigned int i){
    string substring = "";
    if (i > 0) { // If semicolon is not at pos 0 then
        if (s.at(i - 1) != ' '){   // if char before semicolon is not ' ' then
           	 substring = s.substr(pos, counter); // get the previous string
		 if (substring.length() > 0) {
           		 v.push_back(substring);             // push it to the vector
	        }
        }
    }
    pos = i;
    counter = 0;
    return;
}

void getRidOfQMarks(string& s){
    if (s.length() == 2){
        s = "";
        return;
    }
    s.pop_back();
    s = s.substr(1, s.length()-1);
}

queue<vector<char*> > makeParenTempQueue (queue<vector<char*> >& q) { 
	queue<vector<char*> > tempQueue;  
	vector<char*> vTemp;			
	bool foundMatchingParen = false;
	int countParen = 0;

	while (!foundMatchingParen && !q.empty()) { 
		vTemp = q.front();
		if(static_cast<string>(vTemp.at(0)) == "(") {
			++countParen;
			tempQueue.push(vTemp);
			q.pop();
		}
		else if (static_cast<string>(vTemp.at(0)) == ")" && countParen != 0) {
			--countParen;
			tempQueue.push(vTemp);
			q.pop();
		}
		else if (static_cast<string>(vTemp.at(0)) == ")" && countParen == 0) {
			foundMatchingParen = true;
		}
		else {
			tempQueue.push(vTemp);
			q.pop();
		}
	}

	return tempQueue;
}

Base* makeObject(queue<vector<char*> >& q) { 
    Base* root = nullptr;
    Base* left = nullptr;
    Base* right = nullptr;
    Base* temp = nullptr;
    vector<char*> vTemp;
    queue<vector<char*> > tempQueue; 



    while (q.size() != 0) {
        vTemp = q.front();
        q.pop();

        if (static_cast<string>(vTemp.at(0)) == "||") {
            if (q.size() > 0) {
                   vTemp = q.front();
                   q.pop();
                   if (static_cast<string>(vTemp.at(0)) == "(") {
                    	tempQueue = makeParenTempQueue(q);
                    	temp = makeObject(tempQueue);
			right = new Paren(temp);
                    }
                   else {
                    	right = new Command(vTemp);
                   }
            }
            root = new Or(left, right);
	    //left->setParent(root);
            //right->setParent(root);
            left = root;
            right = nullptr;
        }
        else if (static_cast<string>(vTemp.at(0)) == "&&") {
            if (q.size() > 0) {
                   vTemp = q.front();
                   q.pop();
                   if (static_cast<string>(vTemp.at(0)) == "(") {
                    	tempQueue = makeParenTempQueue(q);
                    	temp = makeObject(tempQueue);
			right = new Paren(temp);
                    }
                   else {
                    	right = new Command(vTemp);
                   }
            }
            root = new And(left, right);
	    //left->setParent(root);
	    //right->setParent(root);
            left = root;
            right = nullptr;
        }
        else if (static_cast<string>(vTemp.at(0)) == ";") {
            if (q.size() > 0) {
                   vTemp = q.front();
                   q.pop();
                   if (static_cast<string>(vTemp.at(0)) == "(") {
                    	tempQueue = makeParenTempQueue(q);
                    	temp = makeObject(tempQueue);
			right = new Paren(temp);
                    }
                   else {
                    	right = new Command(vTemp);
                   }
            }
            root = new Semicolon(left, right);
	    //left->setParent(root);
            //right->setParent(root);
            left = root;
            right = nullptr;
        }
	else if (static_cast<string>(vTemp.at(0)) == ">") {
            if (q.size() > 0) {
                   vTemp = q.front();
                   q.pop();
                   if (static_cast<string>(vTemp.at(0)) == "(") {
                        tempQueue = makeParenTempQueue(q);
                        temp = makeObject(tempQueue);
                        right = new Paren(temp);
                    }
                   else {
                        right = new Command(vTemp);
                   }
            }
            root = new OutputReClear(left, right);
            left = root;
            right = nullptr;
        }

	else if (static_cast<string>(vTemp.at(0)) == ">>") {
	     if (q.size() > 0) {
                   vTemp = q.front();
                   q.pop();
                   if (static_cast<string>(vTemp.at(0)) == "(") {
                        tempQueue = makeParenTempQueue(q);
                        temp = makeObject(tempQueue);
                        right = new Paren(temp);
                    }
                   else {
                        right = new Command(vTemp);
                   }
            }
            root = new OutputReApp(left, right);
            left = root;
            right = nullptr;
        }
	else if (static_cast<string>(vTemp.at(0)) == "<") {
            if (q.size() > 0) {
                   vTemp = q.front();
                   q.pop();
                   if (static_cast<string>(vTemp.at(0)) == "(") {
                        tempQueue = makeParenTempQueue(q);
                        temp = makeObject(tempQueue);
                        right = new Paren(temp);
                    }
                   else {
                        right = new Command(vTemp);
                   }
            }
            root = new InputRe(left, right);
            left = root;
            right = nullptr;
        }
	else if (static_cast<string>(vTemp.at(0)) == "|") {
             if (q.size() > 0) {
                   vTemp = q.front();
                   q.pop();
                   if (static_cast<string>(vTemp.at(0)) == "(") {
                        tempQueue = makeParenTempQueue(q);
                        temp = makeObject(tempQueue);
                        right = new Paren(temp);
                    }
                   else {
                        right = new Command(vTemp);
                   }
            }
            root = new Pipe(left, right);
            left = root;
            right = nullptr;
        }
        else if (static_cast<string>(vTemp.at(0)) == "(") { 
		tempQueue = makeParenTempQueue(q);	
    		if (left == nullptr) { 
    			temp = makeObject(tempQueue);
			left = new Paren(temp);
			 
    			
    			if (root == nullptr) {
    				root = left;
    			}
    		}
    		else { }
       
        }
        else {
            if (left == nullptr) {
                    left = new Command(vTemp);
            }
            if (root == nullptr) {
                    root = left;
            }
        }
    }


    return root;
}

bool isNumberOfParenthesesEven(const string& s){
	int counterLeftParenthesis = 0;
	int counterRightParenthesis = 0;
	for (unsigned i = 0; i < s.size(); i++){
        if (s.at(i) == '\"'){
            i++;
            if (i < s.size()){
                while (s.at(i) != '\"'){
                    if (i < s.size() - 1){
                        i++;
                    }
                    else {
                        break;
                    }
                }
            }
        }
		else if (s.at(i) == '('){
			++counterLeftParenthesis;
		}
		else if (s.at(i) == ')'){
			++counterRightParenthesis;
		}
		else if(s.at(i) == '#'){
		    break;
		}
	}
	return counterLeftParenthesis == counterRightParenthesis;
}
