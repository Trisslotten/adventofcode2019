#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

int width = 0;
int height = 0;
std::string map;

char getTile(int x, int y)
{
    if(x < 0 || x >= width || y < 0 || y >= height)
	return ' ';
	
    return map[x + y * width];
}

bool isPortalTile(char tile)
{
    return tile >= 'A' && tile <= 'Z';
}



int main()
{
    std::string line;
    std::ifstream file("data.txt");
    if(file.is_open())
    {
	while (getline(file, line))
	{
	    if (width == 0)
		width = line.size();
	    map += line;
	    
	    height++;
	}
    }
    /*
    for(int y = 0; y < height; y++)
    {
	std::cout << map.substr(y*width, width);
	std::cout << "\n";
    }
    */
    
    for(int i = 0; i < width * height; i++)
    {
	int x = i % width;
	int y = i / width;
	
	char tile = getTile(x, y);
	
	if(isPortalTile(tile))
	{
	    if (isPortalTile(getTile(x+1, y)))
	    {
		
	    } 
	    else if(isPortalTile(getTile(x, y+1)))
	    {
		
	    }
	}
    }
    
    
    std::queue<std::pair<int, int>>
    
    
    
    return 0; 
}
