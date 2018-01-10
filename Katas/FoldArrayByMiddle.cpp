#include "stdafx.h"
#include "FoldArrayByMiddle.h"


FoldArrayByMiddle::FoldArrayByMiddle() {
}

FoldArrayByMiddle::~FoldArrayByMiddle() {
}

std::vector<int> FoldArrayByMiddle::Fold(std::vector<int> array, int runs) {
	for (; runs > 0; --runs) {
		const size_t idxMiddle = array.size() / 2;
		const size_t idx1 = 0;
		const size_t idx2 = array.size() - 1;

		for (size_t i = idx1, j = idx2; i < idxMiddle; ++i, --j) {
			array[i] += array[j];
		}

		array.resize((array.size() + 1) / 2);
	}

	return array;
}


