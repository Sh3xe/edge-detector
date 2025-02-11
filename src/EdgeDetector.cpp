#include "EdgeDetector.hpp"

#include <cmath>
#include <cassert>

GridFunction EdgeDetector::solve(const GridFunction &image, size_t max_iteration)
{
	double tho=1e10;
	size_t current_iteration = 0;

	GridFunction phi_current = create_sin_image(image.get_width(), image.get_height(), 30.0, 0.0, 1.0);

	while(tho < m_parameters.tolerance && current_iteration < max_iteration)
	{
		// Compute C-, and C+
		double c_positive = image.C_positive(phi_current);
		double c_negative = image.C_negative(phi_current);

		// Use euler method for 
		GridFunction phi_new = calc_step(phi_current, c_positive, c_negative);

		// Calculate the error
		tho = img_distance(phi_current, phi_new);

		// One step
		++current_iteration;
		phi_current = phi_new;
	}

	return phi_current;
}

double EdgeDetector::img_distance(const GridFunction &left, const GridFunction &right)
{
	assert(left.get_height() == right.get_height() && left.get_width() == right.get_width());

	double integral = 0.0;
	for(size_t i = 0; i < left.get_width(); ++i)
	for(size_t j = 0; j < left.get_height(); ++j)
	{
		double diff = right(i,j) - left(i,j);
		integral += diff*diff;
	}

	return sqrt(integral);
}

GridFunction EdgeDetector::calc_step(const GridFunction &phi_old, double c_positive, double c_negative)
{

}