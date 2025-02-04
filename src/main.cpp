#include "GridFunction.hpp"

int main()
{
    auto circle_img = create_circle_image(32, 0.5, 0.0, 1.0);
    circle_img.save_to_pgm("output/img.pgm");

    GridFunction saved_circle("output/img.pgm", 128, 128);
    saved_circle.save_to_pgm("output/other.pgm");
}
