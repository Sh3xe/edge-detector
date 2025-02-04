#include "GridFunction.hpp"
#include <iostream>
int main()
{
    auto circle_img = create_circle_image(32, 0.5, 0.0, 1.0);
    circle_img.save_to_pgm("output/img.pgm");

    GridFunction saved_circle("output/img.pgm", 128, 128);
    saved_circle.save_to_pgm("output/other.pgm");

    std::cout<<saved_circle.Integral()<<" The positive Gradiente: "<<saved_circle.gradient_x(12,12,'+')<<std::endl;
}
