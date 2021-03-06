/*********************************************************************
Wetlands of Florida
-------------------
UVa ID: 004 69

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include "position.hpp"
#include <array>
#include <cassert>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using Landscape = Matrix<bool>;

class Flood_fill_area
{
public:
	Flood_fill_area(const Landscape& landscape) : landscape_(landscape)
	{
		visited_.resize(landscape_.rows(), landscape_.cols());
	}

	std::size_t flood_fill_area(const Position pos) const
	{
		assert(is_inside_extents(landscape_, pos) && landscape_(pos));

		visited_.fill(false);
		return flood_fill_area_impl(pos);
	}

private:
	std::size_t flood_fill_area_impl(const Position pos) const
	{
		visited_(pos) = true;

		std::size_t area = 1;
		for (auto new_pos : eight_neighbours(pos))
			if (is_inside_extents(landscape_, new_pos) && !visited_(new_pos) && landscape_(new_pos))
				area += flood_fill_area_impl(new_pos);

		return area;
	}

	static std::array<Position, 8> eight_neighbours(const Position pos)
	{
		std::array<Position, 8> neighbours = {
			{{-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}}};

		for (auto& neighbour : neighbours)
			neighbour += pos;

		return neighbours;
	}

private:
	const Landscape& landscape_;
	mutable Landscape visited_;
};

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		if (wet_landscape_.rows() == 0)
			ignore_line();

		std::string str;
		std::vector<std::vector<bool>> landscape;

		queries_.clear();
		while (read_ln_non_empty(str))
		{
			if (str.front() == 'L' || str.front() == 'W')
			{
				std::vector<bool> line;
				for (auto c : str)
					line.push_back(c == 'W');
				landscape.push_back(std::move(line));
			}
			else
			{
				Position pos;
				std::istringstream ss(str);
				ss >> pos.col >> pos.row; // Matrix (wet_landscape_) is transposed on construction
				pos.to_zero_based();
				queries_.push_back(pos);
			}
		}

		wet_landscape_ = Landscape{landscape};
	}

	virtual void solve(unsigned int i_case) override
	{
		if (i_case > 1)
			write_ln();

		const Flood_fill_area wetland(wet_landscape_);
		for (auto q : queries_)
			write_ln(wetland.flood_fill_area(q));
	}

private:
	Landscape wet_landscape_;
	std::vector<Position> queries_;
};

MAIN
