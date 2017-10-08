// 0-1 knapsack common routines
//
// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include "matrix.hpp"
#include <utility>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>

template<typename T, typename V, class Weight, class Value>
void knapsack_impl(Matrix<V>& m, Weight weight_func, Value value_func)
{
	static_assert(sizeof(T) <= sizeof(std::size_t), "Type is too large");
	assert(m.rows() >= 1 && m.cols() >= 1);

	const auto max_weight = static_cast<T>(m.rows() - 1);
	const auto n = static_cast<T>(m.cols() - 1);

	for (T i = 0; i <= max_weight; ++i)
		m(i, 0) = 0;

	for (T j = 0; j <= n; ++j)
		m(0, j) = 0;

	for (T j = 1; j <= n; ++j)
	{
		const auto weight = weight_func(j - 1);
		const auto value = value_func(j - 1);

		for (T i = 1; i <= max_weight; ++i)
		{
			m(i, j) = m(i, j - 1);
			if (weight <= i)
				m(i, j) = std::max(m(i, j), m(i - weight, j - 1) + value);
		}
	}
}

template<typename T, class Weight, class Value>
std::result_of_t<Value(T)>
	knapsack_max_value(T n, T max_weight, Weight weight_func, Value value_func)
{
	using V = std::result_of_t<Value(T)>;
	Matrix<V> m(max_weight + 1, n + 1);

	knapsack_impl<T>(m, weight_func, value_func);
	return m(max_weight, n);
}

template<typename T, class Weight, class Value>
std::pair<std::result_of_t<Value(T)>, std::vector<T>>
	knapsack_max_value_and_items(T n, T max_weight, Weight weight_func, Value value_func)
{
	using V = std::result_of_t<Value(T)>;
	Matrix<V> m(max_weight + 1, n + 1);

	knapsack_impl<T>(m, weight_func, value_func);

	std::vector<T> items;
	for (auto i = max_weight, j = n; j > 0; --j)
		if (m(i, j) > m(i, j - 1))
		{
			items.push_back(j - 1);
			i -= weight_func(j - 1);
		}

	std::reverse(items.begin(), items.end());
	return {m(max_weight, n), items};
}