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



double GridFunction::gradient_x(uint32_t x,uint32_t y, char a)
{
	double Grad_x=0;


	if(a == '+'){


		if(x== m_width-1){

			Grad_x = 0;

		}else{

			Grad_x = (*this)(x+1,y) - (*this)(x,y);

		}
		

	}

	if(a== '-'){

		if(x== 0){

			Grad_x = 0;

		}else{

			Grad_x = (*this)(x-1,y) - (*this)(x,y);

		}
		

	}


	if(a=='0'){

		if(x==0){
			
			return gradient_x(x,y,'+');
		}

		if(x==m_width-1){

			return gradient_x(x,y,'-');

		}

		Grad_x =  ((*this)(x+1,y) - (*this)(x-1,y))/2;

	}
	

	return Grad_x;
}

double GridFunction::gradient_y(uint32_t x,uint32_t y,char a)
{
	double Grad_y=0;

	
	if(a == '+'){

		if(y== m_height-1){

			Grad_y = 0;

		}else{

			Grad_y = (*this)(x,y+1) - (*this)(x,y);

		}
		
		

	}

	if(a== '-'){

		if(y == 0){

			Grad_y = 0;

		}else{

			Grad_y = (*this)(x,y-1) - (*this)(x,y);

		}

	}


	if(a=='0'){

		if(y==0){
			
			return gradient_y(x,y,'+');
		}

		if(y==m_height-1){

			return gradient_y(x,y,'-');

		}



		Grad_y = ((*this)(x,y+1) - (*this)(x,y-1))/2;

	}
	
	return Grad_y;
}


std::map<uint32_t,std::vector<std::pair<uint32_t,uint32_t>>> GridFunction::Inside_Outside(){

	std::map<uint32_t,std::vector<std::pair<uint32_t,uint32_t>>> Results;
	std::vector<std::pair<uint32_t,uint32_t>> Points_1;
	std::vector<std::pair<uint32_t,uint32_t>> Points_0;
	std::pair<uint32_t,uint32_t> par;

	

	for(size_t i=0;i<m_data.size();i++){
		if(m_data[i]>0){

			uint32_t j = (uint32_t)i;
			uint32_t x =0;
			uint32_t y =0;

			while (j>= m_width)
			{
				y = y+1;
				j = j-m_width;
			}
			
			x = j;

			par = std::make_pair(x,y);

			Points_1.push_back(par);

		}else{

			uint32_t j = (uint32_t)i;
			uint32_t x =0;
			uint32_t y =0;

			while (j>= m_width)
			{
				y = y+1;
				j = j-m_width;
			}
			
			x = j;

			par = std::make_pair(x,y);

			Points_0.push_back(par);

		}
		
	}

	Results[0] = Points_0;
	Results[1] = Points_1;

	return Results;
}


double GridFunction::C_positive(GridFunction phi){

	double sum_numerator  =  0;
	double sum_denominator = 0;
	double epsilon = 2.220446049250313e-16; 

	std::vector<std::pair<uint32_t,uint32_t>> Points_1;

	Points_1 = phi.Inside_Outside()[1];

	sum_denominator = (double)Points_1.size() + epsilon;

	for(uint32_t i =0; i< Points_1.size();i++){

		sum_numerator = sum_numerator + (*this)(Points_1[i].first,Points_1[i].second);

	}


	return sum_numerator/sum_denominator;
}




double GridFunction::C_negative(GridFunction phi){

	double sum_numerator  =  0;
	double sum_denominator = 0;
	double epsilon = 2.220446049250313e-16; 

	std::vector<std::pair<uint32_t,uint32_t>> Points_0;

	Points_0 = phi.Inside_Outside()[0];

	sum_denominator = (double)Points_0.size() + epsilon;

	for(uint32_t i =0; i< Points_0.size();i++){

		sum_numerator = sum_numerator + (*this)(Points_0[i].first,Points_0[i].second);

	}


	return sum_numerator/sum_denominator;
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

bool GridFunction::save_with_colored_border(const std::string &path, double border_r, double border_g, double border_b, unsigned border_width)
{
	std::fstream file {path, std::ios::out};

	if( !file )
	{
		std::cout << "Cannot open: \"" << path << "\"" << std::endl;
		return false;
	}

	file << "P3\n";
	file << m_width << " " << m_height << " " << 255 << "\n";

	for( uint32_t j  = 0; j < m_height; j++) {
		for( uint32_t i  = 0; i < m_width; i++) {
			double grayscale_value = (*this)(i,j);
			
			double min_val = grayscale_value;
			double max_val = grayscale_value;

			// Check if we are in a border in a border_width px area
			for(int dx = -(border_width/2); dx <= (int)(border_width/2); ++dx)
			for(int dy = -(border_width/2); dy <= (int)(border_width/2); ++dy)
			{
				if((int)i+dx < 0 || i+dx >= m_width || (int)j+dy < 0 || j+dy >= m_height)
					continue;

				if((*this)(i+dx,j+dy) > max_val)
					max_val = (*this)(i+dx,j+dy);

				if((*this)(i+dx,j+dy) < min_val)
					min_val = (*this)(i+dx,j+dy);
			}


			if (abs(max_val - min_val) > 0.01) 
			{
				file << (int)(border_r*255) << " " << (int)(border_g*255) << " " << (int)(border_b*255) << " ";
			}
			else 
			{
				file << (int)(grayscale_value*255) << " " << (int)(grayscale_value*255) << " " << (int)(grayscale_value*255) << " ";
			}
		}
		file << "\n";
	}

	return true;
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
