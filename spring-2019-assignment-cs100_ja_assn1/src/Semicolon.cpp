#include "../header/Semicolon.hpp"


Semicolon::Semicolon(Base* userLeft, Base* userRight) {
        this->left = userLeft;
        this->right = userRight;
	this->parent = nullptr;
	this->classType = "Semicolon";
}

void Semicolon::execute() {
        this->setExecPassed(false);
        this->left->execute();

        this->right->execute();
        this->setExecPassed(this->right->getExecPassed());
}
