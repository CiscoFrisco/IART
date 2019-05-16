#include "protein.h"
#include <vector>
#include <algorithm>

using namespace std;

bool compareDistance(const Protein &lhs, const Protein &rhs) 
{ 
	return (lhs.distance < rhs.distance); 
}

void k_nearest(vector<Protein> &proteins, int k, Protein &p) {
	for(int i = 0; i < proteins.size(); ++i)
		proteins[i].calculateDistance(p);

	sort(proteins.begin(), proteins.end(), compareDistance);

	//CYT, NUC, MIT, ME3, ME2, ME1, EXC, VAC, POX, ERL
	unsigned short frequency[10] =  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	if(k > proteins.size())
		k = proteins.size();

	for(int i = 0; i < k; ++i)
		frequency[proteins[i].result]++;

	p.result = max_element(frequency,frequency+10) - frequency;
}