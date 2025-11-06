#include <iostream>
#include <string>
#include <random> 
#include <stdexcept> // for argument error handling
#include "LanguageModel.h"
#include "TextGenerator.h" // include generator header

int main(int argc, char* argv[]) {
    std::cout << "=== Small Language Model (SLM) ===" << std::endl;

    if (argc != 4) {
        std::cout << "usage: ./slm <k> <input_file> <num_chars>" << std::endl;
        return 1;
    }

    int k;
    std::string filename;
    int num_chars;
    
    try {
        k = std::stoi(argv[1]);
        filename = argv[2];
        num_chars = std::stoi(argv[3]);
        
        if (k <= 0) {
            std::cerr << "ERROR k must be a positive integer." << std::endl;
            return 1;
        }
        if (num_chars <= 0) {
            std::cerr << "ERROR num_chars must be a positive integer." << std::endl;
            return 1;
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "ERROR invalid argument: k and num_chars must be integers." << std::endl;
        return 1;
    } catch (const std::out_of_range& e) {
        std::cerr << "ERROR argument out of range." << std::endl;
        return 1;
    }

    LanguageModel model;
    model.buildFromFile(filename, k);

    std::cout << "model built with k = " << k << std::endl;
    std::cout << "ready to generate " << num_chars << " characters..." << std::endl;

    TextGenerator generator(model);
    
    //fixed seed for reproducible results
    generator.seed(42); 

    std::string generated_text = generator.generate(num_chars);
    
    std::cout << "--- Generated Text ---" << std::endl;
    std::cout << generated_text << std::endl;
    std::cout << "----------------------" << std::endl;

    return 0;
}