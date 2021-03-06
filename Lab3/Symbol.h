#ifndef LAB3_SYMBOL_H
#define LAB3_SYMBOL_H

#include <vector>

class Symbol {
private:

public:
    Symbol(char,int,int,std::vector<int>);
    ~Symbol();

    char symbol;
    int symbolSourceId;
    int symbolSourceCounter;
    std::vector<int> positionCRDT;

    std::vector<int> getCRDTSymbol();
};


#endif
