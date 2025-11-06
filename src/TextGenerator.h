#ifndef TEXT_GENERATOR_H
#define TEXT_GENERATOR_H

#include "LanguageModel.h"
#include <string>
#include <random>
#include <stdexcept>

class TextGenerator {
public:
    TextGenerator(const LanguageModel& model);
    void seed(unsigned int s);
    std::string generate(std::size_t length);

private:
    //the model reference is const because the generator only reads data
    const LanguageModel& model_; 
    std::mt19937 rng_; //random number generator
};

#endif