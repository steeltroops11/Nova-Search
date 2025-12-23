#ifndef DOCUMENT_LOADER_H
#define DOCUMENT_LOADER_H

#include <vector>
#include <string>
#include "document.h"

class DocumentLoader {
public:
    static std::vector<Document> loadDocuments(const std::string& directoryPath);
};

#endif
