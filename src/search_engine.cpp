#include "search_engine.h"
#include "tokenizer.h"
#include <cmath>

SearchEngine::SearchEngine(const std::vector<Document>& docs)
    : documents(docs) {
    index = Indexer::buildIndex(documents);
}

double SearchEngine::cosineSimilarity(
    const TFIDF::Vector& a,
    const TFIDF::Vector& b) {

    double dot = 0.0;
    double magA = 0.0;
    double magB = 0.0;

    for (auto it = a.begin(); it != a.end(); ++it) {
        const std::string& term = it->first;
        double valA = it->second;

        magA += valA * valA;

        auto bit = b.find(term);
        if (bit != b.end()) {
            dot += valA * bit->second;
        }
    }

    for (auto it = b.begin(); it != b.end(); ++it) {
        double valB = it->second;
        magB += valB * valB;
    }

    if (magA == 0.0 || magB == 0.0)
        return 0.0;

    return dot / (std::sqrt(magA) * std::sqrt(magB));
}

std::vector<std::pair<int, double>>
SearchEngine::search(const std::string& query) {

    auto queryTokens = Tokenizer::tokenize(query);

    Indexer::InvertedIndex queryIndex;
    for (const auto& token : queryTokens) {
        queryIndex[token][0]++;
    }

    auto queryVec = TFIDF::computeTFIDF(
        0, documents.size(), queryIndex);

    std::vector<std::pair<int, double>> results;

    for (const auto& doc : documents) {
        auto docVec = TFIDF::computeTFIDF(
            doc.id, documents.size(), index);

        double score = cosineSimilarity(queryVec, docVec);
        results.push_back({doc.id, score});
    }

    return results;
}
