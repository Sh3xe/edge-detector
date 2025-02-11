#pragma once

#include "Parameters.hpp"
#include "GridFunction.hpp"

class EdgeDetector
{
public:
	EdgeDetector(const GridParameters &parameters)
		: m_parameters(parameters)
	{}

	GridFunction solve(const GridFunction &image, size_t max_iteration=100);

private:
	double calculate_error(const GridFunction &phi_old, const GridFunction &phi_new);

	GridFunction calc_step(const GridFunction &phi_old);

	GridParameters m_parameters;
};