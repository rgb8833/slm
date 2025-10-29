#include <iostream>
#include <string>
#include "LanguageModel.h"

int main(int argc, char* argv[]) {
    std::cout << "=== Small Language Model (SLM) ===" << std::endl;

    // Check arguments
    if (argc != 4) {
        std::cout << "Usage: ./slm <k> <input_file> <num_chars>" << std::endl;
        return 1;
    }

    // Read command line arguments
    int k = std::stoi(argv[1]);
    std::string filename = argv[2];
    int num_chars = std::stoi(argv[3]);

    // Create model (not fully implemented yet)
    LanguageModel model;
    model.buildFromFile(filename, k);

    std::cout << "[INFO] Model built with k = " << k << std::endl;
    std::cout << "[INFO] Ready to generate " << num_chars << " characters..." << std::endl;

    // TODO: add text generation step later
    std::cout << "[TODO] Text generation not implemented yet." << std::endl;

    return 0;
}
