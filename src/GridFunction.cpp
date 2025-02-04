#include "GridFunction.hpp"
#include "Parameters.hpp"

#include <fstream>
#include <cassert>
#include <iostream>
#include <cmath>

GridFunction::GridFunction(uint32_t width, uint32_t height, double base_value)
{
	construct_constant(width, height, base_value);
}
	
GridFunction::GridFunction(const std::string &pgm_file_path)
{
	if(!load_from_pgm(pgm_file_path))
	{
		std::cout << "Failed to load PGM Image, constructing empty 128x128 Image" << std::endl;
		construct_constant(128, 128, 0.0f);
	}
}

GridFunction::GridFunction(const std::string &pgm_file_path, uint32_t rescale_width, uint32_t rescale_height)
{
	GridFunction image(pgm_file_path);
	construct_constant(rescale_width, rescale_height, 0.0);

	for(uint32_t x = 0; x < m_width; ++x)
	for(uint32_t y = 0; y < m_height; ++y)
	{
		uint32_t x_img = ((double)(x * image.get_width()) / (double)m_width);
		uint32_t y_img = ((double)(y * image.get_height()) / (double)m_height);
		(*this)(x,y) = image(x_img, y_img);
	}
}

double GridFunction::gradient_x(double x,double y, int a)
{
	double Grad_x=0;

	if(x+a*eps>= 1.0f){
		Grad_x = ((*this)(x-a*eps,y)-( *this)(x,y))/(a*eps);
	}else{
		if(x+a*eps<= -1.0f){
			Grad_x = ((*this)(x-a*eps,y)-( *this)(x,y))/(a*eps);
		}else{
			Grad_x = ((*this)(x+a*eps,y)-( *this)(x,y))/(a*eps);
		}
	}

	return Grad_x;
}

double GridFunction::gradient_x(double x,double y)
{
	double Grad_x=0;

	if(x+eps>= 1.0f){
		Grad_x = ((*this)(x,y)-( *this)(x-eps,y))/(eps);
	}else{
		if(x+eps<= -1.0f){
			Grad_x = ((*this)(x,y)-( *this)(x,y))/(eps);
		}else{
			Grad_x = ((*this)(x+eps,y)-( *this)(x-eps,y))/(eps);
		}
	}
	return Grad_x;
}

double GridFunction::gradient_y(double x,double y,int a)
{
	double Grad_y=0;

	if(y+a*eps>= 1.0f){
		Grad_y = ((*this)(x,y-a*eps)-( *this)(x,y))/(a*eps);
	}else{
		if(y+a*eps<= -1.0f){
			Grad_y = ((*this)(x,y-a*eps)-( *this)(x,y))/(a*eps);
		}else{
			Grad_y = ((*this)(x,y+a*eps)-( *this)(x,y))/(a*eps);
		}
	}

	return Grad_y;
}

double GridFunction::gradient_y(double x,double y){
	double Grad_y=0;

	if(y+eps>= 1.0f){
		Grad_y = ((*this)(x,y)-( *this)(x,y-eps))/(eps);
	}else{
		if(y+eps<= -1.0f){
			Grad_y = ((*this)(x,y)-(*this)(x,y))/(eps);
		}else{
			Grad_y = ((*this)(x,y+eps)-( *this)(x,y-eps))/(eps);
		}
	}

	return Grad_y;
}

bool GridFunction::save_to_pgm(const std::string &path)
{
	std::fstream file {path, std::ios::out};

	if( !file )
	{
		std::cout << "Cannot open: \"" << path << "\"" << std::endl;
		return false;
	}

	file << "P2\n";
	file << m_width << " " << m_height << " " << 255 << "\n";

	for( uint32_t j  = 0; j < m_height; j++) {
		for( uint32_t i  = 0; i < m_width; i++) {
			file << (int)((*this)(i,j) * 255) << " ";
		}
		file << "\n";
	}

	return true;
}

bool GridFunction::load_from_pgm(const std::string &path)
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

	if( !is_rgb )
	{
		// Load grayscale image
		for( int i = 0; i < width; i++) {	
			for( int j = 0; j < height; j++) {
				int pixel;
				file >> pixel;
				(*this)(i,j) = (double)pixel / (double)interval;
			}
		}
	}
	else
	{
		// Load RGB image and convert to "human" grayscale (use different weights for r,g and b channels)
		for( int j = 0; j < height; j++) {
			for( int i = 0; i < width; i++) {
				int r, g, b;
				file >> r >> g >> b;
				(*this)(i,j) = ((double)r / (double)interval) * 0.3 + ((double)g / (double)interval) * 0.59 + ((double)b / (double)interval) * 0.11;
			}
		}
	}

	file.close();
	return true;
}

void GridFunction::clear()
{
	m_data.clear();
	m_width = 0;
	m_height = 0;
}

void GridFunction::construct_constant(uint32_t width, uint32_t height, double base_value = 0.0f)
{
	this->clear();

	m_width = width;
	m_height = height;
	m_data.resize(width*height, base_value);
}

void GridFunction::reverse_y()
{
	for(uint32_t x = 0; x < m_width; ++x)
	for(uint32_t y = 0; y < (m_height/2)+1; ++y)
	{
		double tmp = (*this)(x,y);
		(*this)(x, y) = (*this)(x, m_height - y);
		(*this)(x, m_height - y) = tmp;
	}
}

GridFunction create_circle_image(uint32_t img_size, double diam_percent, double outside_color, double inside_color)
{
	GridFunction img(img_size, img_size, outside_color);
	uint32_t half_img_size = img_size / 2;
	double radius_squared = (img_size*img_size*diam_percent*diam_percent) / 4.0;

	for(uint32_t x = 0; x < img_size; ++x)
	for(uint32_t y = 0; y < img_size; ++y)
	{
		if( (x - half_img_size)*(x - half_img_size) + (y - half_img_size)*(y - half_img_size) <= radius_squared)
			img(x,y) = inside_color;
	}

	return img;
}