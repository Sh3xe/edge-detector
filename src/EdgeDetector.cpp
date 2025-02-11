#include "EdgeDetector.hpp"

GridFunction EdgeDetector::solve(const GridFunction &image, size_t max_iteration=100)
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
		GridFunction phi_new = calc_step(phi_current);

		// Calculate the error
		tho = calculate_error(phi_current, phi_new);

		// One step
		++current_iteration;
		phi_current = phi_current;
	}
}

double EdgeDetector::calculate_error(const GridFunction &phi_old, const GridFunction &phi_new)
{
	
}

GridFunction EdgeDetector::calc_step(const GridFunction &phi_old)
{

}