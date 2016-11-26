#include "Maze.h"
#include <stdlib.h>
#include <iostream>
#include <time.h>

Maze::Maze(const int width, const int height)
{
	dims = std::make_pair(height, width);
	matrix = new Node*[height];
	for (int i = 0; i < height; i++)
	{
		matrix[i] = new Node[width];
		for (int c = 0; c < width; c++)
		{
			matrix[i][c] = Node(i, c);
		}
	}
	start = &matrix[0][0];
	end = &matrix[height - 1][width - 1];
	start->member = true;
	members.push_back(start);
	members.push_back(end);
	//int x = 1, y = 1;
	/*Node* old;
	Node* next;*/
	//old = start;
	//for (y = 1; y < height; y++)
	//{
	//	next = &matrix[y][x];
	//	old->add(next);
	//	old = next;
	//	for (x = 1; x < width; x++);
	//	{
	//		next = &matrix[y][x];
	//		old->add(next);
	//		old = next;
	//	}
	//}
	select(start);
}

std::vector<Node*> Maze::getAdjacent(Node* node)
{
	std::vector<Node*> adjacent;
	Node* selected;
	for (int y = -1; y <= 1; y += 2)
	{
		if (node->location.first + y < dims.first && node->location.first + y >= 0)
		{
			selected = &matrix[node->location.first + y][node->location.second];
			if (!selected->member)
				adjacent.push_back(selected);
		}
	}
	for (int x = -1; x <= 1; x += 2)
	{
		if (node->location.second + x < dims.second && node->location.second + x >= 0)
		{
			selected = &matrix[node->location.first][node->location.second + x];
			if (!selected->member)
				adjacent.push_back(selected);
		}
	}
	return adjacent;
}
bool Maze::select(Node* node)
{
	int rand = -1;
	std::srand(time(NULL));
	std::vector<Node*> adjacent;
	Node* selected = nullptr;
	adjacent = getAdjacent(node);
	if (adjacent.size() == 2 && (
		adjacent.at(0)->location.first == adjacent.at(1)->location.first ||
		adjacent.at(0)->location.second == adjacent.at(1)->location.second))
	{
		if (DFS(adjacent.at(0)->location.second, adjacent.at(0)->location.first))
			selected = adjacent.at(0);
		else if (DFS(adjacent.at(1)->location.second, adjacent.at(1)->location.first))
			selected = adjacent.at(1);
		/*int aDiff, bDiff;
		int xDiff = adjacent.at(0)->location.second - node->location.second;
		int yDiff = adjacent.at(0)->location.first - node->location.first;
		if (xDiff != 0)
		{
			int xDiff2 = adjacent.at(1)->location.second - node->location.second;
			bool clearX0 = clearToEndX(xDiff, adjacent.at(0)->location.second, adjacent.at(0)->location.first);
			bool clearX1 = clearToEndX(xDiff2, adjacent.at(1)->location.second, adjacent.at(1)->location.first);
			if (clearX0 && clearX1)
			{
				aDiff = end->location.second - adjacent.at(0)->location.second;
				bDiff = end->location.second - adjacent.at(1)->location.second;
				if (aDiff > bDiff)
					selected = adjacent.at(1);
				if (bDiff > aDiff)
					selected = adjacent.at(0);
			}
			else if (clearX0)
			{
				selected = adjacent.at(0);
			}
			else if (clearX1)
			{
				selected = adjacent.at(1);
			}
			else
			{
				bool clearYS0 = clearToEndY(1, adjacent.at(0)->location.second, adjacent.at(0)->location.first);
				bool clearYN0 = clearToEndY(-1, adjacent.at(0)->location.second, adjacent.at(0)->location.first);
				if (clearYS0 || clearYN0)
				{
					selected = adjacent.at(0);
				}
				bool clearYS1 = clearToEndY(1, adjacent.at(1)->location.second, adjacent.at(1)->location.first);
				bool clearYN1 = clearToEndY(-1, adjacent.at(1)->location.second, adjacent.at(1)->location.first);
				if (clearYS1 || clearYN1)
				{
					selected = adjacent.at(1);
				}
			}
		}
		if (yDiff != 0)
		{
			int yDiff2 = adjacent.at(1)->location.first - node->location.first;
			bool clearY0 = clearToEndY(yDiff, adjacent.at(0)->location.second, adjacent.at(0)->location.first);
			bool clearY1 = clearToEndY(yDiff2, adjacent.at(1)->location.second, adjacent.at(1)->location.first);
			if (clearY0 && clearY1)
			{
				aDiff = end->location.first - adjacent.at(0)->location.first;
				bDiff = end->location.first - adjacent.at(1)->location.first;
				if (aDiff > bDiff)
					selected = adjacent.at(1);
				if (bDiff > aDiff)
					selected = adjacent.at(0);
			}
			else if (clearY0)
			{
				selected = adjacent.at(0);
			}
			else if (clearY1)
			{
				selected = adjacent.at(1);
			}
			else
			{
				bool clearXS0 = clearToEndX(1, adjacent.at(0)->location.second, adjacent.at(0)->location.first);
				bool clearXN0 = clearToEndX(-1, adjacent.at(0)->location.second, adjacent.at(0)->location.first);
				if (clearXS0 || clearXN0)
				{
					selected = adjacent.at(0);
				}
				bool clearXS1 = clearToEndX(1, adjacent.at(1)->location.second, adjacent.at(1)->location.first);
				bool clearXN1 = clearToEndX(-1, adjacent.at(1)->location.second, adjacent.at(1)->location.first);
				if (clearXS1 || clearXN1)
				{
					selected = adjacent.at(1);
				}
			}*/
		//}
	}
	else if (adjacent.size() > 0)
	{
		rand = std::rand() % adjacent.size();
		selected = adjacent.at(rand);
	}
	else
		return false;
	if (selected != nullptr)
		node->add(selected);
	if (selected != end)
	{
		std::system("cls");
		print();
		std::cout << "Adj:" << adjacent.size() << " Choice:" << rand;
		std::getchar();
		members.push_back(selected);
		return select(selected);
	}
	else
	{
		node->add(end);
		return true;
	}
}

