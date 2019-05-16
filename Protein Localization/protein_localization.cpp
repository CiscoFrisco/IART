#include "protein.h"

using namespace std;

vector<Protein> train;
vector<Protein> test;

int main() {
    readTrainFile(&train, &test);

    cout << "\n\n=====Protein Localization=====\n";

	// for(int i = 0; i < train.size(); i++){
	// 	cout << "::::::::PROTEIN LOCALIZATION::::::::" << endl;
	// 	cout << "MCG: " << train[i].mcg << endl;
	// 	cout << "GVH: " << train[i].gvh << endl;
	// 	cout << "ALM: " << train[i].alm << endl;
	// 	cout << "MIT: " << train[i].mit << endl;
	// 	cout << "ERL: " << train[i].erl << endl;
	// 	cout << "POX: " << train[i].pox << endl;
	// 	cout << "VAC: " << train[i].vac << endl;
	// 	cout << "NUC: " << train[i].nuc << endl;
	// }

	cout << "TRAIN: " << train.size() << " | " << "TEST: " << test.size() << endl;

    return 0;
}