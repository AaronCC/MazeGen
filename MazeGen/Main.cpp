#include "Maze.h"
#include <iostream>
int main()
{
	int branches = 0;
	int x, y;
	std::cin >> x >> y;
	Maze maze(x, y);
	while (maze.spawnBranch())
		branches++;
	std::system("cls");
	maze.print();
	std::cout << "ALL DONE!";
	std::getchar();
	return 0;
}