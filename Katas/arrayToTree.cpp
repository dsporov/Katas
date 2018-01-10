#include "stdafx.h"

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <deque>

#include <numeric>

#include <assert.h>

/*
You are given a non - null array of integers.
Implement the method arrayToTree which creates a binary tree from its values in accordance to their order, while creating nodes by depth from left to right.

For example, given the array[17, 0, -4, 3, 15] you should create the following tree :

17
/ \
0 - 4
/ \
3   15
The class TreeNode is available for you :

class TreeNode
{
public:
TreeNode(int value, TreeNode* left, TreeNode* right)
: m_value(value), m_left(left), m_right(right)
{
}

TreeNode(int value)
: m_value(value), m_left(NULL), m_right(NULL)
{
}

bool operator==(const TreeNode& rhs) const
{
... // Already implemented for you and used in test cases
}
...
}
*/

class TreeNode {
public:
	TreeNode(int value, TreeNode* left, TreeNode* right)
		: m_value(value), m_left(left), m_right(right)
	{
	}

	TreeNode(int value)
		: m_value(value), m_left(NULL), m_right(NULL)
	{
	}

	//private:
	int m_value;
	TreeNode *m_left;
	TreeNode *m_right;
};


/// class Solution
class Solution {
public:
	static TreeNode* arrayToTree3(std::vector<int> arr)
	{
		std::deque<TreeNode**> deck;
		TreeNode *root;
		deck.push_back(&root);
		for (int i = 0; i<arr.size(); i++) {
			TreeNode **next = deck.front();
			*next = new TreeNode(arr[i]);
			deck.push_back(&(*next)->m_left);
			deck.push_back(&(*next)->m_right);
			deck.pop_front();
		}
		return arr.size() == 0 ? nullptr : root;
	};

	static TreeNode *GetTreeNode(std::vector<int> const& arr, size_t idx) {
		size_t n = arr.size();
		if (idx >= n)
			return nullptr;

		int level = log2(idx + 1);
		int firstRowElIdx = pow(2, level) - 1;
		int idxLevel = idx - firstRowElIdx;

		int idxNext = firstRowElIdx * 2 + 1;
		int idxLevelNext = idxLevel * 2;

		size_t idxLeft = idxNext + idxLevelNext;
		size_t idxRight = idxLeft + 1;

		return new TreeNode(arr[idx],
			GetTreeNode(arr, idxLeft),
			GetTreeNode(arr, idxRight)
		);
	}

	static TreeNode *GetTreeNode2(std::vector<int> const& arr, size_t idx) {
		if (idx >= arr.size())
			return nullptr;

		size_t idxLeft = idx * 2 + 1;
		size_t idxRight = idxLeft + 1;

		return new TreeNode(arr[idx],
			GetTreeNode(arr, idxLeft),
			GetTreeNode(arr, idxRight)
		);
	}

	static TreeNode* arrayToTree2(std::vector<int> arr) {
		//if (arr.empty())
		//	return nullptr;

		//TreeNode *top = new TreeNode(arr.front(),
		//	GetTreeNode(arr, 1),
		//	GetTreeNode(arr, 2)
		//);

		//return top;
		return GetTreeNode2(arr, 0);
	}

	static TreeNode* arrayToTree(std::vector<int> arr) {
		std::vector<TreeNode*> curLevel;
		std::vector<TreeNode*> prevLevel;

		if (arr.empty())
			return nullptr;

		TreeNode *top = new TreeNode(arr.front());
		prevLevel.push_back(top);

		size_t levelIdx = 0;
		for (size_t i = 1; i < arr.size(); ++i) {
			curLevel.push_back(new TreeNode(arr[i]));
			if ((i % 2) != 0) {
				prevLevel[levelIdx]->m_left = curLevel.back();
			}
			else {
				prevLevel[levelIdx]->m_right = curLevel.back();
				++levelIdx;
			}

			if (levelIdx >= prevLevel.size()) {
				levelIdx = 0;
				std::swap(prevLevel, curLevel);
				curLevel.clear();
			}
		}

		return top;
	}

private:
	static TreeNode* arrayToTreeImpl(std::vector<int> &arr) {
		std::reverse(std::begin(arr), std::end(arr));
		if (arr.empty())
			return nullptr;

		int v = arr.back();
		arr.pop_back();

		new TreeNode(v);
	}
};

void test_arrayToTree() {
	for (size_t i = 0; i < 18; ++i) {
		int level = log2(i + 1);
		int firstRowElIdx = pow(2, level) - 1;
		int idxLevel = i - firstRowElIdx;

		int idxNext = firstRowElIdx * 2 + 1;
		int idxLevelNext = idxLevel * 2;

		std::cout << level << " " << idxLevel << " " << idxNext + idxLevelNext << "\n";
	}

	std::vector<int> arr = { 17, 0, -4, 3, 15 };
	TreeNode* expected = new TreeNode(17, new TreeNode(0, new TreeNode(3), new TreeNode(15)), new TreeNode(-4));

	Solution::arrayToTree3(arr);
}
