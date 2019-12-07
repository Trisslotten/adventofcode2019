#include <iostream>
#include <string>
#include <vector>
#include <future>

int safeGet(std::vector<int>& vec, int i)
{
	if (i >= vec.size())
	{
		vec.resize(i, i);
	}
	return i;
}

void part1()
{
	std::string data = "1,0,0,3,1,1,2,3,1,3,4,3,1,5,0,3,2,1,10,19,2,6,19,23,1,23,5,27,1,27,13,31,2,6,31,35,1,5,35,39,1,39,10,43,2,6,43,47,1,47,5,51,1,51,9,55,2,55,6,59,1,59,10,63,2,63,9,67,1,67,5,71,1,71,5,75,2,75,6,79,1,5,79,83,1,10,83,87,2,13,87,91,1,10,91,95,2,13,95,99,1,99,9,103,1,5,103,107,1,107,10,111,1,111,5,115,1,115,6,119,1,119,10,123,1,123,10,127,2,127,13,131,1,13,131,135,1,135,10,139,2,139,6,143,1,143,9,147,2,147,6,151,1,5,151,155,1,9,155,159,2,159,6,163,1,163,2,167,1,10,167,0,99,2,14,0,0";

	std::vector<int> immutable;
	while (data.size() > 0)
	{
		size_t next;
		int number = std::stoi(data, &next);

		immutable.push_back(number);

		if(next + 1 > data.size())
			break;
		data = data.substr(1 + next);
	}

	std::vector<std::future<void>> futures;

	
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			std::vector<int> arr = immutable;
			arr[1] = i;
			arr[2] = j;

			size_t counter = 0;
			bool running = true;
			while (running)
			{
				int op = arr[counter];
				switch (op)
				{
				case 1:
				{
					int a = arr.at(arr[counter + 1]);
					int b = arr.at(arr[counter + 2]);
					arr[arr[counter + 3]] = a + b;
					counter += 4;
				}
				break;
				case 2:
				{
					int a = arr.at(arr[counter + 1]);
					int b = arr.at(arr[counter + 2]);
					arr[arr[counter + 3]] = a * b;
					counter += 4;
				}
				break;
				case 99:
				{
					running = false;
				}
				break;
				}
			}
			if (arr[0] == 19690720)
			{
				std::cout << 100*arr[1] + arr[2] << "\n";
			}
		}
	}
	
	
}

void part2()
{

}

int main()
{
	part1();

	return 0;
}