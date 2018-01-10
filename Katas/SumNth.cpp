#include "stdafx.h"

#include <sstream>
#include <iomanip>

#include "SumNth.h"


std::string SumNth::seriesSum(int n) {
	double res = 0.0;
	double denom = 1.0;
	for (int i = 0; i < n; ++i) {
		res += 1 / denom;
		denom += 3.0;
	}

	//int res1 = static_cast<int>(res);
	//int res2 = static_cast<int>((res - res1) * 100);
	//std::string ret = std::to_string(res1) + "." + std::to_string(res2);

	std::stringstream ret;
	ret << std::fixed << std::setprecision(2) << res;
	return ret.str();
}