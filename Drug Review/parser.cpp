#include "drug.h"

using namespace std;

set<DrugReview> reviews;
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

string trim(const string& str, const string& whitespace)
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

string reduce(const string& str, const string& fill, const string& whitespace)
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

	set<Drug> review_drugs;
	set<Condition> review_conditions;
	
    while(!file.eof())
	{
		DrugReview review;

        getline(file,temp,'\t');
        getline(file,temp,'\t');

		int pos = 0;
		string token;

		while ((pos = temp.find("/")) != string::npos) {
			token = temp.substr(0, pos);
			Drug drug;
			drug.name = reduce(token);
			review_drugs.insert(drug);
			drugs.insert(drug);
			temp.erase(0, pos + 1);
		}

		Drug drug;
		drug.name = reduce(temp);
		review_drugs.insert(drug);
		drugs.insert(drug);

		review.drugs = review_drugs;

		getline(file,temp,'\t');

		pos = 0;

		while ((pos = temp.find("/")) != string::npos) 
		{
			token = temp.substr(0, pos);
			Condition condition;
			condition.name = reduce(token);
			review_conditions.insert(condition);
			conditions.insert(condition);
			temp.erase(0, pos + 1);
		}

		Condition condition;
		condition.name = reduce(temp);
		review_conditions.insert(condition);
		conditions.insert(condition);

		review.conditions = review_conditions;

		getline(file,temp,'"');
		file.ignore();
		file.ignore();
		getline(file,temp,'"');
		review.review_size = temp.size();
		file.ignore();
		file.ignore();
		file.ignore();
		getline(file,temp, '\t');
		// review.rating = stoi(temp);
		getline(file,temp, '\t');
		getline(file,temp, '\n');
		review.usefulCount = stoi(temp);		
		
		reviews.insert(review);
		
		review_drugs.clear();
		review_conditions.clear();
    }

	cout << "Drugs: " << drugs.size() << "\nConditions: " << conditions.size() << endl;

	// cout << "\n\n=====Drugs=====\n";

	// set<Drug>::iterator itDrugs = drugs.begin();
	// for(; itDrugs != drugs.end(); ++itDrugs)
	// 	cout << itDrugs->name << endl;

	// cout << "\n\n=====Conditions=====\n";

	// set<Condition>::iterator itConditions = conditions.begin();
	// for(; itConditions != conditions.end(); ++itConditions)
	// 	cout << itConditions->name << endl;

	cout << "\n\n=====Drug Review=====\n";

	set<DrugReview>::iterator itReviews = reviews.begin();
	for(; itReviews != reviews.end(); ++itReviews){
		cout << "::::::::DRUG REVIEW::::::::" << endl;
		set<Drug>::iterator itDrugs = itReviews->drugs.begin();
		cout << "Drugs:" << endl;
		for(; itDrugs != itReviews->drugs.end(); ++itDrugs)
			cout <<"- " << itDrugs->name << endl;

		set<Condition>::iterator itConditions = itReviews->conditions.begin();
		cout << "Condition:" << endl;
		for(; itConditions != itReviews->conditions.end(); ++itConditions)
			cout << "- " << itConditions->name << endl;

		cout << "Rating: " << itReviews->rating <<endl;

		cout << "UsefulCount: " << itReviews->usefulCount <<endl;
	}
}