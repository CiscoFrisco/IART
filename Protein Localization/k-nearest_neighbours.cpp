#include "protein.h"
#include <vector>
#include <algorithm>

using namespace std;

bool compareDistance(const Protein &lhs, const Protein &rhs) 
{ 
	return (lhs.distance < rhs.distance); 
}

std::string de_translate(unsigned short res)
{ 
		switch(res) {
			case 0: return "CYT";
			case 1: return "NUC";
			case 2: return "MIT";
			case 3: return "ME3";
			case 4: return "ME2";
			case 5: return "ME1";
			case 6: return "EXC";
			case 7: return "VAC";
			case 8: return "POX";
			case 9: return "ERL";
		}

		return "";
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

	unsigned short correct = 0;

	unsigned short correctPred[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	unsigned short sumReal[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	unsigned short sumPred[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	unsigned short res;
	unsigned short k;

	cout << "Choose K: ";

	cin >> k;

	for(int i = 0; i < test.size(); ++i)
	{
		res = k_nearest(train,k,test[i]);

		++sumReal[test[i].result];
		++sumPred[res];

		if(test[i].result == res) {
			++correctPred[res];
			++correct;
		}

		//cout << "Predicted: " << test[i].de_translate(res) << " Real: " << test[i].de_translate(test[i].result) << " Positives: " << correct << endl;
	}

	cout << "Accuracy: " << ((float) correct / test.size()) * 100.0 << "%\n\n";

	for(int i = 0; i < 10; ++i) {
		int vp = correctPred[i];
		int fn = sumReal[i] - correctPred[i];
		int fp = sumPred[i] - correctPred[i];
		int vn = test.size() - sumReal[i] - sumPred[i] + correctPred[i];

		cout << "Class: " << de_translate(i);
		cout << " VP: " << vp << " FN: " << fn << " FP: " << fp << " VN: " << vn;
		cout << " Accuracy: " << (float) (vp + vn) / (vp + fn + fp + vn);
		cout << " Precision: " << (float) vp / (vp + fp);
		cout << " F-measure: " << (2.0 * vp) / ((2.0 * vp) + fn + fp);


		cout << endl; 
	}

	cout << endl;
}