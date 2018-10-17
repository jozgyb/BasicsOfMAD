//============================================================================
// Name        : proxy_pattern.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// your solution comes here

#include <cstdio>
#include <string>
#include <iostream>
#include <stack>
using std::string;

struct Vertex
{
	char key;
	long long sum;  // number of nodes below the node (include itself)
	Vertex* left;
	Vertex* right;
	Vertex* parent;

	Vertex(char key, long long sum, Vertex* left, Vertex* right, Vertex* parent) :
			key(key), sum(sum), left(left), right(right), parent(parent)
	{
	}
};

class Rope
{
	std::string s;
	Vertex* root;
	public:
	Rope()
		{
			root = nullptr;
			s = "";
		}
	Rope(const std::string &s) :
			s(s)
	{
		root = nullptr;
		for (unsigned int w = 0; w < s.length(); w++)
		{
			Vertex* next = new Vertex(s[w], 1ll, NULL, NULL, NULL);
			root = merge(root, next);
		}
	}

	~Rope()
	{
		free_space(root);
	}

	void free_space(Vertex* root)
	{
		if (root != NULL)
		{
			if (root->left != NULL)
			{
				free_space(root->left);
			}
			if (root->right != NULL)
			{
				free_space(root->right);
			}
			delete root;
		}
	}
	void update(Vertex* v)
	{
		if (v == NULL)
			return;
		v->sum = 1 + (v->left != NULL ? v->left->sum : 0ll)
				+ (v->right != NULL ? v->right->sum : 0ll);
		if (v->left != NULL)
		{
			v->left->parent = v;
		}
		if (v->right != NULL)
		{
			v->right->parent = v;
		}
	}

	void small_rotation(Vertex* v)
	{
		Vertex* parent = v->parent;
		if (parent == NULL)
		{
			return;
		}
		Vertex* grandparent = v->parent->parent;
		if (parent->left == v)
		{
			Vertex* m = v->right;
			v->right = parent;
			parent->left = m;
		}
		else
		{
			Vertex* m = v->left;
			v->left = parent;
			parent->right = m;
		}
		update(parent);
		update(v);
		v->parent = grandparent;
		if (grandparent != NULL)
		{
			if (grandparent->left == parent)
			{
				grandparent->left = v;
			}
			else
			{
				grandparent->right = v;
			}
		}
	}

	void big_rotation(Vertex* v)
	{
		if (v->parent->left == v && v->parent->parent->left == v->parent)
		{
			// Zig-zig
			small_rotation(v->parent);
			small_rotation(v);
		}
		else if (v->parent->right == v && v->parent->parent->right == v->parent)
		{
			// Zig-zig
			small_rotation(v->parent);
			small_rotation(v);
		}
		else
		{
			// Zig-zag
			small_rotation(v);
			small_rotation(v);
		}
	}

	// Makes splay of the given vertex and makes
	// it the new root.
	void splay(Vertex*& root, Vertex* v)
	{
		if (v == NULL)
			return;
		while (v->parent != NULL)
		{
			if (v->parent->parent == NULL)
			{
				small_rotation(v);
				break;
			}
			big_rotation(v);
		}
		root = v;
	}

	// Searches for the node which has 'leftNum' number of nodes
	// in the left side(including itself) in the tree with the given root
	// and calls splay for the deepest visited node after that.
	// If found, returns a pointer to that node
	// Otherwise (only in case leftNum is bigger than the total
	// number of the nodes in the tree), returns NULL

	Vertex* find(Vertex*& root, int leftNum)
	{
		Vertex* v = root;

		while(v!=NULL)
		{
			long long s = (v->left != NULL) ? v->left->sum : 0ll;
			if (leftNum == (s + 1))
			{
				break;
			}
			else if (leftNum < (s + 1))
			{
				v = v->left;
			}
			else if (leftNum > (s + 1))
			{
				v = v->right;
				leftNum = leftNum - s - 1;
			}
		}
		splay(root, v);
		return v;
	}

	void split(Vertex* root, int key, Vertex*& left, Vertex*& right)
	{
		right = find(root, key);
		//splay(root, right);

		if (right == NULL)
		{
			left = root;
			return;
		}

		left = right->left;

		right->left = NULL;

		if (left != NULL)
		{
			left->parent = NULL;
		}

		update(left);
		update(right);
	}

