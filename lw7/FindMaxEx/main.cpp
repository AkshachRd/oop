#include <iostream>
#include <string>
#include "FindMaxEx.h"

using namespace std;

struct Athlete
{
	Athlete()
		: m_name(""), m_height(0), m_weight(0)
	{}

	Athlete(string name, double height, double weight)
		: m_name(name), m_height(height), m_weight(weight)
	{}

	string m_name;
	double m_height;
	double m_weight;
};

ostream& operator<<(ostream& output, Athlete const& athlete)
{
	output << athlete.m_name << endl;
	output << "Weight: " << athlete.m_weight << "kg" << endl;
	output << "Height: " << athlete.m_height << "cm" << endl;

	return output;
}

void FindMaxWeightAthlete(vector<Athlete> const& athletes);
void FindMaxHeightAthlete(vector<Athlete> const& athletes);

int main(int argc, char* argv[])
{
	vector<Athlete> athletes;
	athletes = {
		Athlete("Granovsky Avaz Denisovich", 190.1, 65.3),
		Athlete("Shanskaya Victorina Olegovna", 180.5, 82.7),
		Athlete("Malinovskiy Gleb Mironovich", 155.1, 100)
	};

	FindMaxHeightAthlete(athletes);
	FindMaxWeightAthlete(athletes);

	return 0;
}

void FindMaxWeightAthlete(vector<Athlete> const& athletes)
{
	auto LessWeight = [](Athlete const& lhs, Athlete const& rhs)
	{
		return lhs.m_weight < rhs.m_weight;
	};

	Athlete maxWeightAthlete;

	FindMax(athletes, maxWeightAthlete, LessWeight);

	cout << endl << "Max weight athlete: " << maxWeightAthlete << endl;
}

void FindMaxHeightAthlete(vector<Athlete> const& athletes)
{
	auto LessHeight = [](Athlete const& lhs, Athlete const& rhs)
	{
		return lhs.m_height < rhs.m_height;
	};

	Athlete maxHeightAthlete;

	FindMax(athletes, maxHeightAthlete, LessHeight);

	cout << endl << "Max height athlete: " << maxHeightAthlete << endl;
}