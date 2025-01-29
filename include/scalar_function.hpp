#pragma once

#include <cstdint>
#include <string>
#include <vector>

/**
 * @brief Represents a scalar function [-1,1]x[-1,1] -> R
 * 
 */
class ScalarFunction
{
public:

	ScalarFunction(uint32_t width, uint32_t height, float base_value = 0.0f);

	ScalarFunction(const std::string &pgm_file_path);

	/**
	 * @brief  
	 * 
	 * @param x in [-1,1]
	 * @param y in [-1,1]
	 * @return float& The value of the function at that point
	 */
	float &operator()(float x, float y);

	/**
	 * @brief  
	 * 
	 * @param x in [-1,1]
	 * @param y in [-1,1]
	 * @return float& The value of the function at that point
	 */
	float operator()(float x, float y) const;

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
	void construct_constant(uint32_t width, uint32_t height, float base_value);

	uint32_t m_width = 0, m_height = 0;
	std::vector<float> m_data;
};