#include <fstream>
#include <cassert>
#include <iostream>

# include "../include/scalar_function.hpp"

ScalarFunction::ScalarFunction(uint32_t width, uint32_t height, float base_value)
{
	construct_constant(width, height, base_value);
}
	
ScalarFunction::ScalarFunction(const std::string &pgm_file_path)
{
	if(!load_from_pgm(pgm_file_path))
		construct_constant(128, 128, 0.0f);
}

float &ScalarFunction::operator()(float x, float y)
{
	assert(x <= 1.0f && x >= -1.0f);
	assert(y <= 1.0f && y >= -1.0f);

	float x_pxl_coord = (x + 1.0f) * ((float)m_width/2.0f);
	float y_pxl_coord = (y + 1.0f) * ((float)m_height/2.0f);
	
	return m_data[(int)y_pxl_coord *m_height + (int)x_pxl_coord];
}

float ScalarFunction::operator()(float x, float y) const
{
	assert(x <= 1.0f && x >= -1.0f);
	assert(y <= 1.0f && y >= -1.0f);

	float x_pxl_coord = (x + 1.0f) * ((float)m_width/2.0f);
	float y_pxl_coord = (y + 1.0f) * ((float)m_height/2.0f);

	return m_data[(int)y_pxl_coord *m_height + (int)x_pxl_coord];
}

bool ScalarFunction::save_to_pgm(const std::string &path)
{
	std::fstream file {path, std::ios::out};

	if( !file )
	{
		std::cout << "Cannot open: \"" << path << "\"" << std::endl;
		return false;
	}

	file << "P2\n";
	file << m_width << " " << m_height << " " << 255 << "\n";

	for( int j  = 0; j < m_height; j++) {
		for( int i  = 0; i < m_width; i++) {
			file << (int)(m_data[j*m_height + i] * 255) << " ";
		}
		file << "\n";
	}

	return true;
}

bool ScalarFunction::load_from_pgm(const std::string &path)
{
	std::fstream file {path};
	
	if(!file)
	{
		std::cout << "Cannot open path: \"" << path << "\"" << std::endl; 
		return false;
	}

	std::string btm_format;
	int interval = 255, width = 0, height = 0;

	file >> btm_format >> width >> height >> interval;

	bool is_rgb = false;
	if( btm_format == "P3" )
		is_rgb = true;

	this->construct_constant(width, height, 0.0f);

	if( is_rgb )
	{
		for( int j = 0; j < height; j++) {
			for( int i = 0; i < width; i++) {
				int pixel;
				file >> pixel;
				m_data[i+j*width] = (float)pixel / (float)interval;
			}
		}
	}
	else
	{
		for( int j = 0; j < height; j++) {
			for( int i = 0; i < width; i++) {
				int r, g, b;
				file >> r >> g >> b;
				m_data[i+j*width] = ((float)r / (float)interval) * 0.3 + ((float)g / (float)interval) * 0.59 + ((float)b / (float)interval) * 0.11;
			}
		}
	}

	file.close();
	return true;
}

void ScalarFunction::clear()
{
	m_data.clear();
	m_width = 0;
	m_height = 0;
}

void ScalarFunction::construct_constant(uint32_t width, uint32_t height, float base_value = 0.0f)
{
	this->clear();

	m_width = width;
	m_height = height;
	m_data.resize(width*height, base_value);
}