bool Maze::spawnBranch()
{
	if (members.size() == 0)
		return false;
	std::srand(time(NULL));
	int rand = std::rand() % members.size();
	if (!selectBranch(members.at(rand)))
		return spawnBranch();
	return true;
}

bool Maze::selectBranch(Node* node)
{
	std::srand(time(NULL));
	std::vector<Node*> adjacent;
	Node* selected = nullptr;
	for (int y = -1; y <= 1; y += 2)
	{
		if (node->location.first + y < dims.first && node->location.first + y >= 0)
		{
			selected = &matrix[node->location.first + y][node->location.second];
			if (!selected->member)
				adjacent.push_back(selected);
		}
	}
	for (int x = -1; x <= 1; x += 2)
	{
		if (node->location.second + x < dims.second && node->location.second + x >= 0)
		{
			selected = &matrix[node->location.first][node->location.second + x];
			if (!selected->member)
				adjacent.push_back(selected);
		}
	}
	if (adjacent.size() > 0)
	{
		int rand = std::rand() % adjacent.size();
		selected = adjacent.at(rand);
	}
	else
	{
		eraseMember(node);
		return false;
	}
	if (selected != nullptr)
	{
		node->add(selected);
		std::system("cls");
		print();
		std::getchar();
		members.push_back(selected);
		return selectBranch(selected);
	}
	return true;
}
void Maze::eraseMember(Node* node)
{
	for (int i = 0; i < members.size(); i++)
	{
		if (members.at(i) == node)
		{
			members.erase(members.begin() + i);
		}
	}
}
void Maze::print()
{
	for (int i = 0; i < dims.first; i++)
	{
		for (int c = 0; c < dims.second; c++)
		{
			if (matrix[i][c].member == true)
				std::cout << "*";
			else if (matrix[i][c].visited == true)
				std::cout << "o";
			else
				std::cout << "-";
		}
		std::cout << std::endl;
	}
}

bool Maze::clearToEndY(int dir, int x, int y)
{
	Node* selected = &matrix[y][x];
	if (selected->member)
		return false;
	if (y == 0 || y == end->location.first)
		return true;
	return clearToEndY(dir, x, y + dir);
}

bool Maze::clearToEndX(int dir, int x, int y)
{
	Node* selected = &matrix[y][x];
	if (selected->member)
		return false;
	if (x == 0 || x == end->location.second)
		return true;
	return clearToEndX(dir, x + dir, y);
}

bool Maze::DFS(int posX, int posY)
{
	for (int y = 0; y < dims.first; y++)
	{
		for (int x = 0; x < dims.second; x++)
		{
			matrix[y][x].visited = false;
		}
	}
	return DFSUntil(&matrix[posY][posX], false);
}

bool Maze::DFSUntil(Node* node, bool found)
{
	std::system("cls");
	print();
	std::getchar();

	std::vector<Node*> adjacent;
	node->visited = true;
	adjacent = getAdjacent(node);
	for (int i = 0; i < adjacent.size(); i++)
	{
		node = adjacent.at(i);
		if (node == end)
			found = true;
		if (!node->visited)
			found = DFSUntil(node, found);
	}
	return found;
}