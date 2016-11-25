#include "Maze.h"
#include <iostream>
int main()
{
	int branches = 0;
	Maze maze(10, 10);
	while (maze.spawnBranch())
		branches++;
	std::system("cls");
	maze.print();
	std::getchar();
	return 0;
}