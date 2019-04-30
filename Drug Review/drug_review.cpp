#include <set>
#include <fstream>
#include <iostream>

#include "drug.h"

using namespace std;

set<Condition> conditions;
set<Drug> drugs;

bool iequals(const string& a, const string& b)
{
    unsigned int sz = a.size();
    if (b.size() != sz)
        return false;
    for (unsigned int i = 0; i < sz; ++i)
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    return true;
}

string trim(const string& str, const string& whitespace = " \t")
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

string reduce(const string& str, const string& fill = " ", const string& whitespace = " \t")
{
    // trim first
    auto result = trim(str, whitespace);

    // replace sub ranges
    auto beginSpace = result.find_first_of(whitespace);
    while (beginSpace != string::npos)
    {
        const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
        const auto range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        const auto newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }

    return result;
}

void readTrainFile(){
    ifstream file("drugsComTrain_raw.tsv");

    string temp;

    getline(file,temp); //Ignore header line

    while(!file.eof())
	{
        getline(file,temp,'\t');

        getline(file,temp,'\t');

		int pos = 0;
		string token;

		while ((pos = temp.find("/")) != string::npos) {
			token = temp.substr(0, pos);
			Drug drug;
			drug.name = reduce(token);
			drugs.insert(drug);
			temp.erase(0, pos + 1);
		}

		Drug drug;
		drug.name = reduce(temp);
		drugs.insert(drug);

		getline(file,temp,'\t');

		pos = 0;

		while ((pos = temp.find("/")) != string::npos) 
		{
			token = temp.substr(0, pos);
			Condition condition;
			condition.name = reduce(token);
			conditions.insert(condition);
			temp.erase(0, pos + 1);
		}

		Condition condition;
		condition.name = reduce(temp);
		conditions.insert(condition);

		getline(file,temp,'"');
		file.ignore();
		file.ignore();
		getline(file,temp,'"');
		file.ignore();
		file.ignore();
		getline(file,temp);
    }

	cout << "Drugs: " << drugs.size() << "\nConditions: " << conditions.size() << endl;

	cout << "\n\n=====Drugs=====\n";

	set<Drug>::iterator itDrugs = drugs.begin();
	for(; itDrugs != drugs.end(); ++itDrugs)
		cout << itDrugs->name << endl;

	cout << "\n\n=====Conditions=====\n";

	set<Condition>::iterator itConditions = conditions.begin();
	for(; itConditions != conditions.end(); ++itConditions)
		cout << itConditions->name << endl;
}


int main() {
    readTrainFile();

    return 0;
}