	Vertex* merge(Vertex* left, Vertex* right)
	{
		if (left == NULL)
			return right;
		if (right == NULL)
			return left;
		Vertex* min_right = right;
		while (min_right->left != NULL)
		{
			min_right = min_right->left;
		}
		splay(right, min_right);
		right->left = left;
		update(right);
		return right;
	}


	void insert(Vertex*& root, int k, Vertex*& subString)
	{
		Vertex* left = NULL;
		Vertex* right = NULL;
		split(root, k, left, right);
		root = merge(merge(left, subString), right);
	}

	std::string traversal_in_order(Vertex* root)
	{
		std::string printS = "";
		if (root == NULL)
		{
			return printS;
		}
		std::stack<Vertex*> S;
		Vertex* p = root;

		while (p != NULL)
		{
			S.push(p);
			p = p->left;
		}

		while (!S.empty())
		{
			p = S.top();
			printS.push_back(p->key);
			S.pop();
			p = p->right;
			while (p != NULL)
			{
				S.push(p);
				p = p->left;
			}

		}
		return printS;
	}

	void process(int i, int j, int k)
	{
		if (i > j)
		{
			int temp = i;
			i = j;
			j = temp;
		}
		Vertex* left = NULL;
		Vertex* right = NULL;
		Vertex* middle = NULL;
		split(root, i + 1, left, middle);
		split(middle, j - i + 2, middle, right);
		root = merge(left, right);
		insert(root, k + 1, middle);
	}

	std::string result()
	{
		s.clear();
		s = traversal_in_order(root);
		return s;
	}

	unsigned int length() {
		return result().length();
	}

	char index(const unsigned int i) {
		const char c = result().at(i);
		return c;
	}

	std::string Rope::report(unsigned int start, unsigned int end) {
		std::string str = result();
		return str.substr(s + start, end - start);
	}

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

struct test_controller {
  bool enabled;
  std::string label;
  int points;
  bool ok;
  bool run;
  int &out;
  test_controller(bool enabled, std::string &&label, int points, int &out)
      : enabled(enabled), label(std::move(label)), points(points), ok(true),
        run(true), out(out) {
    if (enabled) {
      std::cout << ">>> Test: " << this->label << " (" << points << ")"
                << std::endl;
    }
  }
  ~test_controller() {
    if (enabled) {
      out += ok ? points : 0;
      std::cout << ">>> Result: " << (ok ? "PASS" : "FAIL") << std::endl;
    }
  }
};

struct measurement_controller {
  std::string name;
  std::chrono::nanoseconds &out;
  std::chrono::time_point<std::chrono::high_resolution_clock> start;
  bool run;
  measurement_controller(std::string &&name, std::chrono::nanoseconds &out)
      : name(std::move(name)), out(out),
        start(std::chrono::high_resolution_clock::now()), run(true) {}
  ~measurement_controller() {
    auto stop = std::chrono::high_resolution_clock::now();
    out = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::cout << name << ": " << out.count() << "ns" << std::endl;
  }
};

#define TEST(label, points)                                                    \
  for (test_controller cntr(++counter == test_no || test_no == 0, label,       \
                            points, total);                                    \
       cntr.run; cntr.run = false)

#define CHECK_EQ(val, expr)                                                    \
  if (cntr.ok) {                                                               \
    try {                                                                      \
      cntr.ok = val == (expr);                                                 \
    } catch (...) {                                                            \
      cntr.ok = false;                                                         \
      std::cout << ">>> unexpected exception" << std::endl;                    \
    }                                                                          \
    if (!cntr.ok) {                                                            \
      std::cout << ">>> " << #val << " == " << #expr << " failed at "          \
                << __LINE__ << " Expr result: " << (expr) << std::endl;        \
    }                                                                          \
  }

int main(int argc, char *argv[]) {
  int test_no = 0;
  int counter = 0;
  int total = 0;
  srand(time(nullptr));
  if (argc == 2) {
    test_no = std::atoi(argv[1]);
  }

  TEST("Create an empty tree. Length should be 0.", 2) {
    Rope rope;
    CHECK_EQ(0, rope.length());
  }

//  TEST("Create a non empty tree. Text should be the same.", 3) {
//    Rope rope("The quick brown fox jumps over the lazy dog.");
//    CHECK_EQ("The quick brown fox jumps over the lazy dog.", rope.report(0, 44));
//  }

  std::cout << ">>> TOTAL POINTS: " << total << std::endl;
  return 0;
}

