#include "../header/Or.hpp"


Or::Or(Base* userLeft, Base* userRight) {
        this->left = userLeft;
        this->right = userRight;
	this->parent = nullptr;
	this->classType = "Or";
}

void Or::execute() {
        this->setExecPassed(true);
        this->left->execute();

        if (!(this->left->getExecPassed())) {
                this->right->execute();
                this->setExecPassed(this->right->getExecPassed());
        }
}
