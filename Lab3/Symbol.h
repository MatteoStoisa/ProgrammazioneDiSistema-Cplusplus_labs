#ifndef LAB3_SYMBOL_H
#define LAB3_SYMBOL_H

#include <vector>

class Symbol {
private:

public:
    char symbol;
    int symbolSourceId;
    int symbolSourceCounter;
    std::vector<int> positionCRDT;
};


#endif
