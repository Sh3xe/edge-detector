#include "GridFunction.hpp"
#include <iostream>
int main()
{
    auto circle_img = create_circle_image(32, 0.5, 0.0, 1.0);
    circle_img.save_to_pgm("output/img.pgm");

    GridFunction saved_circle("output/img.pgm", 128, 128);
    GridFunction test_pos = saved_circle.Gradient_x_pos();
    test_pos.save_to_pgm("output/test_pos.pgm");
    GridFunction test_neg = saved_circle.Gradient_x_neg();
    test_neg.save_to_pgm("output/test_neg.pgm");
    GridFunction test_neu = saved_circle.Gradient_x_neu();
    GridFunction novo=(test_neu)/(test_neu);
    novo.save_to_pgm("output/test_neu.pgm");


    saved_circle.save_to_pgm("output/other.pgm");

    std::cout<<saved_circle.gradient_x(12,12,'+')<<std::endl;
    std::cout<<saved_circle.Inside_Outside()[1][12].first<<std::endl;
    std::cout<<saved_circle(65,32)<<std::endl;
    std::cout<<saved_circle.C_positive(saved_circle)<<" And C_negative : "<<saved_circle.C_negative(saved_circle)<<std::endl;
}
