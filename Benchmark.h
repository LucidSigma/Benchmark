#pragma once
#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <string>
#include <utility>

template<unsigned int Count>
class Benchmark
{
private:
	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = std::chrono::high_resolution_clock::time_point;
	using Milliseconds = std::chrono::milliseconds;

	std::string name;

	double totalTime;
	double averageTime;
	double minTime;
	double maxTime;

public:
	template<typename Function, typename... Args>
	Benchmark(const std::string& name, Function function, Args... parameters)
		: name(name)
	{
		long long total = 0;
		std::array<long long, Count> times;

		for (unsigned int i = 0; i < Count; i++)
		{
			TimePoint beginTime = Clock::now();

			function(std::forward<Args>(parameters)...);

			TimePoint endTime = Clock::now();

			Milliseconds milliseconds = std::chrono::duration_cast<Milliseconds>(endTime - beginTime);

			total += milliseconds.count();
			times[i] = milliseconds.count();
		}

		totalTime = static_cast<double>(total);
		averageTime = totalTime / static_cast<double>(Count);
		minTime = static_cast<double>(*std::min_element(times.cbegin(), times.cend()));
		maxTime = static_cast<double>(*std::max_element(times.cbegin(), times.cend()));
	}

	void DisplayResults() const
	{
		std::cout << "Results for benchmark:   " << name << "\n";
		std::cout << "====================================================\n";
		std::cout << "Total times benchmarked: " << Count << "\n";
		std::cout << "Total time:              " << totalTime << "ms\n";
		std::cout << "Average time:            " << averageTime << "ms\n";
		std::cout << "Minimum time:            " << minTime << "ms\n";
		std::cout << "Maximum time:            " << maxTime << "ms\n";
		std::cout << "Range:                   " << (maxTime - minTime) << "ms\n";
		std::cout << "====================================================" << std::endl;
	}
};

#endif
