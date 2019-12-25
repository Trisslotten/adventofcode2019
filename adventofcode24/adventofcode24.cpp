#include <iostream>
#include <set>
#include <bitset>
#include <climits>
#include <unordered_map>

bool inRange(int x)
{
    return x >= 0 && x < 5;
}

uint32_t next(uint32_t c)
{
    uint32_t result = c;
    for(int i = 0; i < 5*5;i++)
    {
	int cx = i%5;
	int cy = i/5;
	int rx = 1;
	int ry = 0;
	int count = 0;
	for(int j = 0; j < 4; j++)
	{
	    int x = cx + rx;
	    int y = cy + ry;
	    if(inRange(x) && inRange(y))
	    {
		uint32_t mask = 1 << (x + y * 5);
		if(mask & c)
		    count++;
	    }
	    std::swap(rx, ry);
	    ry = -ry;
	}
	
	uint32_t mask = 1U << (cx + cy * 5);
	
	if (mask & c)
	{
	    if (count != 1)
	    {
		result &= ~mask;
	    }
	} else {
	    if(count == 1 || count == 2)
	    {
		result |= mask;
	    }
	}
    }
    return result;
}

void part1()
{
    std::set<uint32_t> prev;
    std::string map_str = "#..#.#.#.#...#.....##.#.#";
    uint32_t map = 0;
    for(int i = 0; i < 5*5;i++)
    {
	int cx = i%5;
	int cy = i/5;
	int index = cx + cy * 5;
	uint32_t mask = 1 << index;
	
	if(map_str[index] == '#')
	{
	    map |= mask;
	}
    }
    
    prev.insert(map);
    
    
    int i = 0;
    while(true)
    {
	/*
	for(int i = 0; i < 5*5;i++)
	{
	    int cx = i%5;
	    int cy = i/5;
	    if(cx == 0)
		std::cout << "\n";
	    int index = cx + cy * 5;
	    uint32_t mask = 1 << index;
	    if(map & mask)
		std::cout << "#";
	    else 
		std::cout << ".";
	}
	*/
	map = next(map);
	i++;
	if(prev.count(map) > 0)
	{
	    std::cout << map << "\n";
	    
	    std::cout << i << "\n";
	    break;
	}
	prev.insert(map);
	
	//std::cout << "\n\n";
    }
}

bool inRange(int x, int y)
{
    return inRange(x) && inRange(y);
}

int sign(int i)
{
    return i > 0 ? 1 : (i < 0 ? -1 : 0);
}

uint32_t next2(uint32_t external, uint32_t current, uint32_t internal)
{
    uint32_t result = current;
    for(int i = 0; i < 5*5;i++)
    {
	int cx = i%5;
	int cy = i/5;
	if(cx == 2 && cy == 2)
	    continue;
	    
	int rx = 1;
	int ry = 0;
	int count = 0;
	for(int j = 0; j < 4; j++)
	{
	    int x = cx + rx;
	    int y = cy + ry;
	    if(!inRange(x,y))
	    {
		// external
		x = 2 + rx;
		y = 2 + ry;
		
		uint32_t mask = 1 << (x + y * 5);
		if(mask & external)
		    count++;
	    }
	    else if(x == 2 && y == 2)
	    {
		// internal
		x = 4 * (1-rx)/2;
		y = 4 * (1-ry)/2;
		int vx = 0;
		int vy = 0;
		if(rx == 0) {
		    x = 0;
		    vx = 1;
		} else {
		    y = 0;
		    vy = 1;
		}
		
		for(int k = 0; k < 5; k++)
		{
		    uint32_t mask = 1 << (x + y * 5);
		    if(mask & internal)
			count++;
		    
		    x += vx;
		    y += vy;
		}
	    }
	    else
	    {
		// current
		uint32_t mask = 1 << (x + y * 5);
		if(mask & current)
		    count++;
	    }
	    std::swap(rx, ry);
	    ry = -ry;
	}
	
	uint32_t mask = 1U << (cx + cy * 5);
	
	if (mask & current)
	{
	    if (count != 1)
	    {
		result &= ~mask;
	    }
	} 
	else 
	{
	    if(count == 1 || count == 2)
	    {
		result |= mask;
	    }
	}
    }
    return result;
}

void part2()
{
    std::string map_str = "#..#.#.#.#...#.....##.#.#";
    uint32_t map = 0;
    for(int i = 0; i < 5*5;i++)
    {
	int cx = i%5;
	int cy = i/5;
	if(cx == 2 && cy == 2)
	    continue;
	int index = cx + cy * 5;
	uint32_t mask = 1 << index;
	
	if(map_str[index] == '#')
	{
	    map |= mask;
	}
    }
    
    
    std::unordered_map<int64_t, uint32_t> layers;
    layers[0] = map;
    
    for(int i = 0; i < 200; i++)
    {
	std::unordered_map<int64_t, uint32_t> temp = layers;
	std::unordered_map<int64_t, uint32_t> next_layers;
	
	
	int64_t min = LLONG_MAX;
	int64_t max = LLONG_MIN;
	for(auto iter : layers)
	{
	    uint32_t ex = temp[iter.first-1];
	    uint32_t cu = iter.second;
	    uint32_t in = temp[iter.first+1];
	    next_layers[iter.first] = next2(ex, cu, in);
	    if(iter.first-1 < min)
		min = iter.first-1;
		
	    if(iter.first+1 > max)
		max = iter.first+1;
	}
	
	uint32_t ex = temp[min-1];
	uint32_t cu = temp[min];
	uint32_t in = temp[min+1];
	next_layers[min] = next2(ex, cu, in);
	
	ex = temp[max-1];
	cu = temp[max];
	in = temp[max+1];
	next_layers[max] = next2(ex, cu, in);
	
	layers = next_layers;
    }
    
    for(int i = -5; i <= 5; i++)
    {
	map = layers[i];
	std::cout << "depth: " << i << " ";
	for(int i = 0; i < 5*5; i++)
	{
	    int cx = i%5;
	    int cy = i/5;
	    if(cx == 0)
		std::cout << "\n";
	    int index = cx + cy * 5;
	    uint32_t mask = 1 << index;
	    if(cx == 2 && cy == 2)
		std::cout << "?";
	    else if(map & mask)
		std::cout << "#";
	    else 
		std::cout << ".";
	}
	
	std::cout << "\n\n";
    }
    
    int sum = 0;
    for(auto iter : layers)
    {
	std::bitset<32> bitset = iter.second;
	sum += bitset.count();
    }
    std::cout << sum << "\n";
}


int main()
{
    part2();
    return 0;
}







