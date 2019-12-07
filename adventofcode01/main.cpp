#include <iostream>
#include <fstream>
#include <string>

void part1()
{
	std::string line;
	std::ifstream data("data.txt");
	size_t sum = 0;
	if (data.is_open())
	{
		while (getline(data, line))
		{
			size_t fuel_r = std::stoi(line);
			fuel_r = fuel_r / 3 - 2;
			sum += fuel_r;
		}
		data.close();
	}

	std::cout << sum << "\n";
}

void part2()
{
	std::string line;
	std::ifstream data("data.txt");
	long long sum = 0;

	int line_nr = 0;
	if (data.is_open())
	{
		while (getline(data, line))
		{
			std::cout << line_nr << "\n";
			long long fuel_r = std::stoi(line);
			fuel_r = fuel_r / 3 - 2;
			while (fuel_r > 0)
			{
				std::cout<< "\t" << fuel_r << "\n";
				sum += fuel_r;
				fuel_r = fuel_r / 3 - 2;
			}
			line_nr++;
		}
		data.close();
	}

	std::cout << sum << "\n";
}

int main()
{
	part2();

	return 0;
}