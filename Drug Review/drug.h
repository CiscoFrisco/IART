#include <string>
#include <ctime>

struct Drug {
    String name;

    bool operator==(const Drug &other) const
	{
		return name == other.name;
	}

    bool operator<(const Drug &other) const
	{
		return name < other.name;
	}
}

struct Condition {
    String name;

    bool operator==(const Condition &other) const
	{
		return name == other.name;
	}

    bool operator<(const Condition &other) const
	{
		return name < other.name;
	}
}

struct DrugReview {
    int id;
    Drug drug;
    Condition condition;
    String review;
    int rating;
    tm date;
    int usefulCount;
}