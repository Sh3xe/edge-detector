#include "EdgeDetector.hpp"
#include "Config.hpp"
#include <iostream>

int main(int argc, char **argv)
{    
    if(argc < 4)
    {
        std::cout << "ERROR: wrong command. Correct use \"prog config_path input_path output_path\"" << std::endl;
        return 1;
    }

    std::string config_path = argv[1];
    std::string input_image = argv[2];
    std::string output_path = argv[3];

    Config config {config_path};
    if(!config)
    {
        std::cout << "ERROR: cannot load \"" << config_path << "\"" << std::endl;
        return -1;
    }

    GridParameters circle_params;
    try
    {
        circle_params.mu = config.get_float("mu");
        circle_params.epsilon = config.get_float("epsilon");
        circle_params.v = config.get_float("v");
        circle_params.lambda_1 = config.get_float("lambda_1");
        circle_params.lambda_2 = config.get_float("lambda_2");
        circle_params.tolerance = config.get_float("tolerance");
        circle_params.delta_t = config.get_float("delta_t");
        circle_params.eta = config.get_float("eta");
        circle_params.max_iterations = config.get_int("max_iter");
        circle_params.log_iterations = config.get_bool("log_iter");
        circle_params.save_iter = config.get_bool("save_iter");
    }
    catch(std::runtime_error err)
    {
        std::cout << "Improper config: ";
        std::cout << err.what() << std::endl;
    }

    EdgeDetector edge_detector(circle_params);

    GridFunction photo_image(input_image);

    auto result = edge_detector.solve(photo_image);

    photo_image.save_to_pgm("input.pgm");
    discretize_colors(result).save_with_colored_border(output_path);    
;}
