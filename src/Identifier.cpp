#include "Identifier.h"

Identifier::Identifier() {
    //ctor
}

Identifier::Identifier(char *n, int val, int s) {
    *name = *n;
    value = val;
    scope = s;
}

int Identifier::getValue() {
    return value;
}

int Identifier::updateValue(int val) {
    value = val;
    return value;
}

int Identifier::getScope() {
    return scope;
}

Identifier::~Identifier() {
    //dtor
}
