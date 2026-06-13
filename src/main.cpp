#include <iostream>
#include <fstream>
#include <sstream>
int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Incorrect Usage" << std::endl;
        std::cerr << "ove <input.ov>" << std::endl;
        return EXIT_FAILURE;
    }

    std::fstream input(argv[1], std::ios::in);
    {
        
    }
    std::stringstream contents_stream;
    contents_stream << input.rdbuf();
    input.close();

    //std::cout << argv[1] << std::endl;

    return EXIT_SUCCESS;
}