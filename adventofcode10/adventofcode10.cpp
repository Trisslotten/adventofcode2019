#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <thread>
#include <chrono>

int width = 0;
int height = 0;
std::string map = "";

int index(int x, int y)
{
	return x + y * width;
}

int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199 };

uint64_t findLowestFactors(int dx, int dy)
{
	union
	{
		struct
		{
			int32_t x, y;
		};
		uint64_t l;
	} un;
	int sx = dx > 0 ? 1 : -1;
	int sy = dy > 0 ? 1 : -1;

	if (dx == 0)
	{
		un.x = 0;
		un.y = sy;
		return un.l;
	}
	if (dy == 0)
	{
		un.x = sx;
		un.y = 0;
		return un.l;
	}


	for (int i = 0; i < width + height; i++)
	{
		int p = primes[i];
		for (int j = 0; j < width + height; j++)
		{
			int rx = ((dx * sx) % p);
			int ry = ((dy * sy) % p);
			if (rx == 0 && ry == 0)
			{
				dx /= p;
				dy /= p;
			}
			else
			{
				break;
			}
		}
		if (p > sx* dx || p > sy* dy)
		{
			un.x = dx;
			un.y = dy;
			return un.l;
		}
	}
}

int testTile(int tx, int ty)
{
	std::set<uint64_t> seen;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (x == tx && y == ty)
				continue;

			if (map.at(index(x, y)) == '#')
			{
				int dx = x - tx;
				int dy = y - ty;
				uint64_t a = findLowestFactors(dx, dy);
				if (seen.count(a) == 0)
				{
					seen.insert(a);
				}
			}
		}
	}
	return seen.size();
}

void part1()
{
	int max = 0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (map.at(index(x, y)) == '#')
			{
				int num_visible = testTile(x, y);
				std::cout << x << ", " << y << ": " << num_visible << "\n";
				if (num_visible > max)
				{
					max = num_visible;
				}
			}
		}
	}
	std::cout << max << "\n";
}

struct vec2
{
	double x, y;
	void normalize()
	{
		double len = sqrt(x * x + y * y);
		x /= len;
		y /= len;
	}
	double dot(vec2 other)
	{
		return x * other.x + y * other.y;
	}

	void rotate()
	{
		std::swap(x, y);
		x = -x;
	}
};

void part2()
{
	int px = 0;
	int py = 0;
	int max = 0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (map.at(index(x, y)) == '#')
			{
				int num_visible = testTile(x, y);
				if (num_visible > max)
				{
					max = num_visible;
					px = x;
					py = y;
				}
			}
		}
	}


	int cx = px;
	int cy = py-1;
	int nx = 0, ny = 0;
	for (int i = 0; i < 200; i++)
	{
		vec2 v{ cx - px , cy - py };
		v.normalize();
		vec2 v2 = v;
		v2.rotate();

		double smallest_dot = 100000000.f;
		// god forgive me
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if (map.at(index(x, y)) == '#')
				{

					vec2 c{ x - px , y - py };
					c.normalize();
					double dot = v2.dot(c);
					if (x == px && y == py || dot <= 0)
						continue;

					if (c.dot(v) > 0 && dot < smallest_dot)
					{
						smallest_dot = dot;
						nx = x;
						ny = y;
					}
				}
			}
		}
		map[index(nx, ny)] = 'x';
	
		cx = nx;
		cy = ny;


		system("cls");
		for (int y = 0; y < height; y++)
		{
			
			for (int x = 0; x < width; x++)
			{
				std::cout << map[index(x, y)];

				if (map[index(x, y)] == 'x')
				{
					map[index(x, y)] = ' ';
				}
			}
			std::cout << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	system("cls");
	std::cout << nx << " " << ny << "\n";
}


void main()
{
	std::string line;
	std::ifstream data("data.txt");
	if (data.is_open())
	{
		while (getline(data, line))
		{
			width = line.size();
			height++;
			map += line;
		}
		data.close();
	}

	//part1();
	part2();

}