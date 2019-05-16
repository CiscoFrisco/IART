#include <ctime>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
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
	unsigned short result;
	float distance;

	void calculateDistance(const Protein &p) 
	{ 
    	distance = sqrt(
			(mcg - p.mcg) * (mcg - p.mcg) +
			(gvh - p.gvh) * (gvh - p.gvh) +
			(alm - p.alm) * (alm - p.alm) +
			(mit - p.mit) * (mit - p.mit) +
			(erl - p.erl) * (erl - p.erl) +
			(pox - p.pox) * (pox - p.pox) +
			(vac - p.vac) * (vac - p.vac) +
			(nuc - p.nuc) * (nuc - p.nuc)
		);
	}

	void translate(std::string resultName) 
	{ 
		if (resultName == "CYT")
			result = 0;
		else if (resultName == "NUC")
			result = 1;
		else if (resultName == "MIT")
			result = 2;
		else if (resultName == "ME3")
			result = 3;
		else if (resultName == "ME2")
			result = 4;
		else if (resultName == "ME1")
			result = 5;
		else if (resultName == "EXC")
			result = 6;
		else if (resultName == "VAC")
			result = 7;
		else if (resultName == "POX")
			result = 8;
		else if (resultName == "ERL")
			result = 9;
	}

	static std::string de_translate(unsigned short res) 
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
};

void readTrainFile(std::vector<Protein> *train, std::vector<Protein> *test);
bool compareDistance(const Protein &lhs, const Protein &rhs);
unsigned short k_nearest(std::vector<Protein> &proteins, int k, Protein &p);
void k_nearest_evaluate(std::vector<Protein> &train, std::vector<Protein> &test);