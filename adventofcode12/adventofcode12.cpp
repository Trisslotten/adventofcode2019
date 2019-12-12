#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <future>
#include <algorithm>  
#include <numeric>

struct ivec3
{
	union
	{
		struct
		{
			int64_t x, y, z;
		};
		int64_t v[3];
	};

	ivec3 operator+(ivec3 other)
	{
		return { x + other.x, y + other.y, z + other.z };
	}
	ivec3 operator-(ivec3 other)
	{
		return { x - other.x, y - other.y, z - other.z };
	}
	ivec3 operator*(ivec3 other)
	{
		return { x * other.x, y * other.y, z * other.z };
	}
	bool operator==(ivec3 other)
	{
		return x == other.x && y == other.y && z == other.z;
	}
	int64_t& operator[](size_t i)
	{
		return v[i];
	}
};
int64_t sign(int64_t i)
{
	if (i > 0)
		return 1;
	else if (i == 0)
		return 0;
	else
		return -1;
}
ivec3 sign(ivec3 v)
{
	return { sign(v.x), sign(v.y), sign(v.z) };
}
ivec3 abs(ivec3 v)
{
	return sign(v) * v;
}
int64_t sum(ivec3 v)
{
	return v.x + v.y + v.z;
}

struct Planet
{
	ivec3 pos;
	ivec3 vel;

	void calcMyGravity(Planet other)
	{
		ivec3 gravity = sign(other.pos - pos);
		vel = vel + gravity;
	}

	void update()
	{
		pos = pos + vel;
	}

	int64_t calcEnergy()
	{
		return sum(abs(pos)) * sum(abs(vel));
	}
};

void part1()
{
	std::vector<Planet> planets;
	planets.push_back({ {3,3,0},{0,0,0} });
	planets.push_back({ {4,-16,2},{0,0,0} });
	planets.push_back({ {-10,-6,5},{0,0,0} });
	planets.push_back({ {-3,0,-13},{0,0,0} });

	int64_t output_range = 20;

	for (int64_t i = 0; i < 1000; i++)
	{
		for (int64_t i = 0; i < planets.size(); i++)
		{
			for (int64_t j = 0; j < planets.size(); j++)
			{
				if (i != j)
				{
					planets[i].calcMyGravity(planets[j]);
				}
			}
		}

		for (auto& planet : planets)
		{
			planet.update();
		}
		/*
		system("cls");
		for (int64_t y = -output_range; y <= output_range; y++)
		{
			for (int64_t x = -output_range; x <= output_range; x++)
			{
				for (auto& planet : planets)
				{
					if (planet.pos.x == x && planet.pos.y == y)
					{
						std::cout << "o";
					}
					else
					{
						std::cout << " ";
					}
				}
			}
			std::cout << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		*/
	}

	int64_t sum = 0;
	for (auto& planet : planets)
	{
		sum += planet.calcEnergy();
	}
	std::cout << sum << "\n";
}

void main()
{
	

	ivec3 cycles{ 0,0,0 };
	for (int64_t c = 0; c < 3; c++)
	{
		std::vector<Planet> planets;
		planets.push_back({ {3,3,0},{0,0,0} });
		planets.push_back({ {4,-16,2},{0,0,0} });
		planets.push_back({ {-10,-6,5},{0,0,0} });
		planets.push_back({ {-3,0,-13},{0,0,0} });
		std::vector<Planet> initial_state = planets;
		int64_t steps = 0;
		while (true)
		{
			for (int64_t i = 0; i < planets.size(); i++)
			{
				for (int64_t j = 0; j < planets.size(); j++)
				{
					if (i != j)
					{
						planets[i].calcMyGravity(planets[j]);
					}
				}
			}

			for (auto& planet : planets)
			{
				planet.update();
			}

			steps++;

			bool same_state = true;
			for (int64_t i = 0; i < planets.size(); i++)
			{
				if (planets[i].pos[c] != initial_state[i].pos[c])
				{
					same_state = false;
					break;
				}
			}
			if (same_state)
			{
				break;
			}
		}
		cycles[c] = steps+1;

		std::cout << steps << "\n";
	}

	std::cout << std::lcm(cycles[0], std::lcm(cycles[1], cycles[2])) << "\n";
}