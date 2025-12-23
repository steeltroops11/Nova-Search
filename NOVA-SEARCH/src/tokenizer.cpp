#include "tokenizer.h"
#include <sstream>
#include <unordered_set>
#include <algorithm>
#include <cctype>

static const std::unordered_set<std::string> STOPWORDS = {
    "the", "is", "and", "a", "an", "of", "to", "in", "on", "for", "with"
};

std::vector<std::string> Tokenizer::tokenize(const std::string& text) {
    std::string cleanText;
    cleanText.reserve(text.size());

    // Lowercase and remove punctuation
    for (char c : text) {
        if (std::isalnum(c) || std::isspace(c)) {
            cleanText += std::tolower(c);
        }
    }

    std::stringstream ss(cleanText);
    std::vector<std::string> tokens;
    std::string word;

    while (ss >> word) {
        if (STOPWORDS.find(word) == STOPWORDS.end()) {
            tokens.push_back(word);
        }
    }

    return tokens;
}
