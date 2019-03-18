#pragma once
#include <chrono>
#include <ctime>
#include <string>
#include "Common.hh"


class Timer {
public:
	Timer(std::string name)
		: start(std::chrono::high_resolution_clock::now()), name(name)
	{}

	~Timer()
	{
		auto end = std::chrono::high_resolution_clock::now();
		LOG(INFO) << name << ':' <<
			std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()
			<< " ms" << '\n';
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	std::string name;
};
