#include "program.hpp"

void part1()
{
	Program program;
	program.setCode({ 109,424,203,1,21102,1,11,0,1106,0,282,21101,18,0,0,1105,1,259,1201,1,0,221,203,1,21102,1,31,0,1105,1,282,21102,38,1,0,1106,0,259,20102,1,23,2,21201,1,0,3,21101,1,0,1,21101,0,57,0,1106,0,303,1202,1,1,222,20101,0,221,3,21001,221,0,2,21101,259,0,1,21102,80,1,0,1106,0,225,21102,1,145,2,21101,91,0,0,1105,1,303,2101,0,1,223,20101,0,222,4,21102,1,259,3,21101,0,225,2,21101,0,225,1,21102,1,118,0,1105,1,225,21001,222,0,3,21101,80,0,2,21101,133,0,0,1105,1,303,21202,1,-1,1,22001,223,1,1,21101,148,0,0,1106,0,259,1201,1,0,223,20102,1,221,4,20101,0,222,3,21101,0,23,2,1001,132,-2,224,1002,224,2,224,1001,224,3,224,1002,132,-1,132,1,224,132,224,21001,224,1,1,21102,1,195,0,106,0,109,20207,1,223,2,21001,23,0,1,21102,1,-1,3,21102,1,214,0,1105,1,303,22101,1,1,1,204,1,99,0,0,0,0,109,5,2101,0,-4,249,22101,0,-3,1,22102,1,-2,2,21201,-1,0,3,21101,0,250,0,1105,1,225,21202,1,1,-4,109,-5,2105,1,0,109,3,22107,0,-2,-1,21202,-1,2,-1,21201,-1,-1,-1,22202,-1,-2,-2,109,-3,2106,0,0,109,3,21207,-2,0,-1,1206,-1,294,104,0,99,22101,0,-2,-2,109,-3,2105,1,0,109,5,22207,-3,-4,-1,1206,-1,346,22201,-4,-3,-4,21202,-3,-1,-1,22201,-4,-1,2,21202,2,-1,-1,22201,-4,-1,1,21202,-2,1,3,21102,1,343,0,1106,0,303,1105,1,415,22207,-2,-3,-1,1206,-1,387,22201,-3,-2,-3,21202,-2,-1,-1,22201,-3,-1,3,21202,3,-1,-1,22201,-3,-1,2,22101,0,-4,1,21102,384,1,0,1105,1,303,1106,0,415,21202,-4,-1,-4,22201,-4,-3,-4,22202,-3,-2,-2,22202,-2,-4,-4,22202,-3,-2,-3,21202,-4,-1,-2,22201,-3,-2,1,21202,1,1,-4,109,-5,2106,0,0 });

	int count = 0;
	for (int y = 0; y < 200; y++)
	{
		for (int x = 0; x < 150; x++)
		{
			program.queueInput(x);
			program.queueInput(y);

			auto output = program.run();

			//std::cout << output << ",";
			if (output == 1)
				std::cout << "#";
			else 
				std::cout << " ";


			program.reset();
			count += output;
		}
		std::cout << "\n";
	}

	std::cout << count << "\n";
}


Program program;

bool IsInside(int x, int y)
{
	program.reset();

	program.queueInput(x);
	program.queueInput(y);

	auto output = program.run();

	//std::cout << "output: " << output << "\n";

	return output == 1;
}

void part2()
{
	program.setCode({ 109,424,203,1,21102,1,11,0,1106,0,282,21101,18,0,0,1105,1,259,1201,1,0,221,203,1,21102,1,31,0,1105,1,282,21102,38,1,0,1106,0,259,20102,1,23,2,21201,1,0,3,21101,1,0,1,21101,0,57,0,1106,0,303,1202,1,1,222,20101,0,221,3,21001,221,0,2,21101,259,0,1,21102,80,1,0,1106,0,225,21102,1,145,2,21101,91,0,0,1105,1,303,2101,0,1,223,20101,0,222,4,21102,1,259,3,21101,0,225,2,21101,0,225,1,21102,1,118,0,1105,1,225,21001,222,0,3,21101,80,0,2,21101,133,0,0,1105,1,303,21202,1,-1,1,22001,223,1,1,21101,148,0,0,1106,0,259,1201,1,0,223,20102,1,221,4,20101,0,222,3,21101,0,23,2,1001,132,-2,224,1002,224,2,224,1001,224,3,224,1002,132,-1,132,1,224,132,224,21001,224,1,1,21102,1,195,0,106,0,109,20207,1,223,2,21001,23,0,1,21102,1,-1,3,21102,1,214,0,1105,1,303,22101,1,1,1,204,1,99,0,0,0,0,109,5,2101,0,-4,249,22101,0,-3,1,22102,1,-2,2,21201,-1,0,3,21101,0,250,0,1105,1,225,21202,1,1,-4,109,-5,2105,1,0,109,3,22107,0,-2,-1,21202,-1,2,-1,21201,-1,-1,-1,22202,-1,-2,-2,109,-3,2106,0,0,109,3,21207,-2,0,-1,1206,-1,294,104,0,99,22101,0,-2,-2,109,-3,2105,1,0,109,5,22207,-3,-4,-1,1206,-1,346,22201,-4,-3,-4,21202,-3,-1,-1,22201,-4,-1,2,21202,2,-1,-1,22201,-4,-1,1,21202,-2,1,3,21102,1,343,0,1106,0,303,1105,1,415,22207,-2,-3,-1,1206,-1,387,22201,-3,-2,-3,21202,-2,-1,-1,22201,-3,-1,3,21202,3,-1,-1,22201,-3,-1,2,22101,0,-4,1,21102,384,1,0,1105,1,303,1106,0,415,21202,-4,-1,-4,22201,-4,-3,-4,22202,-3,-2,-2,22202,-2,-4,-4,22202,-3,-2,-3,21202,-4,-1,-2,22201,-3,-2,1,21202,1,1,-4,109,-5,2106,0,0 });

	int i = 0;
	int start = 30;
	int prev_x = 20;
	double slope_estimate = 0.0;
	bool found = false;
	while (!found)
	{
		int x = i * i + start;
		int y = slope_estimate * x;

		while(!IsInside(x, y)) y++;

		//slope_estimate = double(y) / x;

		std::cout << "IsInside(" << x << ", " << y << ") = " << IsInside(x, y) << "\n";

		std::cout << (x - 99) * 10000 + y << "\n";

		if (IsInside(x - 99, y + 99))
		{
			auto old_start = start;
			start = i-1;
			start *= start;
			start += old_start;
			i = -1;
		}
		i++;
	}
}

void main()
{
	//part1();
	part2();
}