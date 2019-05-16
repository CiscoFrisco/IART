#include "protein.h"

using namespace std;

vector<Protein> train;
vector<Protein> test;

int main() {
    readTrainFile(&train, &test);

    cout << "=====Protein Localization=====\n\n";

	cout << "TRAIN: " << train.size() << " | " << "TEST: " << test.size() << endl;

	cout << "K Nearest Neighbours\n";

	k_nearest_evaluate(train, test);

    return 0;
}