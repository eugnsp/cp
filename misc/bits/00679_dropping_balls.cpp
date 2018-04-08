/*********************************************************************
Dropping balls
--------------
UVa ID: 006 79

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>

unsigned int get_ball_leaf(unsigned int d, unsigned int i)
{
	--i;

	unsigned int leaf = 1;
	while (--d)
	{
		leaf = 2 * leaf + (i % 2);
		i /= 2;
	}

	return leaf;
}

class CP : public CP1
{
private:
	virtual void read_input(std::istream& in) override
	{
		in >> d_ >> i_;
		assert(2 <= d_ && d <= 20 && 0 < i_ && i_ <= 524288);
	}

	virtual void solve(std::ostream& out, unsigned int) const override
	{
		out << get_ball_leaf(d_, i_) << '\n';
	}

private:
	unsigned int d_;
	unsigned int i_;
};

int main()
{
	CP p;
	return p.run();
}
