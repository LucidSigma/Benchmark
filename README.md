# Benchmark C++ Header
Runs a function multiple times and times how long it takes.

Requires a C++17 compiler.

---

## Usage
Create the benchmark class template with the template parameter being the amount of times to benchmark the function.

Constructor arguments:
**name** - the name to give the benchmark
**function** - the function to benchmark
**parameters** - a parameter pack to contain the arguments of the function

Call the DisplayResults function to display the results of the benchmark.

#### Example
This will create a benchmark that runs 100 times called *Test Benchmark*.
The benchmark will test the function **TestFunction** with the parameters 3 and 5.

```cpp
#include "Benchmark.h"

int TestFunction(int a, int b) noexcept
{
	for (int i = 0; i < 1'000'000; i++)
	{
		a += b;
	}

	return a;
}

int main(int argc, const char* argv[])
{
	Benchmark<100> benchmark("Test Benchmark", TestFunction, 3, 5);
	benchmark.DisplayResults();

	return 0;
}
```

**Example output**
```
Results for benchmark:   Test Benchmark
====================================================
Total times benchmarked: 100
Total time:              100ms
Average time:            1ms
Minimum time:            1ms
Maximum time:            1ms
Range:                   0ms
====================================================
```