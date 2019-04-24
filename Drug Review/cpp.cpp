#include <set>
#include <ifstream>

#include "drug.h"

using namespace std;

set<Condition> conditions;
set<Drug> drugs;

void readTrainFile(){
    istream file("drugsComTrain_raw.tsv");

    string temp;

    getline(file,temp); //Ignore header line

    while(!file.eof()){
        getline(file,temp,' ');
        cout << temp << endl;
    }
}


int main() {
    readTrainFile();

    return 0;
}