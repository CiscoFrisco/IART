#include "protein.h"
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

/**
 * Compares distance from two Proteins
 **/
bool compareDistance(const Protein &lhs, const Protein &rhs)
{
	return (lhs.distance < rhs.distance);
}

/**
 * K-Nearest neighbor algorithm, adapted to our problem
 **/
unsigned short k_nearest(vector<Protein> &proteins, int k, Protein &p)
{
	for (int i = 0; i < proteins.size(); ++i)
		proteins[i].calculateDistance(p);

	sort(proteins.begin(), proteins.end(), compareDistance);

	//CYT, NUC, MIT, ME3, ME2, ME1, EXC, VAC, POX, ERL
	unsigned short frequency[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	if (k > proteins.size())
		k = proteins.size();

	for (int i = 0; i < k; ++i)
		++frequency[proteins[i].result];

	return max_element(frequency, frequency + 10) - frequency;
}

/**
 * Test and evalutes k-nearest neighbor algorithm performance
 **/
void k_nearest_evaluate(vector<Protein> &train, vector<Protein> &test)
{

	unsigned short correct = 0;

	unsigned short correctPred[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	unsigned short sumReal[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	unsigned short sumPred[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	unsigned short res;
	unsigned short k;

	cout << "Choose K: ";

	cin >> k;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	for (int i = 0; i < test.size(); ++i)
	{
		res = k_nearest(train, k, test[i]);

		++sumReal[test[i].result];
		++sumPred[res];

		if (test[i].result == res)
		{
			++correctPred[res];
			++correct;
		}

		//cout << "Predicted: " << test[i].de_translate(res) << " Real: " << test[i].de_translate(test[i].result) << " Positives: " << correct << endl;
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2 - t1).count();

	cout << "\nDuration: " << (float)duration / 1000000 << " seconds.\n";

	cout << "Accuracy: " << ((float)correct / test.size()) * 100.0 << "%\n\n";

	showStats(correctPred, sumReal, sumPred, test.size());

	cout << endl;
}