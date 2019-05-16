#include "protein.h"

using namespace std;

void readTrainFile(vector<Protein> *train, vector<Protein> *test){
    
    ifstream file("yeast.data");
    srand (time(NULL));

	float trainPercentage;

	cout << "Train data Percentage: ";
	cin >> trainPercentage;
	
    float mcg, gvh, alm,  mit, erl, pox, vac, nuc;
    string ignore, line;

    Protein protein;
	string result;

    while(getline(file, line))
	{   
        stringstream protein_line(line);

        protein_line >> ignore >> mcg >> gvh >> alm >> mit >> erl >> pox >> vac >> nuc >> result;

		protein.translate(result);
        protein.mcg = mcg*100;
        protein.gvh = gvh*100;
        protein.alm = alm*100;
        protein.mit = mit*100;
        protein.erl = erl*100;
        protein.pox = pox*100;
        protein.vac = vac*100;

        int random = rand() % 100;

        if(random < (100 - (int) trainPercentage))
            (*test).push_back(protein);
        else
            (*train).push_back(protein);        
    }
}