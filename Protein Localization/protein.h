#include <vector>
#include <iostream>
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

unsigned short translate(std::string resultName);
std::vector<double> translateNN(std::string resultName);
std::string de_translate(unsigned short res);

void runKNN();
void runC45();
void runNeuralNetwork();

void readTrainFile(std::vector<Protein> *train, std::vector<Protein> *test);
bool compareDistance(const Protein &lhs, const Protein &rhs);
unsigned short k_nearest(std::vector<Protein> &proteins, int k, Protein &p);
void k_nearest_evaluate(std::vector<Protein> &train, std::vector<Protein> &test);
void displayMenu();
void showStats(unsigned short correctPred[], unsigned short sumReal[], unsigned short sumPred[], unsigned short test);
