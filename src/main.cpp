#include "EdgeDetector.hpp"

int main()
{
    GridParameters params;

    EdgeDetector edge_detector(params);

    GridFunction circle_image = create_circle_image(256, 0.6, 0.2, 1.0);

    auto result = edge_detector.solve(circle_image, 100);

    circle_image.save_with_colored_border("input.pgm", 0.0, 0.0, 1.0, 4);

    result.save_with_colored_border("out.pgm", 0.0, 0.0, 1.0, 4);

    GridFunction photo_image("test_photographer.pgm");

    auto result_2 = edge_detector.solve(photo_image, 10000);

    photo_image.save_with_colored_border("input_2.pgm", 0.0, 0.0, 1.0, 4);

    result_2.save_with_colored_border("out_2.pgm", 0.0, 0.0, 1.0, 4);


;}
