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
	void eraseMember(Node* node);
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