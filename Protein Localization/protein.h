#include <ctime>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdlib>

struct Protein
{
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
			(nuc - p.nuc) * (nuc - p.nuc));
	}
};

unsigned short translate(std::string resultName)
{
	if (resultName == "CYT")
		return 0;
	else if (resultName == "NUC")
		return 1;
	else if (resultName == "MIT")
		return 2;
	else if (resultName == "ME3")
		return 3;
	else if (resultName == "ME2")
		return 4;
	else if (resultName == "ME1")
		return 5;
	else if (resultName == "EXC")
		return 6;
	else if (resultName == "VAC")
		return 7;
	else if (resultName == "POX")
		return 8;
	else if (resultName == "ERL")
		return 9;
}

double translateNN(std::string resultName)
{
	if (resultName == "CYT")
		return 0;
	else if (resultName == "NUC")
		return 0.1;
	else if (resultName == "MIT")
		return 0.2;
	else if (resultName == "ME3")
		return 0.3;
	else if (resultName == "ME2")
		return 0.4;
	else if (resultName == "ME1")
		return 0.5;
	else if (resultName == "EXC")
		return 0.6;
	else if (resultName == "VAC")
		return 0.7;
	else if (resultName == "POX")
		return 0.8;
	else if (resultName == "ERL")
		return 0.9;
}

std::string de_translate(unsigned short res)
{
	switch (res)
	{
	case 0:
		return "CYT";
	case 1:
		return "NUC";
	case 2:
		return "MIT";
	case 3:
		return "ME3";
	case 4:
		return "ME2";
	case 5:
		return "ME1";
	case 6:
		return "EXC";
	case 7:
		return "VAC";
	case 8:
		return "POX";
	case 9:
		return "ERL";
	}

	return "";
}

std::string de_translateNN(double res)
{
	if(res < 0.05)
		return "CYT";
	if(res < 0.15)
		return "NUC";
	if(res < 0.25)
		return "MIT";
	if(res < 0.35)
		return "ME3";
	if(res < 0.45)
		return "ME2";
	if(res < 0.55)
		return "ME1";
	if(res < 0.65)
		return "EXC";
	if(res < 0.75)
		return "VAC";
	if(res < 0.85)
		return "POX";

	return "ERL";
}

void readTrainFile(std::vector<Protein> *train, std::vector<Protein> *test);
bool compareDistance(const Protein &lhs, const Protein &rhs);
unsigned short k_nearest(std::vector<Protein> &proteins, int k, Protein &p);
void k_nearest_evaluate(std::vector<Protein> &train, std::vector<Protein> &test);
std::string de_translate(unsigned short res);