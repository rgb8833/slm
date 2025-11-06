#ifndef LANGUAGE_MODEL_H
#define LANGUAGE_MODEL_H

#include <string>
#include <map>
#include <vector>
#include <random>

class LanguageModel {
public:
    LanguageModel();

    void buildFromFile(const std::string &filename, std::size_t k);

    //return the set of words (k-length substrings) seen in the model
    std::vector<std::string> words() const;

    //return the model's word size k
    std::size_t k() const { return k_; }

    //choose a starting word based on word frequency
    std::string chooseStartWord(std::mt19937& rng) const;

    //choose the next character c given word w based on P(c|w)
    char chooseNextChar(const std::string& word, std::mt19937& rng) const;

private:
    std::size_t k_;
    //count of each word (n(w))
    std::map<std::string,int> word_counts_;
    //for each word, counts of next characters n(w,c)
    std::map<std::string, std::map<char,int>> next_counts_;
    int total_words_;
};

#endif