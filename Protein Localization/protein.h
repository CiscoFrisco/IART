#include <ctime>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

struct Protein {

    unsigned short mcg;
    unsigned short gvh;
    unsigned short alm;
    unsigned short mit;
    unsigned short erl;
    unsigned short pox;
    unsigned short vac;
    std::string nuc;
};

void readTrainFile(std::vector<Protein> *vector);