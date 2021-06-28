#include "stdafx.h"

#include <assert.h>
#include <queue>

namespace {
	struct ListNode {
		int val;
		ListNode *next;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr) {}
		ListNode(int x, ListNode *next) : val(x), next(next) {}
	};

	struct ValAndIndex {
		int value;
		int index;
		
		ValAndIndex() : value(0), index(-1) {};
		ValAndIndex(int v, int i) : value(v), index(i) {};

		bool operator<(ValAndIndex const& other) const {
			return value > other.value;
		}
	};

	ListNode* mergeKLists(std::vector<ListNode*>& lists) {
		ListNode* merged = nullptr;
		ListNode* lastMerged = nullptr;

		std::priority_queue<ValAndIndex> queue;
		for (int i = 0; i < lists.size(); ++i) {
			if (lists[i] != nullptr) {
				queue.push(ValAndIndex(lists[i]->val, i));
				lists[i] = lists[i]->next;
			}
		}

		while (!queue.empty()) {
			ValAndIndex valAndIndex = queue.top();
			queue.pop();

			if (lastMerged == nullptr) {
				merged = lastMerged = new ListNode(valAndIndex.value);
			}
			else {
				lastMerged->next = new ListNode(valAndIndex.value);
				lastMerged = lastMerged->next;
			}

			if (lists[valAndIndex.index] != nullptr) {
				queue.push(ValAndIndex(lists[valAndIndex.index]->val, valAndIndex.index));
				lists[valAndIndex.index] = lists[valAndIndex.index]->next;
			}

		};

		return merged;
	}

	ListNode* mergeKLists_solution1(std::vector<ListNode*>& lists) {
		ListNode *merged = nullptr;
		ListNode *lastMerged = nullptr;

		do {
			int minVal = std::numeric_limits<int>::max();

			size_t minListIdx = size_t(-1);
			for (size_t i = 0; i < lists.size(); ++i) {
				ListNode* node = lists[i];
				if (node == nullptr)
					continue;

				if (node->val < minVal) {
					minVal = node->val;
					minListIdx = i;
				}
			}

			if (minListIdx == size_t(-1))
				break;

			if (lastMerged == nullptr) {
				merged = lastMerged = new ListNode(minVal);
			} else {
				lastMerged->next = new ListNode(minVal);
				lastMerged = lastMerged->next;
			}

			lists[minListIdx] = lists[minListIdx]->next;

		} while(true);

		return merged;
	}

	bool verify_equal(ListNode *list1, ListNode *list2) {
		while (list1 != nullptr && list2 != nullptr) {
			if (list1->val != list2->val)
				return false;

			list1 = list1->next;
			list2 = list2->next;
		}

		return (list1 == nullptr) && (list2 == nullptr);
	}
}

void test_mergeKLists() {
	std::vector<ListNode*> lists = {
		new ListNode(1,
			new ListNode(4, 
				new ListNode(5))),
		new ListNode(1,
			new ListNode(3,
				new ListNode(4))),
		new ListNode(2,
			new ListNode(6))
	};
	bool result = verify_equal(mergeKLists(lists), new ListNode(1,
			new ListNode(1,
			new ListNode(2,
			new ListNode(3,
			new ListNode(4,
			new ListNode(4,
			new ListNode(5,
			new ListNode(6)
		)))))))
	);
	assert(result);
}
