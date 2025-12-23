#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <vector>
#include <string>
#include "document.h"
#include "indexer.h"
#include "tfidf.h"

class SearchEngine {
public:
    SearchEngine(const std::vector<Document>& docs);

    std::vector<std::pair<int, double>>
    search(const std::string& query);

private:
    std::vector<Document> documents;
    Indexer::InvertedIndex index;

    static double cosineSimilarity(
        const TFIDF::Vector& a,
        const TFIDF::Vector& b);
};

#endif
