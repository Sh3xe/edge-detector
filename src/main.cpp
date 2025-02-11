#include "EdgeDetector.hpp"

int main()
{
    GridParameters params;

    EdgeDetector edge_detector(params);

    GridFunction circle_image = create_circle_image(256, 0.6, 0.2, 1.0);

    auto result = edge_detector.solve(circle_image, 100);

    result.save_with_colored_border("out.pgm", 0.0, 0.0, 1.0, 4);
;}
