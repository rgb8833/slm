#include "LanguageModel.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

LanguageModel::LanguageModel() : k_(0), total_words_(0) {}

void LanguageModel::buildFromFile(const std::string &filename, std::size_t k) {
    k_ = k;
    word_counts_.clear();
    next_counts_.clear();
    total_words_ = 0;

    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        std::cerr << "ERROR could not open file: " << filename << std::endl;
        return;
    }

    //read entire file content into a single string
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    std::string text = buffer.str();
    
    //check if text is long enough for k-grams
    if (text.length() < k_) {
        std::cerr << "[ERROR] text length (" << text.length() << ") is less than k (" << k_ << ")" << std::endl;
        return;
    }

    //iterate up to the start of the last possible k-word
    for (std::size_t i = 0; i <= text.length() - k_; ++i) {
        std::string word = text.substr(i, k_);
        
        // 1. record word frequency (n(w))
        word_counts_[word]++;
        total_words_++;
        
        // 2. record the next character (n(w, c)), if it exists
        if (i + k_ < text.length()) {
            char next_char = text[i + k_];
            next_counts_[word][next_char]++;
        }
    }
}

std::vector<std::string> LanguageModel::words() const { 
    //placeholder implementation
    return {}; 
}

//implement random selection of a start word based on word_counts_
std::string LanguageModel::chooseStartWord(std::mt19937& rng) const {
    if (total_words_ == 0 || word_counts_.empty()) {
        return "";
    }

    //keys store the words, probabilities store the counts (weights)
    std::vector<std::string> keys;
    std::vector<double> probabilities;

    for (const auto& pair : word_counts_) {
        //only allow words that have recorded transitions
        if (next_counts_.count(pair.first)) { 
            keys.push_back(pair.first);
            probabilities.push_back(pair.second); //count is used as weight
        }
    }

    if (keys.empty()) {
        return "";
    }

    //use discrete_distribution to sample based on weights
    std::discrete_distribution<> dist(probabilities.begin(), probabilities.end());
    int index = dist(rng);

    return keys[index];
}

//implement random selection of the next character
char LanguageModel::chooseNextChar(const std::string& word, std::mt19937& rng) const {
    //check if the word exists in the transition model
    if (next_counts_.find(word) == next_counts_.end()) {
        //this should be caught by chooseStartWord, but is a safety net
        throw std::runtime_error("word not found in transition model: " + word);
    }

    const auto& char_counts = next_counts_.at(word);

    //keys store the characters, probabilities store the counts (weights)
    std::vector<char> keys;
    std::vector<double> probabilities;

    for (const auto& pair : char_counts) {
        keys.push_back(pair.first);
        probabilities.push_back(pair.second); // count is used as weight
    }

    if (keys.empty()) {
        throw std::runtime_error("no next characters recorded for word: " + word); 
    }

    //use discrete_distribution to sample based on weights
    std::discrete_distribution<> dist(probabilities.begin(), probabilities.end());
    int index = dist(rng);

    return keys[index];
}