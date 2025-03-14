#include "EdgeDetector.hpp"
<<<<<<< Updated upstream

int main()
{
=======
#include <iostream>
#include <string.h>
#include <string>

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

    std::string world;

>>>>>>> Stashed changes
    GridParameters params;

    EdgeDetector edge_detector(params);

<<<<<<< Updated upstream
    GridFunction circle_image = create_circle_image(256, 0.6, 0.2, 1.0);

    auto result = edge_detector.solve(circle_image, 100);

    result.save_with_colored_border("out.pgm", 0.0, 0.0, 1.0, 4);
=======
    std::cout<<"By now,if you did not add other any other images the possible archives are the following to test: "<<std::endl;
    std::cout<<"ti_out.pgm(picture of the student Thibaut Pannet)"<<std::endl;
    std::cout<<"PengBrew_out.pgm(symbol of a famous penguim)"<<std::endl;
    std::cout<<"test_photographer.pgm"<<std::endl;
    std::cout<<"If you want to add any image, firstly assure yourself of being a P2 pmg archive, otherwise it will not work"<<std::endl;




    std::cout<<"Tell the name of the file in the directory Images that you want to find the contour: "<<std::endl;
    std::cin>>world;

    // GridFunction photo_image("../test_photographer.pgm");
    auto photo_image = create_circle_image(256, 0.6, 0.0, 1.0);

    //"Images/test_photographer.pgm"

    photo_image = GridFunction(std::string("Images/")+ world);

    auto result = edge_detector.solve(photo_image, 100000);

    //photo_image.save_to_pgm("input.pgm");
    result.save_to_pgm("Images/out.pgm");
    result.save_with_colored_border("Images/out_col.pgm");
>>>>>>> Stashed changes
;}
