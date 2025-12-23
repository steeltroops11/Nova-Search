#include "tfidf.h"
#include <cmath>

double TFIDF::computeIDF(int totalDocs, int docFreq) {
    return std::log((double)totalDocs / (1 + docFreq));
}

TFIDF::Vector TFIDF::computeTFIDF(
    int docId,
    int totalDocs,
    const Indexer::InvertedIndex& index) {

    Vector vec;

    for (auto it = index.begin(); it != index.end(); ++it) {
        const std::string& term = it->first;
        const auto& postings = it->second;

        auto docIt = postings.find(docId);
        if (docIt != postings.end()) {
            int tf = docIt->second;
            int df = postings.size();

            vec[term] = tf * computeIDF(totalDocs, df);
        }
    }

    return vec;
}
