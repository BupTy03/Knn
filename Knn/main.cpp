#include "point.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cassert>
#include <algorithm>


template<class T>
std::vector<double> knn(
				const std::size_t k,
				const std::size_t countClasses, 
				const std::vector<T>& objects,
				const std::vector<std::size_t>& mapping,
				const T& newObject)
{
	assert(k <= objects.size());

	std::vector<std::pair<std::size_t, double>> distances(objects.size());
	for (std::size_t objectID = 0; objectID < objects.size(); ++objectID)
		distances.at(objectID) = std::make_pair(mapping.at(objectID), distance(newObject, objects.at(objectID)));
	
	std::partial_sort(distances.begin(), distances.begin() + k, distances.end(), 
		[](const auto& lhs, const auto& rhs) {return lhs.second < rhs.second; });
	
	std::vector<double> results(countClasses);
	for (std::size_t classID = 0; classID < countClasses; ++classID)
	{
		const auto countObjectsOfClass = std::count_if(distances.cbegin(), distances.cbegin() + k, 
			[classID](const auto& p) { return p.first == classID; });
		
		results.at(classID) = static_cast<double>(countObjectsOfClass) / static_cast<double>(k);
	}

	return results;
}

void print(const std::vector<std::string>& classes, const std::vector<double>& chances)
{
	assert(classes.size() == chances.size());

	for (std::size_t classID = 0; classID < classes.size(); ++classID)
		std::cout << classes.at(classID) << ": " << chances.at(classID) << '\n';

	std::cout.flush();
}

void Example1()
{
	const std::vector<std::string> classes{ "A", "B", "C" };
	const std::vector<point2<int>> objects = {
		point2<int>{0, 0},
		point2<int>{1, 1},
		point2<int>{2, 3},
		point2<int>{3, 2},
		point2<int>{0, 3},

		point2<int>{0, 6},
		point2<int>{1, 8},
		point2<int>{2, 6},
		point2<int>{3, 7},
		point2<int>{0, 8},

		point2<int>{8, 1},
		point2<int>{9, 2},
		point2<int>{8, 0},
		point2<int>{7, 1},
		point2<int>{10, 3}
	};

	const std::vector<std::size_t> mapping = {
		0, 0, 0, 0, 0,
		1, 1, 1, 1, 1,
		2, 2, 2, 2, 2
	};

	const auto results = knn(5, classes.size(), objects, mapping, point2<int>{1, 6});
	print(classes, results);
}


struct WoodProperties
{
	explicit WoodProperties(double crackLength, double diameterOfWoodKnot)
		: crackLength{ crackLength }, diameterOfWoodKnot{ diameterOfWoodKnot } {}

	double crackLength{ 0.0 };
	double diameterOfWoodKnot{ 0.0 };
};

double distance(const WoodProperties& lhs, const WoodProperties& rhs)
{
	return std::sqrt(
		std::pow(rhs.crackLength - lhs.crackLength, 2.0) +
		std::pow(rhs.diameterOfWoodKnot - lhs.diameterOfWoodKnot, 2.0));
}


void Example2()
{
	const std::vector<std::string> classes{ "defect", "normal" };
	const std::vector<WoodProperties> objects = {
		WoodProperties(7.0, 7.0),
		WoodProperties(7.0, 4.0),
		WoodProperties(3.0, 4.0),
		WoodProperties(1.0, 4.0)
	};

	const std::vector<std::size_t> mapping{ 0, 0, 1, 1 };
	const WoodProperties newObject(3.0, 7.0);
	const std::size_t k = 3;

	const auto results = knn(k, classes.size(), objects, mapping, newObject);
	print(classes, results);
}


int main()
{
	Example1();
	Example2();
	return 0;
}
