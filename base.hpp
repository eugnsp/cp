// Base classes and general routines
// ---------------------------------
//
// This file is covered by the LICENSE file in the root of this project.

#pragma once

#ifdef ONLINE_JUDGE
#define NDEBUG
#endif

#include <cstddef>
#include <limits>
#include <iostream>
#include <cassert>

class CP1
{
public:
	int run()
	{
		std::ios_base::sync_with_stdio(false);
		std::cin.tie(nullptr);

		init();

		std::size_t n_test_cases;
		std::cin >> n_test_cases;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		for (std::size_t i = 0; i < n_test_cases; ++i)
		{
			read_input();
			assert(std::cin);
			solve(i);
		}

		return 0;
	}

protected:
	virtual void init()
	{ }
	
	virtual void read_input() = 0;
	virtual void solve(std::size_t) = 0;
};

class CP2
{
public:
	int run()
	{
		std::ios_base::sync_with_stdio(false);
		std::cin.tie(nullptr);

		init();
		
		std::size_t i = 0;
		while (read_input())
		{
			assert(std::cin);
			solve(i++);
		}

		return 0;
	}

protected:
	virtual void init()
	{ }
	
	virtual bool read_input() = 0;
	virtual void solve(std::size_t) = 0;
};
