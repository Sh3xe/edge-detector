#pragma once

#include "Parameters.hpp"
#include "GridFunction.hpp"

class EdgeDetector
{
public:
	EdgeDetector(const GridParameters &parameters)
		: m_parameters(parameters)
	{}

	/**
	 * @brief Detect the edge of image
	 * 
	 * @param image A grayscale image
	 * @param max_iteration
	 * @return GridFunction An image that only takes 2 values: c- in [0,1] if the pixel is considered inside the edge, and c+ in [0,1] if the pixel is outside. c+ and c- may change depending on the image fed to the algorithm.
	 */
	GridFunction solve(const GridFunction &image, size_t max_iteration=100);

private:
	/**
	 * @brief Calculate the euclidian distance between image left and right
	 * 
	 * @param left 
	 * @param right 
	 * @return double euclidian distance between left and right
	 */
	double img_distance(const GridFunction &left, const GridFunction &eight);

	/**
	 * @brief 
	 * 
	 * @param phi_old 
	 * @return GridFunction 
	 */
	GridFunction calc_step(const GridFunction &phi_old, double c_positive, double c_negative);

	GridParameters m_parameters;
};