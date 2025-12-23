#include "indexer.h"
#include "tokenizer.h"

Indexer::InvertedIndex Indexer::buildIndex(
    const std::vector<Document>& documents) {

    InvertedIndex index;

    for (const auto& doc : documents) {
        auto tokens = Tokenizer::tokenize(doc.content);

        for (const auto& token : tokens) {
            index[token][doc.id]++;
        }
    }

    return index;
}
