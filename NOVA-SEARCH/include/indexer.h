#ifndef INDEXER_H
#define INDEXER_H

#include <unordered_map>
#include <vector>
#include <string>
#include "document.h"

class Indexer {
public:
    using InvertedIndex =
        std::unordered_map<std::string, std::unordered_map<int, int>>;

    static InvertedIndex buildIndex(
        const std::vector<Document>& documents);
};

#endif
