#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <map>

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

	inline uint32_t get_width() const { return m_width; }

	inline uint32_t get_height() const { return m_height; }

	/**
	 * @brief  
	 * 
	 * @param x between 0 and m_width-1
	 * @param y between 0 and height-1
	 * @return double The value of the Gradient at that point regarding the point foward(+) , backward(-) or both(0)
	 */
	double gradient_x(uint32_t x,uint32_t y, char s);


	/**
	 * @brief  
	 * 
	 * @param x between 0 and m_width-1
	 * @param y between 0 and height-1
	 * @return double The value of the Gradient at that point regarding the point upward(+) , downward(-) or both(0)
	 */
	double gradient_y(uint32_t x,uint32_t y, char s);

	/**
	 * @brief  
	 * I created this map in order to know all the points that value 0 and its respective coordinates
	 * This is very useful to calculate C+ and C- 
	 * 
	 * @return A map of points 0 or 1 , that show us the coordinates of the GridFunction where they assume each value
	 * 
	 */
	std::map<uint32_t,std::vector<std::pair< uint32_t, uint32_t>>> Inside_Outside() const;



	/**
	 * @brief 
	 * THE ACTUAL FUNCTION AND THE GRIDFUNCTION NEED TO HAVE THE SAME WIDTH AND HEIGHT OTHERWISE IT WILL NOT WORK
	 * 
	 * @return The value o C+ defined in the article 
	 * 
	 */
	double C_positive(const GridFunction &phi) const;


	/**
	 * @brief  
	 * THE ACTUAL FUNCTION AND THE GRIDFUNCTION NEED TO HAVE THE SAME WIDTH AND HEIGHT OTHERWISE IT WILL NOT WORK
	 * 
	 * @return The value o C- defined in the article  
	 * 
	 */
	double C_negative(const GridFunction &phi) const;


	// FIRSt WAY OF SOLVING THE EQUATIONS:

	/**
	 * All the techniques down here help us to implement the article in using the explict way of solving the EDP, it means
	 * For all the terms related to the time (n+1) we will substitute by (n) except for the term defining a differencial in time(left side)
	 * 
	 */



	/**
	 * @brief  
	 * Tool to some and subtract GridFunction and still have a GridFunction, it is used to 
	 * 
	 * @return We gonna implement the Nabla_operator, and return a GridFunction made of finite difference between the elements , regarding the foward elements
	 *  
	 */
	GridFunction Gradient_x_pos();

	/**
	 * @brief  
	 * Tool to some and subtract GridFunction and still have a GridFunction, it is used to 
	 * 
	 * @return We gonna implement the Nabla_operator, and return a GridFunction made of finite difference between the elements , regarding the backward elements
	 * 
	 */
	GridFunction Gradient_x_neg();

	/**
	 * @brief  
	 * Tool to some and subtract GridFunction and still have a GridFunction
	 * 
	 * @return We gonna implement the Nabla_operator, and return a GridFunction made of finite difference between the elements , regarding the backward and foward elements
	 * 
	 */
	GridFunction Gradient_x_neu();


	/**
	 * @brief  
	 * Tool to square and take the root of a GridFunction very useful to solve the EDP equation
	 * 
	 * @return GridFunction where all the value in (x,y) are now to the power of x
	 * 
	 */
	GridFunction operator ^ (double x);

	/**
	 * @brief  
	 * Tool to divide GridFunction used for solving the EDP equation
	 * 
	 * @return GridFunction where all the value in (x,y) are now divided by the value of the other GridFunction in (x,y)
	 */
	GridFunction operator /(GridFunction phi_2);



	// SECOND WAY OF SOLVING THE EQUATIONS:
	
	/**
	 * @brief On the images stored in a computer, the (0,0) point typically corresponds to the top-left corner instead of the bottom-left corner like in mathematics. Use this function to return the image around its x axis
	 * 
	 */
	void reverse_y();

	/**
	 * @brief  
	 * 
	 * @param x between 0 and width-1
	 * @param y between 0 and height-1
	 * @return double& The value of the function at that point
	 */
	inline double operator()(uint32_t x, uint32_t y) const
	{
		return m_data[x + y*m_width];
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
		return m_data[x + y*m_width];
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

	bool save_with_colored_border(const std::string &path, double border_r=0.0, double border_g=1.0, double border_b=0.0, uint32_t border_width=3);

private:
	void clear();
	void construct_constant(uint32_t width, uint32_t height, double base_value);

	uint32_t m_width = 0, m_height = 0;
	std::vector<double> m_data;

};

/**
 * @brief Create a [img_size x img_size] [inside_color] circle inside a [outside_color] rectangle. The circle's diameter is [diam_percent x img_size]
 * 
 * @param width 
 * @param height 
 * @param outside_color 
 * @param inside_color 
 * @return GridFunction 
 */
GridFunction create_circle_image(uint32_t img_size, double diam_percent=1.0, double outside_color = 0.0, double inside_color = 1.0);

GridFunction create_sin_image(uint32_t width, uint32_t height, double frequency, double range_min, double range_max);
