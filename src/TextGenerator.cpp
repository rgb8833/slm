#include "TextGenerator.h"
#include <iostream>
#include <stdexcept>

TextGenerator::TextGenerator(const LanguageModel& model)
    : model_(model)
{
    //model reference initialized
}

void TextGenerator::seed(unsigned int s) {
    rng_.seed(s);
}

std::string TextGenerator::generate(std::size_t length) {
    std::string result = "";
    std::size_t k = model_.k();

    if (k == 0 || length == 0) {
        return result;
    }
    
    // 1. choose a starting word (w=w1w2...wk)
    std::string word = model_.chooseStartWord(rng_);

    if (word.empty()) {
        std::cerr << "[ERROR] no valid start word found." << std::endl;
        return result;
    }

    //output the starting word (w1...wk)
    result += word;
    
    //start generating from the (k+1)-th character until the requested length is met
    for (std::size_t i = k; i < length; ++i) {
        try {
            // 2. look up a character distribution for w, and sample the next character c
            char next_char = model_.chooseNextChar(word, rng_);

            // 3. output c
            result += next_char;
            
            // 4. set w = w2w3...wk-1c (slide the window)
            word = word.substr(1) + next_char;
            
        } catch (const std::runtime_error& e) {
            std::cerr << "[WARNING] generation stopped early: " << e.what() << std::endl;
            //stop if an unknown word is encountered
            break; 
        }
    }
    
    //return only the requested length
    return result.substr(0, length); 
}