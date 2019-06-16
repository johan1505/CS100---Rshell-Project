#include "../header/And.hpp"

//And::And() {
//        this->left = 0;
//        this->right = 0;
//}

And::And(Base* userLeft, Base* userRight) {
        this->left = userLeft;
        this->right = userRight;
	this->parent = nullptr;
	this->classType = "And";
}

//And::And(Base* userLeft) {
//        this->left = userLeft;
//        this->right = 0;
//}

void And::execute() {
        this->setExecPassed(false);
        this->left->execute();

        if (this->left->getExecPassed()) {
                this->right->execute();
                this->setExecPassed(this->right->getExecPassed());
        }
}
