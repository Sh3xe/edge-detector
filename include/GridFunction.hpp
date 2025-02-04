#pragma once

#include <cstdint>
#include <string>
#include <vector>

/**
 * @brief Represents a scalar function [-1,1]x[-1,1] -> R
 * 
 */
class GridFunction
{
public:
	GridFunction(uint32_t width, uint32_t height, double base_value = 0.0f);

	/**
	 * @brief Construct a new Scalar function from a grayscale pgm file, rescale its width and height for more precise grid size if needed
	 * 
	 * @param pgm_file_path 
	 * @param rescale_width internal grid width of the function
	 * @param rescale_height internal grid height of the function
	 */
	GridFunction(const std::string &pgm_file_path, uint32_t rescale_width, uint32_t rescale_height);

	/**
	 * @brief Construct a new Scalar function from a grayscale pgm file, inherits the image's width and height
	 * 
	 * @param pgm_file_path
	 */
	GridFunction(const std::string &pgm_file_path);

	inline const uint32_t get_width() const { return m_width; }

	inline const uint32_t get_height() const { return m_height; }

	double gradient_x(double x,double y, int a=1);

	double gradient_x(double x,double y);

	double gradient_y(double x,double y, int a=1);

	double gradient_y(double x,double y);

	/**
	 * @brief  
	 * 
	 * @param x between 0 and width-1
	 * @param y between 0 and height-1
	 * @return double& The value of the function at that point
	 */
	inline double operator()(uint32_t x, uint32_t y) const
	{
		return m_data[x + y*m_height];
	}

	/**
	 * @brief  
	 * 
	 * @param x between 0 and width-1
	 * @param y between 0 and height-1
	 * @return double& The value of the function at that point, can be modified
	 */
	inline double &operator()(uint32_t x, uint32_t y)
	{
		return m_data[x + y*m_height];
	}

	/**
	 * @brief Save the function to a pgm grayscale image
	 * 
	 * @param path 
	 * @return true in case of success
	 * @return false in case of failure
	 */
	bool save_to_pgm(const std::string &path);

	/**
	 * @brief Loads the function from a pgm grayscale image
	 * 
	 * @param path 
	 * @return true in case of success
	 * @return false in case of failure
	 */
	bool load_from_pgm(const std::string &path);

private:
	void clear();
	void construct_constant(uint32_t width, uint32_t height, double base_value);

	uint32_t m_width = 0, m_height = 0;
	std::vector<double> m_data;
};