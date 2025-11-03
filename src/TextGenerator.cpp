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
    std::string result;
    std::size_t k = model_.k();

    if (k == 0) {
        return result;
    }

    //pick a starting word from the model
    std::string word = model_.chooseStartWord(rng_);

    if (word.empty()) {
        return result; //no valid start word
    }
    return result;
}
