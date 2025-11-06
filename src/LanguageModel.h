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

    std::vector<std::string> words() const;

    int wordCount(const std::string &w) const;

    std::vector<std::pair<char,int>> nextCharCounts(const std::string &w) const;

    std::string chooseStartWord(std::mt19937 &rng) const;

    char sampleNextChar(const std::string &w, std::mt19937 &rng) const;

    std::size_t k() const { return k_; }

private:
    std::size_t k_ = 0;
    std::map<std::string,int> word_counts_;                   // n(w)
    std::map<std::string, std::map<char,int>> next_counts_;   // n(w,c)
    int total_words_ = 0;

    //cached for fast random sampling of start words
    mutable std::vector<std::string> words_cache_;
    mutable std::vector<int> word_weights_cache_;
    mutable bool caches_built_ = false;

    void buildCaches() const;
};

#endif 
