#include "../header/Paren.hpp"

Paren::Paren(Base* userRight) {
        this->left = nullptr;
        this->right = userRight;
        this->parent = nullptr;
        this->classType = "Paren";
}

void Paren::execute() {
        this->right->execute();
        this->setExecPassed(this->right->getExecPassed());
}

