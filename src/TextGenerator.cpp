#include "TextGenerator.h"
#include <iostream>

TextGenerator::TextGenerator(const LanguageModel& model)
    : model_(model)
{
    //later
}

void TextGenerator::seed(unsigned int s) {
    rng_.seed(s);
}

std::string TextGenerator::generate(std::size_t length) {
    //need to implement text generation based on the model
    return "[GENERATOR NOT IMPLEMENTED YET]";
}
