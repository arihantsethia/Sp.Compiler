#ifndef Identifier_H
#define Identifier_H

class Identifier {
public:
    Identifier();
    Identifier(char *,int,int);
    int getValue();
    int updateValue(int);
    int getScope();
    virtual ~Identifier();
protected:
private:
    char *name;
    int value;
    int scope;
};

#endif // Identifier_H
