#include <utility>
#include <vector>
class Node {
 public:
	 Node() { member = false; };
	 Node(int x, int y);
	 void add(Node* next);
	 void clear();
	 bool member;
	 bool elemNexts(Node* node);
	 std::pair<int, int> location;
 private:
	 std::vector<Node*> nexts;
};