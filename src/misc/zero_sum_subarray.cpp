/*********************************************************************
Zero-sum subarray
-----------------

Count the number of zero-sum contiguous subarrays in the given array.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cstddef>
#include <iterator>
#include <unordered_map>
#include <vector>

template<class It>
std::size_t count_zero_sums(It first, const It last)
{
	using T = typename std::iterator_traits<It>::value_type;
	std::unordered_map<T, std::size_t> sums;

	auto sum = T{0};
	sums.insert(std::make_pair(sum, 1));

	std::size_t count = 0;
	while (first != last)
	{
		sum += *first++;
		count += sums[sum]++;
	}

	return count;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(seq_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(count_zero_sums(seq_.begin(), seq_.end()));
	}

private:
	std::vector<int> seq_;
};

MAIN
