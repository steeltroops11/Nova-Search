#ifndef TFIDF_H
#define TFIDF_H

#include <unordered_map>
#include <vector>
#include <string>
#include "indexer.h"

class TFIDF {
public:
    using Vector = std::unordered_map<std::string, double>;

    static double computeIDF(int totalDocs, int docFreq);
    static Vector computeTFIDF(
        int docId,
        int totalDocs,
        const Indexer::InvertedIndex& index);
};

#endif
