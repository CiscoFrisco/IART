#include <ctime>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

struct Protein {

    unsigned short mcg;
    unsigned short gvh;
    unsigned short alm;
    unsigned short mit;
    unsigned short erl;
    unsigned short pox;
    unsigned short vac;
    unsigned short nuc;
    std::string result;
};

void readTrainFile(std::vector<Protein> *train, std::vector<Protein> *test);