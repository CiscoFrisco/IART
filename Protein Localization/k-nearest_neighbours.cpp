#include "protein.h"
#include <vector>
#include <algorithm>

using namespace std;

bool compareDistance(const Protein &lhs, const Protein &rhs) 
{ 
	return (lhs.distance < rhs.distance); 
}

unsigned short k_nearest(vector<Protein> &proteins, int k, Protein &p) 
{
	for(int i = 0; i < proteins.size(); ++i)
		proteins[i].calculateDistance(p);

	sort(proteins.begin(), proteins.end(), compareDistance);

	//CYT, NUC, MIT, ME3, ME2, ME1, EXC, VAC, POX, ERL
	unsigned short frequency[10] =  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	if(k > proteins.size())
		k = proteins.size();

	for(int i = 0; i < k; ++i)
		++frequency[proteins[i].result];

	return max_element(frequency,frequency+10) - frequency;
}

void k_nearest_evaluate(vector<Protein> &train, vector<Protein> &test) {

	unsigned short positives = 0;
	unsigned short res;
	unsigned short k;

	cout << "Choose K: ";

	cin >> k;

	for(int i = 0; i < test.size(); ++i)
	{
		res = k_nearest(train,k,test[i]);

		if(test[i].result == res)
			++positives;

		cout << "Predicted: " << test[i].de_translate(res) << " Real: " << test[i].de_translate(test[i].result) << " Positives: " << positives << endl;
	}

	cout << "Success: " << ((float) positives / test.size()) * 100.0 << "%\n"; 	
}