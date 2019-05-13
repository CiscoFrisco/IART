#include <string>
#include <ctime>
#include <set>
#include <fstream>
#include <iostream>

bool iequals(const std::string& a, const std::string& b);

struct Drug {
    std::string name;

    bool operator==(const Drug &other) const
	{
		return iequals(name,other.name);
	}

    bool operator<(const Drug &other) const
	{
		return name < other.name;
	}
};

struct Condition {
    std::string name;

    bool operator==(const Condition &other) const
	{
		return iequals(name,other.name);
	}

    bool operator<(const Condition &other) const
	{
		return name < other.name;
	}
};

struct DrugReview {
    int id;
    std::set<Drug> drugs;
    std::set<Condition> conditions;
    int review_size;
    float rating;
    int usefulCount;

    bool operator==(const DrugReview &other) const
	{
		return rating == other.rating;
	}

    bool operator<(const DrugReview &other) const
	{
		return rating < other.rating;
	}
};

bool iequals(const std::string& a, const std::string& b);

std::string trim(const std::string& str, const std::string& whitespace = " \t");

std::string reduce(const std::string& str, const std::string& fill = " ", const std::string& whitespace = " \t");

void readTrainFile();