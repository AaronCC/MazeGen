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
	}
	else if (adjacent.size() > 0)
	{
		rand = std::rand() % adjacent.size();
		selected = adjacent.at(rand);
	}
	else
		return false;
	if (selected != end)
	{
		std::system("cls");
		print();
		std::cout << "Adj:" << adjacent.size() << " Choice:" << rand;
		std::getchar();
		node->add(selected);
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
	Node* node = members.at(rand);
	if (!selectBranch(node))
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
		node->add(selected);
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
	Node *node = nullptr;
	Node *nodeN = nullptr;
	Node *nodeE = nullptr;
	Node *nodeS = nullptr;
	Node *nodeW = nullptr;
	const int height = dims.first * 2 + 1;
	const int width = dims.second * 2 + 1;
	char ** drawable;
	drawable = new char*[height];
	for (int i = 0; i < height; i++)
	{
		drawable[i] = new char[width];
		for (int c = 0; c < width; c++)
		{
			drawable[i][c] = '0';
		}
	}

	for (int i = 0; i < dims.first; i++)
	{
		for (int c = 0; c < dims.second; c++)
		{
			node = &matrix[i][c];
			if (i - 1 >= 0)
				nodeN = &matrix[i - 1][c];
			if (c + 1 < dims.second)
				nodeE = &matrix[i][c + 1];
			if (i + 1 < dims.first)
				nodeS = &matrix[i + 1][c];
			if (c - 1 >= 0)
				nodeW = &matrix[i][c - 1];
			int newi = i * 2 + 1;
			int newc = c * 2 + 1;

			if(node->member == true)
				drawable[newi][newc] = ' ';

			if (nodeN != nullptr)
				if (node->elemNexts(nodeN))
					drawable[newi - 1][newc] = ' ';
			if (nodeE != nullptr)
				if (node->elemNexts(nodeE))
					drawable[newi][newc + 1] = ' ';
			if (nodeS != nullptr)
				if (node->elemNexts(nodeS))
					drawable[newi + 1][newc] = ' ';
			if (nodeW != nullptr)
				if (node->elemNexts(nodeW))
					drawable[newi][newc - 1] = ' ';

			nodeN = nullptr;
			nodeE = nullptr;
			nodeS = nullptr;
			nodeW = nullptr;
		}
	}
	for (int i = 0; i < height; i++)
	{
		for (int c = 0; c < width; c++)
		{
			std::putchar(drawable[i][c]);
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
{/*
	std::system("cls");
	print();
	std::getchar();*/

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