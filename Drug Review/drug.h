#include <string>
#include <ctime>

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
    Drug drug;
    Condition condition;
    std::string review;
    int rating;
    tm date;
    int usefulCount;
};