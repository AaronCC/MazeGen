#include "Node.h"
#include <utility>
#include <vector>

class Maze {
public:
	Maze(const int width, const int height);
	bool select(Node* node);
	bool spawnBranch();
	bool selectBranch(Node* node);
	void print();
	bool DFS(int x, int y);
	bool DFSUntil(Node * node, bool found);
	void eraseMember(Node* node);
	std::vector<Node*> getAdjacent(Node* node);
	bool clearToEndY(int dir, int x, int y);
	bool clearToEndX(int dir, int x, int y);
	//bool canEscape(Node* node);
private:
	std::vector<Node*> members;
	std::pair<int, int> dims;
	Node* start;
	Node* end;
	Node** matrix;
};