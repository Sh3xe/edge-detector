#include "EdgeDetector.hpp"

#include <cmath>
#include <iostream>
#include <cassert>

GridFunction EdgeDetector::solve(const GridFunction &image)
{
	double tho=1e10;
	size_t current_iteration = 0;

	GridFunction phi_current = create_sin_image(image.get_width(), image.get_height(), 30.0, 0.0, 1.0);

	GridFunction phi_new(phi_current);

	while(tho > m_parameters.tolerance && current_iteration < m_parameters.max_iterations)
	{
		// Compute C-, and C+
		double c_positive = image.C_positive(phi_current);
		double c_negative = image.C_negative(phi_current);

		// Use euler method for 
		phi_new = calc_step(phi_current,image,c_positive,c_negative,phi_new);

		// Calculate the error
		tho = img_distance(discretize_colors(phi_current), discretize_colors(phi_new));

		// One step
		++current_iteration;
		phi_current = phi_new;

		// Log the result if required
		if(m_parameters.log_iterations && current_iteration % 5 == 0)
		{
			std::cout << "Iteration: " << current_iteration << "/" << m_parameters.max_iterations << ". ";
			std::cout << "Distance between consecutive iterations: " << tho << std::endl;

			if(m_parameters.save_iter)
			{
				phi_new.save_to_pgm("inter" + std::to_string(current_iteration) + std::string(".pgm"));
			}
		}
	}

	std::cout << "Number of iterations: " << current_iteration << " " << tho << " " << m_parameters.tolerance << std::endl;

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

GridFunction EdgeDetector::calc_step(const GridFunction &phi_old,const GridFunction &image,double C_positive,double C_negative,GridFunction &phi)
{
	// Inside
	for(uint32_t i=1;i<phi.get_width()-1;i++)
	{
		for(uint32_t j=1;j<phi.get_height()-1;j++)
		{
			double v1 = m_parameters.mu*phi_old.gradient_x(i,j,'+');
			double v2 = sqrt(4*pow(phi_old.gradient_y(i,j,'0'),2)+pow(phi_old.gradient_x(i,j,'+'),2)+pow(m_parameters.eta,2));

			double v3 = m_parameters.mu*phi_old.gradient_x(i-1,j,'+');
			double v4 = sqrt(4*pow(phi_old.gradient_y(i-1,j,'0'),2)+pow(phi_old.gradient_x(i-1,j,'+'),2)+pow(m_parameters.eta,2));

			double v5 = v1/v2 - v3/v4;

			double w1 = m_parameters.mu*phi_old.gradient_y(i,j,'+');
			double w2 = sqrt(4*pow(phi_old.gradient_x(i,j,'0'),2)+pow(phi_old.gradient_y(i,j,'+'),2)+pow(m_parameters.eta,2));

			double w3 = m_parameters.mu*phi_old.gradient_y(i-1,j,'+');
			double w4 = sqrt(4*pow(phi_old.gradient_x(i-1,j,'0'),2)+pow(phi_old.gradient_y(i-1,j,'+'),2)+pow(m_parameters.eta,2));

			double w5 = w1/w2 - w3/w4;

			double z = m_parameters.v + m_parameters.lambda_1*pow(image(i,j)-C_negative,2) - m_parameters.lambda_2*pow(image(i,j)-C_positive,2);

			phi(i,j)  = abs(phi_old(i,j) + m_parameters.delta_t * Dirac(m_parameters,phi_old(i,j))*(v5+w5-z));
		}
	}

	// Borders
	for(uint32_t i=0;i<phi.get_width();i++)
	{
		phi(i,0) = phi(i,1);
		phi(i,phi.get_height()-1) = phi(i,phi.get_height()-2);
	}

	for(uint32_t j=0;j<phi.get_height();j++)
	{
		phi(0,j) = phi(1,j);
		phi(phi.get_width()-1,j) = phi(phi.get_width()-2,j);
	}

	return phi;
}