#include "ScalarFunction.hpp"
#include "Parameters.hpp"

#include <fstream>
#include <cassert>
#include <iostream>

GridFunction::GridFunction(uint32_t width, uint32_t height, double base_value)
{
	construct_constant(width, height, base_value);
}
	
GridFunction::GridFunction(const std::string &pgm_file_path)
{
	if(!load_from_pgm(pgm_file_path))
		construct_constant(128, 128, 0.0f);
}

GridFunction::GridFunction(const std::string &pgm_file_path, uint32_t rescale_width, uint32_t rescale_height)
{

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

	for( int j  = 0; j < m_height; j++) {
		for( int i  = 0; i < m_width; i++) {
			file << (int)(m_data[j*m_height + i] * 255) << " ";
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

	if( is_rgb )
	{
		for( int j = 0; j < height; j++) {
			for( int i = 0; i < width; i++) {
				int pixel;
				file >> pixel;
				m_data[i+j*width] = (double)pixel / (double)interval;
			}
		}
	}
	else
	{
		for( int j = 0; j < height; j++) {
			for( int i = 0; i < width; i++) {
				int r, g, b;
				file >> r >> g >> b;
				m_data[i+j*width] = ((double)r / (double)interval) * 0.3 + ((double)g / (double)interval) * 0.59 + ((double)b / (double)interval) * 0.11;
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