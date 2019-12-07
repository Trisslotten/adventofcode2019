#include <iostream>
#include <algorithm>

bool isValid(int n)
{
	bool found_double = false;
	int concurrent = 0;
	int min_concurrent = 10000;
	int t = 10;
	for (int i = 1; i < log10(n); i++)
	{
		int a = (n / t) % 10;
		int b = (n / (t / 10)) % 10;
		if (a > b)
		{
			return false;
		}
		if (a == b)
		{
			concurrent++;
			found_double = true;
		}
		else if (concurrent != 0)
		{
			min_concurrent = std::min(concurrent+1, min_concurrent);
			concurrent = 0;
		}

		t *= 10;
	}
	if (concurrent != 0)
	{
		min_concurrent = std::min(concurrent + 1, min_concurrent);
		concurrent = 0;
	}

	return found_double && min_concurrent == 2;
}

// 123444

int main()
{
	int start = 357253;
	int end = 892942;

	int count = 0;
	for (int i = start; i < end; i++)
	{
		if (isValid(i))
		{
			count++;
		}
	}

	std::cout << count << "\n";
	return 0;
}