#include "EdgeDetector.hpp"
#include <iostream>

// double img_distance(const GridFunction &left, const GridFunction &right)
// {
// 	double integral = 0.0;
// 	for(size_t i = 0; i < left.get_width(); ++i)
// 	for(size_t j = 0; j < left.get_height(); ++j)
// 	{
// 		double diff = right(i,j) - left(i,j);
// 		integral += diff*diff;
// 	}

// 	return sqrt(integral);
// }

int main()
{
    // GridFunction img0("inter145.pgm");
    // GridFunction img1("inter146.pgm");

    // std::cout << img_distance(img0, img0) << std::endl;
    // std::cout << img_distance(img1, img0) << std::endl;

    GridParameters params;

    EdgeDetector edge_detector(params);

    // GridFunction photo_image("../test_photographer.pgm");
    auto photo_image = create_circle_image(256, 0.6, 0.0, 1.0);

    auto result = edge_detector.solve(photo_image, 10000);

    photo_image.save_to_pgm("input.pgm");
    result.save_to_pgm("out.pgm");
    result.save_with_colored_border("out_col.pgm");
;}
