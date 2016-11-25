#include "Node.h"
#include <vector>

Node::Node(int x, int y)
{
	location = std::make_pair(x, y);
	member = false;
}

void Node::add(Node* next)
{
	nexts.push_back(next);
	if (!next->member)
		next->member = true;
} 

bool Node::elemNexts(Node* node)
{
	for (int i = 0; i < nexts.size(); i++)
	{
		if (nexts.at(i) == node)
		{
			return true;
		}
	}
	return false;
}

void Node::clear()
{
	nexts.clear();
}

