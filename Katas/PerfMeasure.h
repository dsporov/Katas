#pragma once

#include <string>
#include <iostream>

#include <windows.h>
#undef min
#undef max

class PerfMeasure {
public:
	PerfMeasure(std::string const& msg) : m_msg(msg) {
		QueryPerformanceCounter(&t1);
	}

	~PerfMeasure() {
		QueryPerformanceCounter(&t2);
		QueryPerformanceFrequency(&c);
		int msec = (int)((t2.QuadPart - t1.QuadPart) / double(c.QuadPart) * 1000);
		std::cout << m_msg << " execution time measurement: " << msec << "\n";
	}

private:
	std::string m_msg;
	LARGE_INTEGER t1, t2, c;
};

